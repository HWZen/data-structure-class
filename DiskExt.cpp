#include "nlohmann/json.hpp"
#include "cppUtil/tools.h"
#include "cppUtil/unicode/legally.h"


#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <format>
#include <fstream>
#include <filesystem>
#include <optional>

#include "nlohmann/json_fwd.hpp"
#include "re2/re2.h"

#include <windows.h>
#include <wbemidl.h>
#include <setupapi.h>
#include <initguid.h>
#include <devguid.h>
#include <devpkey.h>
#include <Regstr.h>
#include <wbemidl.h>
#include <fcntl.h>
#include <io.h>

namespace fs = std::filesystem;

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "comsuppw.lib")
#pragma comment(lib, "setupapi.lib")

using nlohmann::json;
// GUID_DEVCLASS_HIDCLASS



namespace {

struct ComGuard {
	bool initialized = false;

	~ComGuard() {
		if (initialized) {
			CoUninitialize();
		}
	}
};

struct WmiConnection {
	IWbemLocator* locator = nullptr;
	IWbemServices* services = nullptr;

	~WmiConnection() {
		if (services != nullptr) {
			services->Release();
		}
		if (locator != nullptr) {
			locator->Release();
		}
	}
};

bool InitComSecurity(ComGuard& comGuard) {
	const HRESULT initHr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(initHr) && initHr != RPC_E_CHANGED_MODE) {
		std::wcerr << L"CoInitializeEx 失败，HRESULT=" << std::hex << initHr << std::dec << L'\n';
		return false;
	}

	comGuard.initialized = (initHr != RPC_E_CHANGED_MODE);

	const HRESULT secHr = CoInitializeSecurity(
		nullptr,
		-1,
		nullptr,
		nullptr,
		RPC_C_AUTHN_LEVEL_DEFAULT,
		RPC_C_IMP_LEVEL_IMPERSONATE,
		nullptr,
		EOAC_NONE,
		nullptr);

	if (FAILED(secHr) && secHr != RPC_E_TOO_LATE) {
		std::wcerr << L"CoInitializeSecurity 失败，HRESULT=" << std::hex << secHr << std::dec << L'\n';
		return false;
	}

	return true;
}

bool ConnectWmi(WmiConnection& connection) {
	const HRESULT createHr = CoCreateInstance(
		CLSID_WbemLocator,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator,
		reinterpret_cast<LPVOID*>(&connection.locator));
	if (FAILED(createHr)) {
		std::wcerr << L"CoCreateInstance(IWbemLocator) 失败，HRESULT=" << std::hex << createHr << std::dec << L'\n';
		return false;
	}

	BSTR nameSpace = SysAllocString(L"ROOT\\CIMV2");
	if (nameSpace == nullptr) {
		std::wcerr << L"SysAllocString 失败。\n";
		return false;
	}

	const HRESULT connectHr = connection.locator->ConnectServer(
		nameSpace,
		nullptr,
		nullptr,
		nullptr,
		0,
		nullptr,
		nullptr,
		&connection.services);
	SysFreeString(nameSpace);
	if (FAILED(connectHr)) {
		std::wcerr << L"ConnectServer 失败，HRESULT=" << std::hex << connectHr << std::dec << L'\n';
		return false;
	}

	const HRESULT blanketHr = CoSetProxyBlanket(
		connection.services,
		RPC_C_AUTHN_WINNT,
		RPC_C_AUTHZ_NONE,
		nullptr,
		RPC_C_AUTHN_LEVEL_CALL,
		RPC_C_IMP_LEVEL_IMPERSONATE,
		nullptr,
		EOAC_NONE);
	if (FAILED(blanketHr)) {
		std::wcerr << L"CoSetProxyBlanket 失败，HRESULT=" << std::hex << blanketHr << std::dec << L'\n';
		return false;
	}

	return true;
}

IWbemClassObject* QuerySingleObject(IWbemServices* services, const wchar_t* wql) {
	IEnumWbemClassObject* enumerator = nullptr;
	BSTR queryLanguage = SysAllocString(L"WQL");
	BSTR queryText = SysAllocString(wql);
	if (queryLanguage == nullptr || queryText == nullptr) {
		if (queryLanguage != nullptr) {
			SysFreeString(queryLanguage);
		}
		if (queryText != nullptr) {
			SysFreeString(queryText);
		}
		std::wcerr << L"SysAllocString 失败。\n";
		return nullptr;
	}

	const HRESULT execHr = services->ExecQuery(
		queryLanguage,
		queryText,
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		nullptr,
		&enumerator);
	SysFreeString(queryLanguage);
	SysFreeString(queryText);
	if (FAILED(execHr)) {
		std::wcerr << L"ExecQuery 失败，WQL=" << wql << L"，HRESULT=" << std::hex << execHr << std::dec << L'\n';
		return nullptr;
	}

	IWbemClassObject* object = nullptr;
	ULONG returned = 0;
	const HRESULT nextHr = enumerator->Next(WBEM_INFINITE, 1, &object, &returned);
	enumerator->Release();

	if (FAILED(nextHr) || returned == 0) {
		std::wcerr << L"未查询到对象，WQL=" << wql << L"\n";
		return nullptr;
	}

	return object;
}

