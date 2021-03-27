#include <iostream>
#include <Windows.h>
#include <Xinput.h>
using namespace std;

#pragma comment(lib, "Xinput.lib")
#pragma comment(lib, "Xinput9_1_0.lib")

int main()
{
    DWORD dwResult;
    XINPUT_BATTERY_INFORMATION state;
    for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
    {
        ZeroMemory(&state, sizeof(XINPUT_BATTERY_INFORMATION));

        if (XInputGetBatteryInformation(i, BATTERY_DEVTYPE_GAMEPAD, &state) == ERROR_SUCCESS)
            cout << "batter level is " << (unsigned long)state.BatteryLevel << endl;
        else
            cout << "Controller is not connected" << endl;
    }
    return 0;
}