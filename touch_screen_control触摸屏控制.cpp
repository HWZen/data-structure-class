//
// Created by HWZ on 2025/3/10.
//
#include "cppUtil//tools.h"
#include <algorithm>
#include <iostream>
#include <format>
#include <vector>
#include <array>
#include <ranges>

#include <Windows.h>
#include <setupapi.h>
#include <initguid.h>
#include <devguid.h>
#include <devpkey.h>
#include <Regstr.h>

#pragma comment(lib, "setupapi.lib")


static void enumHIDDevice(const auto &Executor){
    HDEVINFO hDevInfo;
    SP_DEVINFO_DATA deviceInfoData{sizeof(SP_DEVINFO_DATA)};

    hDevInfo = SetupDiGetClassDevs(&GUID_DEVCLASS_HIDCLASS, 0, nullptr, DIGCF_PRESENT);
    defer([&](){
        SetupDiDestroyDeviceInfoList(hDevInfo);
    });

    if (hDevInfo == INVALID_HANDLE_VALUE){
        std::wcout << L"SetupDiGetClassDevs failed" << std::endl;
        return;
    }

    for (int i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &deviceInfoData); i++)
    {
        DWORD dataT;
        std::array<wchar_t, 2048> buffer{};
        DWORD buffersize = sizeof(buffer);
        DWORD req_bufsize{ 0 };

        // Get device description
        if (!SetupDiGetDeviceRegistryProperty(hDevInfo,
            &deviceInfoData,
            SPDRP_DEVICEDESC,
            &dataT,
            (PBYTE)buffer.data(),
            buffersize,
            &buffersize))
        {
            std::wcout << L"Get SPDRP_DEVICEDESC failed" << std::endl;
        }

        // Retrieves a specified Plug and Play device property
        if (!SetupDiGetDeviceRegistryProperty(
            hDevInfo,
            &deviceInfoData,
            SPDRP_DEVICEDESC,
            &dataT,
            (LPBYTE)buffer.data(),
            buffersize,
            &req_bufsize))
        {
            std::wcout << L"SetupDiGetDeviceRegistryProperty failed" << std::endl;
            continue;
        }

        std::wstring deviceDesc(buffer.data());
        std::wcout << L"Device: " << deviceDesc << std::endl;

        // Get hardware ID
        if (auto res = SetupDiGetDeviceRegistryProperty(
                hDevInfo,
                &deviceInfoData,
                SPDRP_HARDWAREID,
                &dataT,
                (LPBYTE)&buffer,
                sizeof(buffer),
                &req_bufsize);
            res == FALSE)
        {
            if (auto lastError = GetLastError(); lastError == ERROR_INVALID_DATA)
            {
                std::wcout << L"No Hardware ID" << std::endl;
            }
            else
                std::wcout << L"SetupDiGetDeviceRegistryProperty failed: " << lastError << std::endl;
        }

        std::wcout << L"Hardware ID: " << buffer.data() << std::endl;

        // Get device property keys
        SetupDiGetDevicePropertyKeys(hDevInfo, &deviceInfoData, nullptr, 0, &req_bufsize, 0);
        std::vector<DEVPROPKEY> propKeys(req_bufsize);
        if (!SetupDiGetDevicePropertyKeys(hDevInfo, &deviceInfoData, propKeys.data(),
            static_cast<DWORD>(propKeys.size()), &req_bufsize, 0))
        {
            std::wcout << L"SetupDiGetDevicePropertyKeys failed" << std::endl;
            continue;
        }

        auto it = std::ranges::find(propKeys, DEVPKEY_Device_Parent);
        if (it == propKeys.end())
        {
            std::wcout << L"DEVPKEY_Device_Parent not found" << std::endl;
            continue;
        }

        // Get parent device information
        DEVPROPTYPE propType;
        DWORD propSize{ 0 };
        if (auto res = SetupDiGetDevicePropertyW(hDevInfo,
                &deviceInfoData,
                &DEVPKEY_Device_Parent,
                &propType,
                nullptr,
                0,
                &propSize,
                0); !res)
        {
            if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
            {
                std::wcout << L"SetupDiGetDevicePropertyW1 failed" << std::endl;
                continue;
            }
        }

        std::vector<BYTE> propData(propSize);
        if (!SetupDiGetDevicePropertyW(
            hDevInfo,
            &deviceInfoData,
            &DEVPKEY_Device_Parent,
            &propType,
            propData.data(),
            static_cast<DWORD>(propData.size()),
            &propSize,
            0))
        {
            std::wcout << L"SetupDiGetDevicePropertyW2 failed" << std::endl;
            continue;
        }

        std::wstring_view parent(reinterpret_cast<wchar_t*>(propData.data()), propSize / sizeof(wchar_t) - 1);

        std::wcout << L"Parent: " << parent << std::endl;
        std::wcout << L"---" << std::endl;

        auto res = Executor(hDevInfo, deviceInfoData, deviceDesc);
        if (!res)
            break;
    }
}