bool GetWmiString(IWbemClassObject* object, const wchar_t* name, std::wstring& outValue) {
	outValue.clear();

	VARIANT value;
	VariantInit(&value);

	const HRESULT getHr = object->Get(name, 0, &value, nullptr, nullptr);
	if (FAILED(getHr)) {
		VariantClear(&value);
		return false;
	}

	if (value.vt == VT_NULL || value.vt == VT_EMPTY) {
		VariantClear(&value);
		return false;
	}

	VARIANT stringValue;
	VariantInit(&stringValue);
	const HRESULT changeHr = VariantChangeType(&stringValue, &value, 0, VT_BSTR);
	VariantClear(&value);
	if (FAILED(changeHr) || stringValue.vt != VT_BSTR || stringValue.bstrVal == nullptr) {
		VariantClear(&stringValue);
		return false;
	}

	outValue.assign(stringValue.bstrVal, SysStringLen(stringValue.bstrVal));
	VariantClear(&stringValue);
	return true;
}

bool ReadRegString(HKEY root, const wchar_t* subKey, const wchar_t* valueName, std::wstring& outValue) {
	outValue.clear();

	wchar_t buffer[256] = {};
	DWORD bytes = static_cast<DWORD>(sizeof(buffer));
	const LSTATUS status = RegGetValueW(
		root,
		subKey,
		valueName,
		RRF_RT_REG_SZ,
		nullptr,
		buffer,
		&bytes);
	if (status != ERROR_SUCCESS) {
		return false;
	}
	outValue = buffer;
	return true;
}

bool ReadRegDword(HKEY root, const wchar_t* subKey, const wchar_t* valueName, DWORD& outValue) {
	outValue = 0;

	DWORD value = 0;
	DWORD bytes = sizeof(value);
	const LSTATUS status = RegGetValueW(
		root,
		subKey,
		valueName,
		RRF_RT_REG_DWORD,
		nullptr,
		&value,
		&bytes);
	if (status != ERROR_SUCCESS) {
		return false;
	}
	outValue = value;
	return true;
}

std::wstring OrUnknown(const std::wstring& v) {
	if (v.empty()) {
		return L"未知";
	}
	return v;
}

} // namespace



void enumDevice(const GUID& guid_class, const auto& executor){
    HDEVINFO hDevInfo;
    SP_DEVINFO_DATA deviceInfoData{};
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    hDevInfo = SetupDiGetClassDevs(&guid_class, 0, nullptr, DIGCF_PRESENT);
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
        std::wstring hardwareId = buffer.data();
        std::wcout << L"Hardware ID: " << hardwareId << std::endl;

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

        auto res = executor(hDevInfo, deviceInfoData, deviceDesc, hardwareId);
        if (!res)
            break;
    }
}

void enumHIDDevice(const auto& executor){
    enumDevice(GUID_DEVCLASS_HIDCLASS, executor);
}

void enumVideoDevice(const auto& executor)
{
    enumDevice(GUID_DEVCLASS_DISPLAY, executor);
}

