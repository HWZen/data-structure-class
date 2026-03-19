#pragma once
#include "cppUtil/tools.h"

#include <Windows.h>
#include <cstdint>
#include <iostream>

using FN_IsInpOutDriverOpen = uint32_t (__stdcall*)();
using FN_Out32              = void     (__stdcall*)(int, int);
using FN_Inp32              = uint8_t  (__stdcall*)(int);

using FN_DlPortWritePortUshort = void     (__stdcall*)(short, uint16_t);
using FN_DlPortReadPortUshort  = uint16_t (__stdcall*)(short);

using FN_DlPortWritePortUlong  = void     (__stdcall*)(int, uint32_t);
using FN_DlPortReadPortUlong   = uint32_t (__stdcall*)(int);

using FN_GetPhysLong = BOOL (__stdcall*)(int*, uint32_t*);
using FN_SetPhysLong = BOOL (__stdcall*)(int*, uint32_t*);


class ECInterface
{
public:
    ECInterface();
    ~ECInterface();

    bool IsValid() const { return nResult != 0; }

    uint32_t LPC_Read(uint16_t addr);
    void     LPC_Write(uint32_t addr, uint32_t data);

    void     ITE_WRITE(uint32_t addr, uint32_t data);
    void     ITE_WRITE_WORD(uint32_t addr, uint16_t data);

    uint32_t ITE_READ(uint32_t addr);
    uint32_t ITE_READ_WORD(uint32_t addr);


    int      ITE_GET_PORT();

private:
    bool LoadIoDll();
    void UnloadIoDll();

private:
    // ---- io.dll handle ----
    HMODULE ioDll = nullptr;

    // ---- function pointers ----
    FN_IsInpOutDriverOpen      pIsInpOutDriverOpen = nullptr;
    FN_Out32                  pOut32 = nullptr;
    FN_Inp32                  pInp32 = nullptr;

    FN_DlPortWritePortUshort  pDlPortWritePortUshort = nullptr;
    FN_DlPortReadPortUshort   pDlPortReadPortUshort = nullptr;
    FN_DlPortWritePortUlong   pDlPortWritePortUlong = nullptr;
    FN_DlPortReadPortUlong    pDlPortReadPortUlong = nullptr;

    FN_GetPhysLong            pGetPhysLong = nullptr;
    FN_SetPhysLong            pSetPhysLong = nullptr;

private:
    uint32_t nResult = 0;
    bool     DRIVER_OK = false;
    int      ECLPC_IO = 78;
};

class EneIoClass
{
public:
    EneIoClass(){
        LoadEneIoDll();

        nResult = pIsInpOutDriverOpen ? pIsInpOutDriverOpen() : 0;
        std::cerr << "init nResult: " << nResult << std::endl;
    }
    ~EneIoClass(){
        UnloadEneIoDll();
    }

    void IndexIO_SetRegValue(int address, int offset, byte dat)
    {

        pOut32(address + 1, (offset & 65280) >> 8);
        pOut32(address + 2, offset & 255);
        pOut32(address + 3, (int)dat);
        return;
    }


private:
    HMODULE eneIoDll = nullptr;
    void LoadEneIoDll(){
        eneIoDll = LoadLibraryW(L"inpout32.dll");
        if (!eneIoDll)
        {
            std::wcerr << "load EneIo.dll failed: " << GetLastError() << std::endl;
            return;
        }
        auto GP = [&](const char* name)
        {
            return GetProcAddress(eneIoDll, name);
        };
        pOut32              = (FN_Out32)GP("Out32");
        pInp32              = (FN_Inp32)GP("Inp32");
        pIsInpOutDriverOpen = (FN_IsInpOutDriverOpen)GP("IsInpOutDriverOpen");
    };
    void UnloadEneIoDll(){
        if (eneIoDll)
        {
            FreeLibrary(eneIoDll);
            eneIoDll = nullptr;
        }
    }
    bool nResult = false;
    FN_IsInpOutDriverOpen pIsInpOutDriverOpen = nullptr;

    FN_Out32 pOut32 = nullptr;
    FN_Inp32 pInp32 = nullptr;

};

//------------------------------------------------------------
// ctor / dtor
//------------------------------------------------------------
ECInterface::ECInterface()
{
    if (!LoadIoDll())
        return;

    nResult = pIsInpOutDriverOpen ? pIsInpOutDriverOpen() : 0;
    std::cerr << "init nResult: " << nResult << std::endl;
}

ECInterface::~ECInterface()
{
    UnloadIoDll();
}

