#include <windows.h>
#include <string>
#include <iostream>
using namespace std;

class memeryshare
{
private:
    HANDLE hmutex;
    HANDLE hMapFile;
    int buf_size;
    string sharename;
    LPVOID lpBase;

public:
    memeryshare(UINT32 Buf_size, string ShareName);
    ~memeryshare();

    void write(string str);
    string read();

    void lock(uint32_t time);
};

memeryshare::memeryshare(UINT32 Buf_size, string ShareName)
{
    buf_size = Buf_size;
    sharename = ShareName;
    hmutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, (ShareName + "_mutex").c_str()); //打开进程锁
    if (hmutex == NULL)
        hmutex = CreateMutex(NULL, false, (ShareName + "_mutex").c_str()); //创建进程锁
    else
        cerr << "Muxtex existed." << endl;

    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE, // 物理文件句柄
        NULL,                 // 默认安全级别
        PAGE_READWRITE,       // 可读可写
        0,                    // 高位文件大小
        buf_size,             // 地位文件大小
        sharename.c_str()     // 共享内存名称
    );

    // 映射缓存区视图 , 得到指向共享内存的指针
    lpBase = MapViewOfFile(
        hMapFile,            // 共享内存的句柄
        FILE_MAP_ALL_ACCESS, // 可读写许可
        0,
        0,
        buf_size);
}


memeryshare::~memeryshare()
{
    // 解除文件映射
    UnmapViewOfFile(lpBase);
    // 关闭内存映射文件对象句柄
    CloseHandle(hMapFile);

    if (hmutex != NULL)
        CloseHandle(hmutex);
}

void memeryshare::write(string str)
{
    DWORD ts = WaitForSingleObject(hmutex, INFINITE); //获取进程锁
    strcpy_s((char *)lpBase,buf_size, str.c_str());
    ReleaseMutex(hmutex); //释放锁
}

string memeryshare::read()
{
    string res;
    DWORD ts = WaitForSingleObject(hmutex, INFINITE); //获取进程锁
    res = (char *)lpBase;
    ReleaseMutex(hmutex); //释放锁
    return res;
}

void memeryshare::lock(uint32_t time)
{
    DWORD ts = WaitForSingleObject(hmutex, INFINITE); //获取进程锁
    Sleep(time);
    ReleaseMutex(hmutex); //释放锁
}