json disableTouchScreen()
{
    std::wcout.imbue(std::locale{"chs"});

    json result;
    result["is_ok"] = false;
    result["log"] = json::array();
    bool found = false;

    enumHIDDevice([&](auto &hDevInfo, auto &deviceInfoData, const auto &deviceDesc, const auto&){
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
    enumHIDDevice([&](auto &hDevInfo, auto &deviceInfoData, const auto &deviceDesc, const auto&){
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
    enumHIDDevice([&](auto &hDevInfo, auto &deviceInfoData, const auto &deviceDesc, const auto&){
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



bool WmiQuery(const std::wstring& queryStr, const std::wstring& propertyName, VARIANT& result)
{
    HRESULT hres;

    // 初始化结果
    VariantInit(&result);

    // 初始化 COM
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres) && hres != RPC_E_CHANGED_MODE) {
        return false;
    }
    defer([] { CoUninitialize(); });

    // 设置 COM 安全级别
    hres = CoInitializeSecurity(nullptr, -1, nullptr, nullptr, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE,
            nullptr, EOAC_NONE, nullptr);

    if (FAILED(hres) && hres != RPC_E_TOO_LATE) {
        return false;
    }

    // 创建 WbemLocator
    IWbemLocator* pLoc = nullptr;
    hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
    if (FAILED(hres)) {
        return false;
    }
    defer([pLoc] { pLoc->Release(); });

    // 连接到 WMI
    IWbemServices* pSvc = nullptr;
    hres = pLoc->ConnectServer(BT L"ROOT\\CIMV2", nullptr, nullptr, 0, 0, 0, 0, &pSvc);
    if (FAILED(hres)) {
        return false;
    }
    defer([pSvc] { pSvc->Release(); });

    // 设置代理
    hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr, RPC_C_AUTHN_LEVEL_CALL,
            RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE);
    if (FAILED(hres)) {
        return false;
    }

    // 执行查询
    IEnumWbemClassObject* pEnumerator = nullptr;
    hres = pSvc->ExecQuery(BT L"WQL", BT queryStr.c_str(), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
            nullptr, &pEnumerator);

    if (FAILED(hres)) {
        return false;
    }
    defer([pEnumerator] { pEnumerator->Release(); });

    // 获取第一个结果
    IWbemClassObject* pclsObj = nullptr;
    ULONG uReturn = 0;

    hres = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
    if (uReturn == 0) {
        return false;
    }
    defer([pclsObj] { pclsObj->Release(); });

    // 读取属性
    hres = pclsObj->Get(propertyName.c_str(), 0, &result, 0, 0);
    if (FAILED(hres)) {
        VariantClear(&result);
        return false;
    }

    return true;
}

// 获取系统激活状态（通过WMI）
int systemActivationStatus()
{
    VARIANT vtLicenseStatus;
    VariantInit(&vtLicenseStatus);

    // 查询带有 PartialProductKey 的 Windows 产品许可证状态
    // 这个条件确保我们只获取 Windows 本身的激活状态，而不是 Office 等其他产品
    bool success = WmiQuery(L"SELECT LicenseStatus FROM SoftwareLicensingProduct WHERE PartialProductKey <> "
                                   L"NULL AND Name LIKE '%Windows%'",
            L"LicenseStatus", vtLicenseStatus);

    if (!success) {
        VariantClear(&vtLicenseStatus);
        return -1; // 查询失败
    }

    int status = -1;
    if (vtLicenseStatus.vt == VT_I4) {
        status = vtLicenseStatus.lVal;
    }
    else if (vtLicenseStatus.vt == VT_UI4) {
        status = static_cast<int>(vtLicenseStatus.ulVal);
    }


    VariantClear(&vtLicenseStatus);
    return status;
}

// 注册表路径
const std::wstring registryPath = L"SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings";
const std::vector<std::wstring> pauseKeys = {
	L"PauseFeatureUpdatesStartTime",
	L"PauseQualityUpdatesStartTime",
	L"PauseUpdatesStartTime",
	L"PauseFeatureUpdatesEndTime",
	L"PauseQualityUpdatesEndTime",
	L"PauseUpdatesExpiryTime"
};

// 读取注册表键值
std::wstring ReadRegistryValue(const std::wstring& key) {
	HKEY hKey;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, registryPath.c_str(), 0, KEY_READ | KEY_WOW64_64KEY, &hKey) != ERROR_SUCCESS) {
        return L"Not Set";
    }
	wchar_t value[128] = {0};
	DWORD value_length = sizeof(value);
	if (RegQueryValueExW(hKey, key.c_str(), nullptr, nullptr, (LPBYTE)value, &value_length) != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		return L"Not Set";
	}
	RegCloseKey(hKey);
	return value;
}

// 写入注册表键值
bool WriteRegistryValue(const std::wstring& key, const std::wstring& value) {
	HKEY hKey;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, registryPath.c_str(), 0, KEY_SET_VALUE | KEY_WOW64_64KEY, &hKey) != ERROR_SUCCESS) {
        return false;
    }
	if (RegSetValueExW(hKey, key.c_str(), 0, REG_SZ, (const BYTE*)value.c_str(), DWORD(value.size()+1)*sizeof(wchar_t)) != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		return false;
	}
	RegCloseKey(hKey);
	return true;
}

// 删除注册表键值
bool DeleteRegistryValue(const std::wstring& key) {
	HKEY hKey;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, registryPath.c_str(), 0, KEY_SET_VALUE | KEY_WOW64_64KEY, &hKey) == ERROR_SUCCESS) {
        if (RegDeleteValueW(hKey, key.c_str()) == ERROR_SUCCESS) {
            RegCloseKey(hKey);
            return true;
        } else {
            RegCloseKey(hKey);
            return false;
        }

    } else
    {
        return false;
    }
}


