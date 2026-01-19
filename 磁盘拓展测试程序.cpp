#include "nlohmann/json.hpp"
#include "cppUtil/tools.h"

#include <sys/stat.h>
#include <windows.h>
#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <format>
#include <wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "comsuppw.lib")
using nlohmann::json;

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
	if (RegSetValueExW(hKey, key.c_str(), 0, REG_SZ, (const BYTE*)value.c_str(), (value.size()+1)*sizeof(wchar_t)) != ERROR_SUCCESS) {
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

// ...existing code...

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

// 示例主函数
// int main() {
//     std::cout << "Current Windows Update status: " << GetWindowsUpdateStatus() << std::endl;
//     PauseWindowsUpdate(24); // 暂停 24 小时
//     // ResumeWindowsUpdate();
//     std::cout << "Current Windows Update status: " << GetWindowsUpdateStatus() << std::endl;
//     // ResumeWindowsUpdate(); // 恢复更新
//     return 0;
// }

extern "C" __declspec(dllexport) const char * Run(void*) try
{
    json result;
    bool status = GetWindowsUpdateStatus();
    result["defaultState"] = status;
    if (status)
    {
        result["DisableOperator"] = PauseWindowsUpdate(24 * 15);
        result["QureyAfterDisable"] = GetWindowsUpdateStatus();
        result["EnableOperator"] = ResumeWindowsUpdate();
        result["QureyAfterEnable"] = GetWindowsUpdateStatus();
    } else {
        result["EnableOperator"] = ResumeWindowsUpdate();
        result["QureyAfterEnable"] = GetWindowsUpdateStatus();
        result["DisableOperator"] = PauseWindowsUpdate(24 * 15);
        result["QureyAfterDisable"] = GetWindowsUpdateStatus();
    }

    // 查询系统激活状态
    result["activationStatus"] = systemActivationStatus();

    static std::string res = result.dump();
    return res.c_str();
}
catch (const std::exception& e)
{
    json errorResult{
        {"catchException", e.what()}
    };
    static std::string res = errorResult.dump();
    return res.c_str();
}