//------------------------------------------------------------
// Load io.dll
//------------------------------------------------------------
bool ECInterface::LoadIoDll()
{
    ioDll = LoadLibraryW(L"io.dll");
    if (!ioDll)
    {
        std::wcerr << "load io.dll failed: " << GetLastError() << std::endl;
        return false;
    }


    auto GP = [&](const char* name)
    {
        return GetProcAddress(ioDll, name);
    };

    pIsInpOutDriverOpen = (FN_IsInpOutDriverOpen)GP("IsInpOutDriverOpen");
    pOut32              = (FN_Out32)GP("Out32");
    pInp32              = (FN_Inp32)GP("Inp32");

    pDlPortWritePortUshort = (FN_DlPortWritePortUshort)GP("DlPortWritePortUshort");
    pDlPortReadPortUshort  = (FN_DlPortReadPortUshort)GP("DlPortReadPortUshort");
    pDlPortWritePortUlong  = (FN_DlPortWritePortUlong)GP("DlPortWritePortUlong");
    pDlPortReadPortUlong   = (FN_DlPortReadPortUlong)GP("DlPortReadPortUlong");

    pGetPhysLong = (FN_GetPhysLong)GP("GetPhysLong");
    pSetPhysLong = (FN_SetPhysLong)GP("SetPhysLong");

    return pIsInpOutDriverOpen && pOut32 && pInp32;
}

//------------------------------------------------------------
void ECInterface::UnloadIoDll()
{
    if (ioDll)
    {
        FreeLibrary(ioDll);
        ioDll = nullptr;
    }
}

//------------------------------------------------------------
// LPC
//------------------------------------------------------------
uint32_t ECInterface::LPC_Read(uint16_t addr)
{
    if (!nResult) return 0;

    pOut32(ECLPC_IO, addr & 0xFF);
    return pInp32(ECLPC_IO + 1);
}

void ECInterface::LPC_Write(uint32_t addr, uint32_t data)
{
    if (!nResult) return;

    pOut32(ECLPC_IO, addr & 0xFF);
    pOut32(ECLPC_IO + 1, data & 0xFF);
}

//------------------------------------------------------------
// ITE
//------------------------------------------------------------
void ECInterface::ITE_WRITE(uint32_t addr, uint32_t data)
{
    LPC_Write(46, 17);
    LPC_Write(47, addr >> 8);

    LPC_Write(46, 16);
    LPC_Write(47, addr);

    LPC_Write(46, 18);
    LPC_Write(47, data);
}

void ECInterface::ITE_WRITE_WORD(uint32_t addr, uint16_t data)
{
    ITE_WRITE(addr,     (data >> 8) & 0xFF);
    ITE_WRITE(addr + 1, data & 0xFF);
}

uint32_t ECInterface::ITE_READ(uint32_t addr)
{
    LPC_Write(46, 17);
    LPC_Write(47, addr >> 8);

    LPC_Write(46, 16);
    LPC_Write(47, addr);

    LPC_Write(46, 18);
    return LPC_Read(47) & 0xFF;
}

uint32_t ECInterface::ITE_READ_WORD(uint32_t addr)
{
    return (ITE_READ(addr) << 8) | ITE_READ(addr + 1);
}

//------------------------------------------------------------
// Detect EC LPC port
//------------------------------------------------------------
int ECInterface::ITE_GET_PORT()
{
    DRIVER_OK = true;

    int ports[] = { 46, 78, 110 };
    for (int p : ports)
    {
        ECLPC_IO = p;
        uint32_t id = ITE_READ(0x2000);
        if (id == 0x85 || id == 0x89 || id == 0x55)
            return p;
    }

    DRIVER_OK = false;
    return 0;
}


int main(int argc, char* argv[])
{
    // IO访问封装类（开源库）
    ECInterface ecInterface;
    EneIoClass eneIoClass;

    // 推测：解锁EC保护（工厂软件初始化时就会执行）
    ecInterface.ITE_WRITE(4192U, 128U);
    ecInterface.ITE_GET_PORT();


    // 判断EC版本，执行不同的写入指令操作
    if (argc > 1 && std::stoi(argv[1]) == 1)
        ecInterface.ITE_WRITE(1031U, 1U); // 均是魔法数字，无法找到相关文档说明
    else if (argc > 1 && std::stoi(argv[1]) == 2)
        ecInterface.ITE_WRITE(50183U, 1U); // 均是魔法数字，无法找到相关文档说明
    else
        eneIoClass.IndexIO_SetRegValue(912, 61447, 1); // 均是魔法数字，无法找到相关文档说明

    system("pause");

}