// 获取 Windows Update 状态
bool GetWindowsUpdateStatus() {
    std::vector<std::wstring> activeKeys;
    std::map<std::wstring, std::wstring> pauseStatus;
    for (const auto& key : pauseKeys) {
        auto value = ReadRegistryValue(key);
        pauseStatus[key] = value;
        if (value != L"Not Set") activeKeys.push_back(key);
    }
    bool updateStatus = true;
    time_t now = time(nullptr);
    struct tm tmNow;
    gmtime_s(&tmNow, &now);
    for (const auto& key : activeKeys) {
        if (key.find(L"StartTime") != std::wstring::npos) {
            std::wstring endKey = key;
            size_t pos = endKey.find(L"StartTime");
            endKey.replace(pos, 9, L"EndTime");
            auto startStr = pauseStatus[key];
            auto endStr = pauseStatus[endKey];
            if (endStr != L"Not Set") {
                struct tm tmStart = {}, tmEnd = {};
                swscanf_s(startStr.c_str(), L"%d-%d-%dT%d:%d:%dZ", &tmStart.tm_year, &tmStart.tm_mon, &tmStart.tm_mday, &tmStart.tm_hour, &tmStart.tm_min, &tmStart.tm_sec);
                swscanf_s(endStr.c_str(), L"%d-%d-%dT%d:%d:%dZ", &tmEnd.tm_year, &tmEnd.tm_mon, &tmEnd.tm_mday, &tmEnd.tm_hour, &tmEnd.tm_min, &tmEnd.tm_sec);
                tmStart.tm_year -= 1900; tmStart.tm_mon -= 1;
                tmEnd.tm_year -= 1900; tmEnd.tm_mon -= 1;
                time_t tStart = _mkgmtime(&tmStart);
                time_t tEnd = _mkgmtime(&tmEnd);
                if (now >= tStart && now <= tEnd) {
                    updateStatus = false;
                    break;
                }
            }
        }
    }
    return updateStatus;
}

// 暂停 Windows Update
bool PauseWindowsUpdate(int hours) {
    time_t now = time(nullptr);
    struct tm tmStart;
    gmtime_s(&tmStart, &now);
    time_t tEnd = now + hours * 3600;
    struct tm tmEnd;
    gmtime_s(&tmEnd, &tEnd);
    std::wstring startStr = std::format(L"{:04}-{:02}-{:02}T{:02}:{:02}:{:02}Z", tmStart.tm_year+1900, tmStart.tm_mon+1, tmStart.tm_mday, tmStart.tm_hour, tmStart.tm_min, tmStart.tm_sec);
    std::wstring endStr = std::format(L"{:04}-{:02}-{:02}T{:02}:{:02}:{:02}Z", tmEnd.tm_year+1900, tmEnd.tm_mon+1, tmEnd.tm_mday, tmEnd.tm_hour, tmEnd.tm_min, tmEnd.tm_sec);
    bool ok = true;
    for (int i = 0; i < 3; ++i) {
        ok &= WriteRegistryValue(pauseKeys[i], startStr);
    }
    for (int i = 3; i < 6; ++i) {
        ok &= WriteRegistryValue(pauseKeys[i], endStr);
    }
    if (ok) {
        std::wcout << std::format(L"Windows Update paused for {} hours (until {} UTC)", hours, endStr) << std::endl;
    } else {
        std::wcerr << L"Failed to pause Windows Update." << std::endl;
    }
    return ok;
}

// 恢复 Windows Update
bool ResumeWindowsUpdate() {
    for (const auto& key : pauseKeys) {
        if (!DeleteRegistryValue(key)) {
            return false;
        }
    }
    std::wcout << L"Windows Update resumed." << std::endl;
    return true;
}

json queryGPUDriverInfo()
{
    json result;
    result["found"] = false;
    result["data"] = json::array();
    enumVideoDevice([&](auto& hDevInfo, auto& deviceInfoData, const auto& deviceDesc, const auto& hardwareId) {
        // 获取驱动注册表项
        HKEY hDriverKey = SetupDiOpenDevRegKey(hDevInfo, &deviceInfoData, DICS_FLAG_GLOBAL, 0, DIREG_DRV, KEY_READ);
        std::wstring driverVersion, driverDate;
        if (hDriverKey == INVALID_HANDLE_VALUE) {
            std::wcout << L"Failed to open driver registry key for device: " << deviceDesc << std::endl;
        }
        defer([&]{RegCloseKey(hDriverKey);});
        
        // 读取 DriverVersion
        wchar_t verBuf[256] = {};
        DWORD verSize = sizeof(verBuf);
        if (RegQueryValueExW(hDriverKey, L"DriverVersion", nullptr, nullptr, (LPBYTE)verBuf, &verSize) ==
                ERROR_SUCCESS) {
            driverVersion = verBuf;
        }
        
        // 读取 DriverDate
        wchar_t dateBuf[256] = {};
        DWORD dateSize = sizeof(dateBuf);
        if (RegQueryValueExW(hDriverKey, L"DriverDate", nullptr, nullptr, (LPBYTE)dateBuf, &dateSize) ==
                ERROR_SUCCESS) {
            driverDate = dateBuf;
        }

        result["data"].emplace_back(json{{"device", BT8 deviceDesc}, {"driver_version", BT8 driverVersion}, {"driver_date", BT8 driverDate}, {"hardwareId", BT8 hardwareId}});
        result["found"] = true;
        return true;  // Continue enumeration
    });

    return result;
}