json disableTouchScreen()
{
    std::wcout.imbue(std::locale{"chs"});

    json result;
    result["is_ok"] = false;
    result["log"] = json::array();
    bool found = false;

    enumHIDDevice([&](auto &hDevInfo, auto &deviceInfoData, const auto &deviceDesc){
        // Check if it's a touchscreen - look for keywords in description
        auto deviceDescLower = deviceDesc;
        std::transform(deviceDescLower.begin(), deviceDescLower.end(), deviceDescLower.begin(), ::towlower);
        bool isTouchscreen = (deviceDescLower.find(L"touch") != std::wstring::npos && deviceDescLower.find(L"screen") != std::wstring::npos) ||
                             (deviceDescLower.find(L"触摸屏") != std::wstring::npos);

        if (isTouchscreen) {
            std::wcout << L"Found touchscreen: " << deviceDesc << std::endl;

            // Check if device is already disabled
            DWORD devStatus = 0;
            if (!SetupDiGetDeviceRegistryProperty(hDevInfo,
                &deviceInfoData,
                SPDRP_CONFIGFLAGS,
                nullptr,
                (PBYTE)&devStatus,
                sizeof(devStatus),
                nullptr)) {
                std::wcout << L"Failed to get device status" << std::endl;
                result["log"].emplace_back(std::format("'{}' failed to get device status", BT8 deviceDesc.c_str()));
                return true;
            }

            if (devStatus & CONFIGFLAG_DISABLED) {
                std::wcout << L"Touchscreen already disabled" << std::endl;
                result["result"] = "Touchscreen already disabled";
                result["is_ok"] = true;
                found = true;
                return false;
            }

            // Disable the touchscreen device
            SP_PROPCHANGE_PARAMS propChange{};
            propChange.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
            propChange.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
            propChange.Scope = DICS_FLAG_GLOBAL;
            propChange.StateChange = DICS_DISABLE;

            if (!SetupDiSetClassInstallParams(hDevInfo,
                &deviceInfoData,
                &propChange.ClassInstallHeader,
                sizeof(propChange))) {
                std::wcout << L"Failed to set class install params" << std::endl;
                result["log"].emplace_back(std::format("'{}' failed to set class install param", BT8 deviceDesc.c_str()));
                return true;
            }

            if (!SetupDiChangeState(hDevInfo, &deviceInfoData)) {
                std::wcout << L"Failed to disable touchscreen" << std::endl;
                result["log"].emplace_back(std::format("'{}' failed to disable", BT8 deviceDesc.c_str()));
                return true;
            }

            std::wcout << L"Touchscreen disabled successfully" << std::endl;
            result["result"] = "Touchscreen disabled successfully";
            result["is_ok"] = true;
            found = true;
            return false;  // Stop enumeration after finding and disabling
        }

        return true;  // Continue enumeration
    });

    if (!found) {
        result["result"] = "No touchscreen device found";
        result["is_ok"] = false;
    }
    return result;

}

