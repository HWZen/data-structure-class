#include <windows.h>
#include <shellapi.h>
#include <ShlObj.h>
#include <shobjidl_core.h>
#include <exdisp.h>
#include <comdef.h>

#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")

// 窗口信息结构体
struct WindowInfo {
    HWND hWnd;                  // 窗口句柄
    std::wstring path;          // 文件夹路径
    std::chrono::steady_clock::time_point creationTime;  // 创建时间
    std::chrono::steady_clock::time_point lastActiveTime; // 最后活动时间
    bool isBeingMonitored;      // 是否处于监控中
};

// 获取所有资源管理器窗口（标准做法：IShellWindows）
std::vector<IWebBrowser2*> GetAllExplorerWindows() {
    std::vector<IWebBrowser2*> browsers;
    CoInitialize(nullptr);
    IShellWindows* pShellWindows = nullptr;
    if (SUCCEEDED(CoCreateInstance(CLSID_ShellWindows, nullptr, CLSCTX_ALL, IID_IShellWindows, (void**)&pShellWindows))) {
        long count = 0;
        pShellWindows->get_Count(&count);
        for (long i = 0; i < count; ++i) {
            VARIANT vIndex;
            vIndex.vt = VT_I4;
            vIndex.lVal = i;
            IDispatch* pDisp = nullptr;
            if (SUCCEEDED(pShellWindows->Item(vIndex, &pDisp)) && pDisp) {
                IWebBrowser2* pBrowser = nullptr;
                if (SUCCEEDED(pDisp->QueryInterface(IID_IWebBrowser2, (void**)&pBrowser)) && pBrowser) {
                    browsers.push_back(pBrowser);
                }
                pDisp->Release();
            }
        }
        pShellWindows->Release();
    }
    return browsers;
}

// 获取资源管理器窗口的当前路径（标准做法）
std::wstring GetExplorerWindowPath(IWebBrowser2* pBrowser) {
    std::wstring path;
    VARIANT v;
    VariantInit(&v);
    if (SUCCEEDED(pBrowser->get_Document(&v.pdispVal)) && v.pdispVal) {
        IServiceProvider* pServiceProvider = nullptr;
        if (SUCCEEDED(v.pdispVal->QueryInterface(IID_IServiceProvider, (void**)&pServiceProvider)) && pServiceProvider) {
            IShellBrowser* pShellBrowser = nullptr;
            if (SUCCEEDED(pServiceProvider->QueryService(SID_STopLevelBrowser, IID_IShellBrowser, (void**)&pShellBrowser)) && pShellBrowser) {
                IShellView* pShellView = nullptr;
                if (SUCCEEDED(pShellBrowser->QueryActiveShellView(&pShellView)) && pShellView) {
                    IFolderView* pFolderView = nullptr;
                    if (SUCCEEDED(pShellView->QueryInterface(IID_PPV_ARGS(&pFolderView))) && pFolderView) {
                        IPersistFolder2* pPersistFolder = nullptr;
                        if (SUCCEEDED(pFolderView->GetFolder(IID_PPV_ARGS(&pPersistFolder))) && pPersistFolder) {
                            LPITEMIDLIST pidl = nullptr;
                            if (SUCCEEDED(pPersistFolder->GetCurFolder(&pidl)) && pidl) {
                                WCHAR pathBuffer[MAX_PATH];
                                if (SHGetPathFromIDListW(pidl, pathBuffer)) {
                                    path = pathBuffer;
                                }
                                CoTaskMemFree(pidl);
                            }
                            pPersistFolder->Release();
                        }
                        pFolderView->Release();
                    }
                    pShellView->Release();
                }
                pShellBrowser->Release();
            }
            pServiceProvider->Release();
        }
        v.pdispVal->Release();
    }
    return path;
}

// 关闭重复路径的资源管理器窗口，只保留一个
void CloseDuplicateExplorerWindows() {
    std::vector<IWebBrowser2*> browsers = GetAllExplorerWindows();
    std::map<std::wstring, IWebBrowser2*> pathToBrowser;
    for (IWebBrowser2* pBrowser : browsers) {
        std::wstring path = GetExplorerWindowPath(pBrowser);
        if (path.empty()) {
            pBrowser->Release();
            continue;
        }
        if (pathToBrowser.count(path)) {
            // 关闭重复窗口
            pBrowser->Quit();
            pBrowser->Release();
        } else {
            pathToBrowser[path] = pBrowser;
        }
    }
    // 释放保留的窗口
    for (auto& kv : pathToBrowser) {
        kv.second->Release();
    }
    CoUninitialize();
}

int main()
{
    CloseDuplicateExplorerWindows();
}