json parseDiskInfoReport(const std::string& reportContent)
{
    json result;
    auto str = legalStringUTF8(reportContent);
    // enum each disk
    re2::StringPiece input(str);
    re2::StringPiece match;
    int index;
    while(RE2::FindAndConsume(&input, R"(\(([0-9]+)\) .+\n-{76}\n([\s\S]+?)\n-- )", &index, &match))
    {
        json disk;
        // parse model
        std::string model;
        if (!RE2::PartialMatch(match, R"(Model : (.+))", &model))
        {
            std::cerr << "Failed to parse model." << std::endl;
            disk["model"] = nullptr;
        } else
        {
            disk["model"] = model;
        }

        // parse powerOnHour
        std::string strPowerOn;
        if (!RE2::PartialMatch(match, R"(Power On Hours ?: ?(\d+))", &strPowerOn))
        {
            std::cerr << "Failed to parse power On Hours." << std::endl;
            disk["powerOnHour"] = nullptr;
        } else
        {
            disk["powerOnHour"] = std::atoi(strPowerOn.c_str());
        }

        // parse powerOnCount
        std::string strPowerOnCount;
        if (!RE2::PartialMatch(match, R"(Power On Count ?: ?(\d+))", &strPowerOnCount))
        {
            std::cerr << "Failed to parse power On Count." << std::endl;
            disk["powerOnCount"] = nullptr;
        } else
        {
            disk["powerOnCount"] = std::atoi(strPowerOnCount.c_str());
        }

        result["diskList"].emplace_back(MV disk);
    }


    return result;
}

HMODULE GetCurrentModule()
{
    HMODULE hModule = NULL;
    GetModuleHandleEx(
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
        (LPCTSTR)GetCurrentModule,
        &hModule);
    return hModule;
}


void extractEmbeddedToExeDir(int resourceId, std::wstring resourceName)
{

    auto module = GetCurrentModule();
    if (module == nullptr)
    {
        throw std::runtime_error("Failed to get current module");
    }

	HRSRC resource = FindResourceW(module, MAKEINTRESOURCEW(resourceId), RT_RCDATA);
	if (resource == nullptr)
	{
        throw std::runtime_error("Failed to find embedded resource");
	}

	const DWORD resourceSize = SizeofResource(module, resource);
	if (resourceSize == 0)
	{
        throw std::runtime_error("Embedded resource is empty");
	}

	HGLOBAL loadedResource = LoadResource(module, resource);
	if (loadedResource == nullptr)
	{
        throw std::runtime_error("Failed to load embedded resource");
	}

	const void *resourceData = LockResource(loadedResource);
	if (resourceData == nullptr)
	{
        throw std::runtime_error("Failed to lock embedded resource");
	}

	const std::filesystem::path outputPath =
			std::filesystem::current_path() / resourceName;

	std::ofstream outputFile(outputPath, std::ios::binary | std::ios::trunc);
	if (!outputFile)
	{
        throw std::runtime_error("Failed to open output file for writing: " + outputPath.string());
	}

	outputFile.write(static_cast<const char *>(resourceData), static_cast<std::streamsize>(resourceSize));
	if (!outputFile.good())
	{
        throw std::runtime_error("Failed to write bytes to file: " + outputPath.string());
	}

	std::cout << "extracted to: " << outputPath.string() << std::endl;
}