json enableTouchScreen()
{
    std::wcout.imbue(std::locale{"chs"});

    json result;
    result["is_ok"] = false;
    result["log"] = json::array();
    bool found = false;
    enumHIDDevice([&](auto &hDevInfo, auto &deviceInfoData, const auto &deviceDesc){
        // Check if it's a touchscreen - look for keywords in description
        auto deviceDescLower = deviceDesc;
        std::transform(deviceDescLower.begin(), deviceDescLower.end(), deviceDescLower.begin(), ::towlower);
        bool isTouchscreen = (deviceDescLower.find(L"touch") != std::wstring::npos && deviceDescLower.find(L"screen") != std::wstring::npos) ||
                             (deviceDescLower.find(L"触摸屏") != std::wstring::npos);

        if (isTouchscreen) {
            std::wcout << L"Found touchscreen: " << deviceDesc << std::endl;

            // Check if device is already enabled
            DWORD devStatus = 0;
            if (!SetupDiGetDeviceRegistryProperty(hDevInfo,
                &deviceInfoData,
                SPDRP_CONFIGFLAGS,
                nullptr,
                (PBYTE)&devStatus,
                sizeof(devStatus),
                nullptr)) {
                std::wcout << L"Failed to get device status" << std::endl;
                result["log"].emplace_back(std::format("'{}' failed to get device status", BT8 deviceDesc.c_str()));
                return true;
            }

            if (!(devStatus & CONFIGFLAG_DISABLED)) {
                std::wcout << L"Touchscreen already enabled" << std::endl;
                result["result"] = "Touchscreen already enabled";
                result["is_ok"] = true;
                found = true;
                return false;
            }

            // Enable the touchscreen device
            SP_PROPCHANGE_PARAMS propChange{};
            propChange.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
            propChange.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
            propChange.Scope = DICS_FLAG_GLOBAL;
            propChange.StateChange = DICS_ENABLE;

            if (!SetupDiSetClassInstallParams(hDevInfo,
                &deviceInfoData,
                &propChange.ClassInstallHeader,
                sizeof(propChange))) {
                std::wcout << L"Failed to set class install params" << std::endl;
                result["log"].emplace_back(std::format("'{}' failed to set class install param", BT8 deviceDesc.c_str()));
                return true;
            }

            if (!SetupDiChangeState(hDevInfo, &deviceInfoData)) {
                std::wcout << L"Failed to enable touchscreen" << std::endl;
                result["log"].emplace_back(std::format("'{}' failed to enable", BT8 deviceDesc.c_str()));
                return true;
            }

            std::wcout << L"Touchscreen enabled successfully" << std::endl;
            result["result"] = "Touchscreen enabled successfully";
            result["is_ok"] = true;
            found = true;
            return false;  // Stop enumeration after finding and enabling
        }

        return true;  // Continue enumeration
    });

    if (!found) {
        result["result"] = "No touchscreen device found";
        result["is_ok"] = false;
    }

    return result;
}

json queryTouchScreenStatus()
{
    json result;
    result["is_ok"] = false;
    result["log"] = json::array();
    result["data"] = json::array();
    bool found = false;
enumHIDDevice([&](auto &hDevInfo, auto &deviceInfoData, const auto &deviceDesc){
        // Check if it's a touchscreen - look for keywords in description
        auto deviceDescLower = deviceDesc;
        std::transform(deviceDescLower.begin(), deviceDescLower.end(), deviceDescLower.begin(), ::towlower);
        bool isTouchscreen = (deviceDescLower.find(L"touch") != std::wstring::npos && deviceDescLower.find(L"screen") != std::wstring::npos) ||
                             (deviceDescLower.find(L"触摸屏") != std::wstring::npos);

        if (isTouchscreen) {
            std::wcout << L"Found touchscreen: " << deviceDesc << std::endl;

            // Check device status
            DWORD devStatus = 0;
            if (!SetupDiGetDeviceRegistryProperty(hDevInfo,
                &deviceInfoData,
                SPDRP_CONFIGFLAGS,
                nullptr,
                (PBYTE)&devStatus,
                sizeof(devStatus),
                nullptr)) {
                std::wcout << L"Failed to get device status" << std::endl;
                result["log"].emplace_back(std::format("'{}' failed to get device status", BT8 deviceDesc.c_str()));
                return true;
            }
            found = true;

            if (devStatus & CONFIGFLAG_DISABLED) {
                std::wcout << L"Touchscreen is disabled" << std::endl;
                result["data"].emplace_back(json{{"device", (char *)(BT8 deviceDesc.c_str())}, {"enable", false}});
            } else {
                std::wcout << L"Touchscreen is enabled" << std::endl;
                result["data"].emplace_back(json{{"device", deviceDesc}, {"enable", true}});
            }
            result["is_ok"] = true;
        }

        return true;  // Continue enumeration
    });

    result["found"] = found;
    return result;
}



int main(int argc, char**){
    std::cout << queryTouchScreenStatus() << std::endl;
    if (argc > 1) {
        std::cout << disableTouchScreen() << std::endl;
    } else {
        std::cout << enableTouchScreen() << std::endl;
    }
}