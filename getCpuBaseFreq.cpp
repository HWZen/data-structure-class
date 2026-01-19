/********************************************************************
created:	2022/01/26
created:	26:1:2022   10:23
filename: 	HardwareInfo\CPU\CPUFrequency.h
file path:	HardwareInfo\CPU
file base:	CPUFrequency
file ext:	h
author:		HUANG QIANG

purpose:	cpu 频率相关
*********************************************************************/
#pragma once
#include <Windows.h>
#include <MMSystem.h>
#include <cmath>
#pragma comment(lib, "Winmm.lib")

class CAdjustPriority
{
public:
CAdjustPriority()
    : dwPriorityClass(GetPriorityClass(GetCurrentProcess()))
      , dwThreadPriority(GetThreadPriority(GetCurrentThread()))
{
    SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
}
~CAdjustPriority()
{
    SetPriorityClass(GetCurrentProcess(), dwPriorityClass);
    SetThreadPriority(GetCurrentThread(), dwThreadPriority);
}

private:
DWORD dwPriorityClass;
DWORD dwThreadPriority;
};

class CCpuFrequency
{
public:
static int GetCPUSpeed( void )
{
    double fTmpDouble = GetCpuDoubleSpeed(500);

    int nTmpFreq = (int)hardware::utils::BankerRound(fTmpDouble / 1000 );

    int nTempOldFreq = GetRealFreq();
    int nFrequency = nTempOldFreq < nTmpFreq ? nTmpFreq : nTempOldFreq;

    LOGW(L"CCpuInfo::GetCPUSpeed: %dMHz, Freq: %dMHz, RealFreq: %dMHz",
         nFrequency, nTmpFreq,nTempOldFreq);

    return nFrequency;
}
private:
static double GetCpuDoubleSpeed(DWORD msTime)
{
    if (msTime == 0 ) return 0.;

    TIMECAPS timeCaps = {};
    if (timeGetDevCaps(&timeCaps, sizeof(timeCaps)) != TIMERR_NOERROR) return 0;

    unsigned __int64 llStart = 0;
    double fResult = 0.;

    {
        CAdjustPriority autoAdjust;

        timeBeginPeriod(timeCaps.wPeriodMax);
        DWORD dwStart = timeGetTime();
        llStart = __rdtsc();

        while ((timeGetTime() - dwStart) < msTime);

        unsigned __int64 llStop = __rdtsc();
        timeEndPeriod(timeCaps.wPeriodMax);

        fResult = (llStop - llStart) / (double)msTime;
    }

    double bf1 = 1000 * 50.;
    double bf2 = 1000 * 66.66666;
    double fMinErr = fResult;

    double fRatio = (double)hardware::utils::BankerRound(fResult / bf1);
    double fBestRatio = fRatio;
    double fBestBf = bf1;
    double fTErr = (fRatio * bf1) - fResult;
    if (fTErr < fMinErr)
    {
        fMinErr = fTErr;
        fBestRatio = fRatio;
        fBestBf = bf1;
    }

    fRatio -= 1;
    fTErr = fResult - (fRatio * bf1);
    if (fTErr < fMinErr)
    {
        fMinErr = fTErr;
        fBestRatio = fRatio;
        fBestBf = bf1;
    }

    fRatio = (double)hardware::utils::BankerRound(fResult / bf2);//51
    fTErr = fRatio * bf2 - fResult;
    if (fTErr < fMinErr)
    {
        fMinErr = fTErr;
        fBestRatio = fRatio;
        fBestBf = bf2;
    }

    fRatio -= 1;
    fTErr = fResult - fRatio * bf2;
    if (fTErr < fMinErr)
    {
        fBestRatio = fRatio;
        fBestBf = bf2;
    }
    fResult = fBestRatio * fBestBf;

    return fResult;
}

static int GetRealFreq( void )
{
    LARGE_INTEGER lgTicksCount = {};
    LARGE_INTEGER lgCurrTicks = {};
    if (QueryPerformanceFrequency(&lgTicksCount))
    {
        CAdjustPriority autoAdjustor;

        QueryPerformanceFrequency(&lgTicksCount);
        QueryPerformanceCounter(&lgCurrTicks);

        lgTicksCount.QuadPart /= 16;
        lgTicksCount.QuadPart += lgCurrTicks.QuadPart;

        unsigned __int64 lltsc = __rdtsc();

        while (lgCurrTicks.QuadPart < lgTicksCount.QuadPart)
        {
            QueryPerformanceCounter(&lgCurrTicks);
        }

        lltsc = __rdtsc() - lltsc;

        return static_cast<int>(ceil(lltsc / 62500.));
    }
    else
    {
        CAdjustPriority autoAdjustor;

        unsigned __int64 llStart = __rdtsc();
        unsigned __int64 llEnd = __rdtsc();

        DWORD dwDiff = DWORD(llEnd - llStart);
        // 原始代码
        // DWORD TimerHi, TimerLo;
        // 		_asm
        // 		{
        // 			dw  0x310F
        // 			mov TimerLo, eax
        // 			mov TimerHi, edx
        // 		}
        // 		_asm
        // 		{
        // 			dw  0x310F
        // 			sub eax, TimerLo
        // 			sbb edx, TimerHi
        // 			mov TimerLo, eax
        // 			mov TimerHi, edx
        // 		}
        //return static_cast<int>(TimerLo / (1000.0 * 500));

        return static_cast<int>(dwDiff / (1000.0 * 500));
    }
}
};