// 查询Bios/ec版本，Windows系统版本信息
const char * Run_1005(void*)  try
{
    ComGuard comGuard;
	if (!InitComSecurity(comGuard)) {
		throw std::runtime_error(std::format("Failed to initialize COM security, {}", BT8 GetLastErrorString()));
	}

	WmiConnection connection;
	if (!ConnectWmi(connection)) {
		throw std::runtime_error(std::format("Failed to connect to WMI, {}", BT8 GetLastErrorString()));
	}

	IWbemClassObject* osObject = QuerySingleObject(connection.services, L"SELECT Caption,InstallDate,BuildNumber FROM Win32_OperatingSystem");
	if (osObject == nullptr) {
		throw std::runtime_error("Failed to query Win32_OperatingSystem");
	}

	std::wstring caption;
	std::wstring installDate;
	std::wstring buildNumber;
	GetWmiString(osObject, L"Caption", caption);
	GetWmiString(osObject, L"InstallDate", installDate);
	GetWmiString(osObject, L"BuildNumber", buildNumber);
	osObject->Release();

	const wchar_t* currentVersionKey = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
	std::wstring displayVersion;
	DWORD ubr = 0;
	const bool hasDisplayVersion = ReadRegString(HKEY_LOCAL_MACHINE, currentVersionKey, L"DisplayVersion", displayVersion);
	const bool hasUbr = ReadRegDword(HKEY_LOCAL_MACHINE, currentVersionKey, L"UBR", ubr);

	std::wstring fullBuild = OrUnknown(buildNumber);
	if (!buildNumber.empty() && hasUbr) {
		fullBuild = buildNumber + L"." + std::to_wstring(ubr);
	}

    IWbemClassObject* biosObject = QuerySingleObject(connection.services, L"SELECT SMBIOSBIOSVersion,ReleaseDate,EmbeddedControllerMajorVersion,EmbeddedControllerMinorVersion FROM Win32_BIOS");
	if (biosObject == nullptr) {
		throw std::runtime_error(std::format("Failed to query Win32_BIOS, {}", BT8 GetLastErrorString()));
	}

	std::wstring biosVersion;
	std::wstring biosDate;
	std::wstring ecMajor;
	std::wstring ecMinor;
	GetWmiString(biosObject, L"SMBIOSBIOSVersion", biosVersion);
	GetWmiString(biosObject, L"ReleaseDate", biosDate);
	GetWmiString(biosObject, L"EmbeddedControllerMajorVersion", ecMajor);
	GetWmiString(biosObject, L"EmbeddedControllerMinorVersion", ecMinor);
	biosObject->Release();

    auto ecVersion = [&]() -> std::wstring {
        if (ecMajor.empty() || ecMinor.empty()) {
            return L"未知";
        }
        return ecMajor + L"." + ecMinor;
     }();

    json result{
        {"os", {
            {"version", BT8 caption},
            {"installDate", BT8 installDate},
            {"versionNumber", BT8 (hasDisplayVersion ? displayVersion : L"未知")},
            {"fullBuild", BT8 fullBuild}
        }},
        {"bios", {
            {"biosVersion", BT8 biosVersion},
            {"releaseDate", BT8 biosDate},
            {"ecVersion", BT8 ecVersion},
        }},
    {"version", "1.0.0.5"},
    {"buildTime", __DATE__ " " __TIME__},
    {"description", "查询Bios/ec版本，Windows系统版本信息"}
    };

    static std::string jsonResult;
    jsonResult = result.dump();
    return jsonResult.c_str();
}
catch (const std::exception& e)
{
    json errorResult{
        {"catchException", e.what()}
    };
    static std::string errorRes = errorResult.dump();
    return errorRes.c_str();
}




