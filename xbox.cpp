#include "socketor/socketor.cpp"
#include <iostream>
#include <thread>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <Windows.h>
#include <Xinput.h>
#include <stdio.h>
using namespace std;

#pragma comment(lib, "Xinput.lib")
#pragma comment(lib, "Xinput9_1_0.lib")

#define SERVER_ADDRESS "192.168.1.181" //服务器端IP地址
#define DEFAULT_PORT 1234              //服务器的端口号
#define MSGSIZE 1024                   //收发缓冲区的大小

XINPUT_STATE state;

void verb(DWORD sec);
void verb_src(DWORD sec);

int main(int argc, char **argv)
{

    DWORD dwResult;
    for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
    {
        
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        // Simply get the state of the controller from XInput.
        dwResult = XInputGetState(i, &state);

        if (dwResult == ERROR_SUCCESS)
        {
            string Real_Addr = SERVER_ADDRESS;
            // Initialize Windows socket library
            WSADATA wsaData;
            WSAStartup(0x0202, &wsaData);
            WORD wVersionRequested = 0;
            int err = 0;

            wVersionRequested = MAKEWORD(2, 2);

            err = WSAStartup(wVersionRequested, &wsaData);

            if (err != 0)
                exit(0);

            if (LOBYTE(wsaData.wVersion) != 2 ||
                HIBYTE(wsaData.wVersion) != 2)
            {

                WSACleanup();
                exit(0);
            }
            // 创建客户端套节字
            SOCKET sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //AF_INET指明使用TCP/IP协议族；
                                                                        //SOCK_STREAM, IPPROTO_TCP具体指明使用TCP协议
            // 指明远程服务器的地址信息(端口号、IP地址等)
            SOCKADDR_IN server;
            memset(&server, 0, sizeof(SOCKADDR_IN)); //先将保存地址的server置为全0
            server.sin_family = PF_INET;             //声明地址格式是TCP/IP地址格式
            int port = DEFAULT_PORT;
            server.sin_port = htons(port);                         //指明连接服务器的端口号，htons()用于 converts values between the host and network byte order
            server.sin_addr.s_addr = inet_addr(Real_Addr.c_str()); //指明连接服务器的IP地址
                                                                   //结构SOCKADDR_IN的sin_addr字段用于保存IP地址，sin_addr字段也是一个结构体，sin_addr.s_addr用于最终保存IP地址
                                                                   //inet_addr()用于将 形如的"127.0.0.1"字符串转换为IP地址格式
            if (connect(sClient, (struct sockaddr *)&server, sizeof(SOCKADDR_IN)) < 0)
            {
                cerr << "connect fail." << endl;
                exit(1);
            }
            socketor cli(sClient, server);

            string msg;
            msg.resize(9);
            msg[6] = 2;
            BYTE Last_RT = 0;

            while (dwResult == ERROR_SUCCESS)
            {

                dwResult = XInputGetState(i, &state);
                if (state.Gamepad.sThumbLX > 32700)
                    state.Gamepad.sThumbLX = 32700;
                else if (state.Gamepad.sThumbLX < -32700)
                    state.Gamepad.sThumbLX = -32700;
                
                // verb
                if(msg[6]>=3)
                {
                    if (abs(state.Gamepad.bRightTrigger-Last_RT)>240)
                        verb(250);
                    Last_RT = state.Gamepad.bRightTrigger;
                }
                //

                msg[0] = 123;
                msg[1] = (state.Gamepad.bRightTrigger == 0) ? 1 : (char)state.Gamepad.bRightTrigger;
                msg[2] = *(char *)&state.Gamepad.sThumbLX;
                msg[3] = *(((char *)&state.Gamepad.sThumbLX) + 1);
                msg[4] = *(char *)&state.Gamepad.sThumbLY;
                msg[5] = *(((char *)&state.Gamepad.sThumbLY) + 1);
                if (state.Gamepad.wButtons == 16384)
                    msg[6] = (msg[6] < 4) ? msg[6] + 1 : msg[6];
                else if (state.Gamepad.wButtons == 4096)
                    msg[6] = (msg[6] > 1) ? msg[6] - 1 : msg[6];
                msg[7] = (state.Gamepad.bLeftTrigger == 0) ? 1 : (char)state.Gamepad.bLeftTrigger;
                msg[8] = '\0';
                system("cls");
                cout << "bLeftTrigger:			" << (SHORT)state.Gamepad.bLeftTrigger << endl
                     << "bRightTrigger:			" << (SHORT)state.Gamepad.bRightTrigger << endl
                     << "sThumbLX\\sThumbLY:	" << state.Gamepad.sThumbLX << "\\" << state.Gamepad.sThumbLY << endl
                     << "sThumbRX\\sThumbRY:	" << state.Gamepad.sThumbRX << "\\" << state.Gamepad.sThumbRY << endl
                     << "wButtons:				" << state.Gamepad.wButtons << endl;
                cli.Send(msg);
                Sleep(90);
            }
        }
        else
        {
            cout << "Controller is not connected" << endl;
        }
    }
    return 0;
}

void verb_src(DWORD sec)
{
    XINPUT_VIBRATION vib = {65000, 65000};
    XInputSetState(0, &vib);
    Sleep(sec);
    vib.wLeftMotorSpeed = 0;
    vib.wRightMotorSpeed = 0;
    XInputSetState(0, &vib);
    return;
}

void verb(DWORD sec)
{
    thread th(verb_src, sec);
    th.detach();
    return;
}