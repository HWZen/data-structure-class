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
    hmutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, (ShareName + "_mutex").c_str()); //�򿪽�����
    if (hmutex == NULL)
        hmutex = CreateMutex(NULL, false, (ShareName + "_mutex").c_str()); //����������
    else
        cerr << "Muxtex existed." << endl;

    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE, // �����ļ����
        NULL,                 // Ĭ�ϰ�ȫ����
        PAGE_READWRITE,       // �ɶ���д
        0,                    // ��λ�ļ���С
        buf_size,             // ��λ�ļ���С
        sharename.c_str()     // �����ڴ�����
    );

    // ӳ�仺������ͼ , �õ�ָ�����ڴ��ָ��
    lpBase = MapViewOfFile(
        hMapFile,            // �����ڴ�ľ��
        FILE_MAP_ALL_ACCESS, // �ɶ�д���
        0,
        0,
        buf_size);
}


memeryshare::~memeryshare()
{
    // ����ļ�ӳ��
    UnmapViewOfFile(lpBase);
    // �ر��ڴ�ӳ���ļ�������
    CloseHandle(hMapFile);

    if (hmutex != NULL)
        CloseHandle(hmutex);
}

void memeryshare::write(string str)
{
    DWORD ts = WaitForSingleObject(hmutex, INFINITE); //��ȡ������
    strcpy_s((char *)lpBase,buf_size, str.c_str());
    ReleaseMutex(hmutex); //�ͷ���
}

string memeryshare::read()
{
    string res;
    DWORD ts = WaitForSingleObject(hmutex, INFINITE); //��ȡ������
    res = (char *)lpBase;
    ReleaseMutex(hmutex); //�ͷ���
    return res;
}

void memeryshare::lock(uint32_t time)
{
    DWORD ts = WaitForSingleObject(hmutex, INFINITE); //��ȡ������
    Sleep(time);
    ReleaseMutex(hmutex); //�ͷ���
}