// 查询C++能力和CrystalDiskInfo的硬盘名称、接口、传输模式、标准，C++能力和CrystalDiskInfo各跑两次
const char * Run_1006(void*) try{

    json crystalDiskInfoResult(json::array());
    json ljtoolDiskResult(json::array());

    // 解压资源文件到临时目录
    extractEmbeddedToExeDir(101, L"CrystalDiskInfo9_4_4.exe");
    extractEmbeddedToExeDir(102, L"LjTool_Disk_Test.dll");

    // 解压CrystalDiskInfo到./diskInfo
    std::wstring diskInfoDir = L".\\diskInfo";
    if (CreateDirectoryW(diskInfoDir.c_str(), nullptr) == FALSE && GetLastError() != ERROR_ALREADY_EXISTS) {
        throw std::runtime_error(std::format("Failed to create diskInfo directory: {}", BT8 diskInfoDir));
    }
    
    auto cmdLine = std::format(".\\CrystalDiskInfo9_4_4.exe x -y -o\"{}\"", BT8 diskInfoDir);
    if (system(cmdLine.c_str()) != 0)
    {
        throw std::runtime_error(std::format("Failed to execute command: {}", cmdLine));
    }

    // 加载dll和函数
    HMODULE hModule = LoadLibraryW(L"LjTool_Disk_Test.dll");
    if (hModule == nullptr) {
        throw std::runtime_error(std::format("Failed to load LjTool_Disk_Test.dll, {}", BT8 GetLastErrorString()));
    }

    using GetDiskInfosFunc = const char *(*)();
    auto getDiskInfos = reinterpret_cast<GetDiskInfosFunc>(GetProcAddress(hModule, "getDiskInfos"));
    if (getDiskInfos == nullptr) {
        FreeLibrary(hModule);
        throw std::runtime_error(std::format("Failed to get getDiskInfos function from LjTool_Disk_Test.dll, {}", BT8 GetLastErrorString()));
    }


    for (int i{}; i < 2; ++i)
    {
        // 执行CrystalDiskInfo，静默执行，获取硬盘报告
        cmdLine = std::format("\"{}\\DiskInfo64.exe\" /CopyExit", BT8 diskInfoDir);
        if (system(cmdLine.c_str()) != 0)
        {
            throw std::runtime_error(std::format("Failed to execute command: {}", cmdLine));
        }

        // 读取报告
        std::wstring reportFile = diskInfoDir + L"\\DiskInfo.txt";
        std::ifstream reportStream(reportFile);
        if (!reportStream.is_open()) {
            throw std::runtime_error(std::format("Failed to open CrystalDiskInfo report file: {}", BT8 reportFile));
        }
        std::string reportContent((std::istreambuf_iterator<char>(reportStream)), std::istreambuf_iterator<char>());
        reportStream.close();

        // 确保reportContent都是合法utf-8
        reportContent = legalStringUTF8(reportContent);

        crystalDiskInfoResult.emplace_back(json{
            {"index", i},
            {"context", reportContent}
        });

        // 删除DiskInfo.txt
        fs::remove(reportFile);


        // 调用C++能力获取硬盘信息



        auto diskInfos = getDiskInfos();
        ljtoolDiskResult.emplace_back(json{
            {"index", i},
            {"context", json::parse(diskInfos)}
        });
    }

    json result{
        {"crystalDiskInfo",   MV crystalDiskInfoResult},
        {"ljtoolDisk", MV ljtoolDiskResult},
        {"version", "1.0.0.6"},
        {"buildTime", __DATE__ " " __TIME__},
        {"description", "查询C++能力和CrystalDiskInfo的硬盘名称、接口、传输模式、标准，C++能力和CrystalDiskInfo各跑两次"}
    };

    static std::string jsonResult;
    jsonResult = result.dump();
    return jsonResult.c_str();

}
catch (const std::exception& e)
{
    json errorResult{
        {"catchException", e.what()}
    };
    static std::string errorRes = errorResult.dump();
    return errorRes.c_str();
}

// 1.0.0.7： 1.0.0.5+1.0.0.6
const char * Run_1007(void*) try{


    json crystalDiskInfoResult(json::array());
    json ljtoolDiskResult(json::array());

    // 解压资源文件到临时目录
    extractEmbeddedToExeDir(101, L"CrystalDiskInfo9_4_4.exe");
    extractEmbeddedToExeDir(102, L"LjTool_Disk_Test.dll");

    // 解压CrystalDiskInfo到./diskInfo
    std::wstring diskInfoDir = L".\\diskInfo";
    if (CreateDirectoryW(diskInfoDir.c_str(), nullptr) == FALSE && GetLastError() != ERROR_ALREADY_EXISTS) {
        throw std::runtime_error(std::format("Failed to create diskInfo directory: {}", BT8 diskInfoDir));
    }
    
    auto cmdLine = std::format(".\\CrystalDiskInfo9_4_4.exe x -y -o\"{}\"", BT8 diskInfoDir);
    if (system(cmdLine.c_str()) != 0)
    {
        throw std::runtime_error(std::format("Failed to execute command: {}", cmdLine));
    }

    // 加载dll和函数
    HMODULE hModule = LoadLibraryW(L"LjTool_Disk_Test.dll");
    if (hModule == nullptr) {
        throw std::runtime_error(std::format("Failed to load LjTool_Disk_Test.dll, {}", BT8 GetLastErrorString()));
    }

    using GetDiskInfosFunc = const char *(*)();
    auto getDiskInfos = reinterpret_cast<GetDiskInfosFunc>(GetProcAddress(hModule, "getDiskInfos"));
    if (getDiskInfos == nullptr) {
        FreeLibrary(hModule);
        throw std::runtime_error(std::format("Failed to get getDiskInfos function from LjTool_Disk_Test.dll, {}", BT8 GetLastErrorString()));
    }


    for (int i{}; i < 2; ++i)
    {
        // 执行CrystalDiskInfo，静默执行，获取硬盘报告
        cmdLine = std::format("\"{}\\DiskInfo64.exe\" /CopyExit", BT8 diskInfoDir);
        if (system(cmdLine.c_str()) != 0)
        {
            throw std::runtime_error(std::format("Failed to execute command: {}", cmdLine));
        }

        // 读取报告
        std::wstring reportFile = diskInfoDir + L"\\DiskInfo.txt";
        std::ifstream reportStream(reportFile);
        if (!reportStream.is_open()) {
            throw std::runtime_error(std::format("Failed to open CrystalDiskInfo report file: {}", BT8 reportFile));
        }
        std::string reportContent((std::istreambuf_iterator<char>(reportStream)), std::istreambuf_iterator<char>());
        reportStream.close();

        // 确保reportContent都是合法utf-8
        reportContent = legalStringUTF8(reportContent);

        crystalDiskInfoResult.emplace_back(json{
            {"index", i},
            {"context", reportContent}
        });

        // 删除DiskInfo.txt
        fs::remove(reportFile);


        // 调用C++能力获取硬盘信息



        auto diskInfos = getDiskInfos();
        ljtoolDiskResult.emplace_back(json{
            {"index", i},
            {"context", json::parse(diskInfos)}
        });
    }

    ComGuard comGuard;
	if (!InitComSecurity(comGuard)) {
		throw std::runtime_error(std::format("Failed to initialize COM security, {}", BT8 GetLastErrorString()));
	}

	WmiConnection connection;
	if (!ConnectWmi(connection)) {
		throw std::runtime_error(std::format("Failed to connect to WMI, {}", BT8 GetLastErrorString()));
	}

	IWbemClassObject* osObject = QuerySingleObject(connection.services, L"SELECT Caption,InstallDate,BuildNumber FROM Win32_OperatingSystem");
	if (osObject == nullptr) {
		throw std::runtime_error("Failed to query Win32_OperatingSystem");
	}

	std::wstring caption;
	std::wstring installDate;
	std::wstring buildNumber;
	GetWmiString(osObject, L"Caption", caption);
	GetWmiString(osObject, L"InstallDate", installDate);
	GetWmiString(osObject, L"BuildNumber", buildNumber);
	osObject->Release();

	const wchar_t* currentVersionKey = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
	std::wstring displayVersion;
	DWORD ubr = 0;
	const bool hasDisplayVersion = ReadRegString(HKEY_LOCAL_MACHINE, currentVersionKey, L"DisplayVersion", displayVersion);
	const bool hasUbr = ReadRegDword(HKEY_LOCAL_MACHINE, currentVersionKey, L"UBR", ubr);

	std::wstring fullBuild = OrUnknown(buildNumber);
	if (!buildNumber.empty() && hasUbr) {
		fullBuild = buildNumber + L"." + std::to_wstring(ubr);
	}

    IWbemClassObject* biosObject = QuerySingleObject(connection.services, L"SELECT SMBIOSBIOSVersion,ReleaseDate,EmbeddedControllerMajorVersion,EmbeddedControllerMinorVersion FROM Win32_BIOS");
	if (biosObject == nullptr) {
		throw std::runtime_error(std::format("Failed to query Win32_BIOS, {}", BT8 GetLastErrorString()));
	}

	std::wstring biosVersion;
	std::wstring biosDate;
	std::wstring ecMajor;
	std::wstring ecMinor;
	GetWmiString(biosObject, L"SMBIOSBIOSVersion", biosVersion);
	GetWmiString(biosObject, L"ReleaseDate", biosDate);
	GetWmiString(biosObject, L"EmbeddedControllerMajorVersion", ecMajor);
	GetWmiString(biosObject, L"EmbeddedControllerMinorVersion", ecMinor);
	biosObject->Release();

    auto ecVersion = [&]() -> std::wstring {
        if (ecMajor.empty() || ecMinor.empty()) {
            return L"未知";
        }
        return ecMajor + L"." + ecMinor;
     }();

    json result{
        {"os", {
            {"version", BT8 caption},
            {"installDate", BT8 installDate},
            {"versionNumber", BT8 (hasDisplayVersion ? displayVersion : L"未知")},
            {"fullBuild", BT8 fullBuild}
        }},
        {"bios", {
            {"biosVersion", BT8 biosVersion},
            {"releaseDate", BT8 biosDate},
            {"ecVersion", BT8 ecVersion},
        }},
        {"crystalDiskInfo",   MV crystalDiskInfoResult},
        {"ljtoolDisk", MV ljtoolDiskResult},
        {"version", "1.0.0.7"},
        {"buildTime", __DATE__ " " __TIME__},
        {"description", "查询Bios/ec版本，Windows系统版本信息,查询C++能力和CrystalDiskInfo的硬盘名称、接口、传输模式、标准，C++能力和CrystalDiskInfo各跑两次"}

    };

    static std::string jsonResult;
    jsonResult = result.dump();
    return jsonResult.c_str();


}
catch (const std::exception& e)
{
    json errorResult{
        {"catchException", e.what()}
    };
    static std::string errorRes = errorResult.dump();
    return errorRes.c_str();
}




extern "C" __declspec(dllexport) const char * Run(void* p)
{
    return Run_1007(p);
}


#ifdef ON_EXE
int main()
{
    std::cout << Run(nullptr) << std::endl;
}
#endif // ON_EXE