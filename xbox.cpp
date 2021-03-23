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

#define SERVER_ADDRESS "192.168.1.181" //��������IP��ַ
#define DEFAULT_PORT 1234              //�������Ķ˿ں�
#define MSGSIZE 1024                   //�շ��������Ĵ�С

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
            // �����ͻ����׽���
            SOCKET sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //AF_INETָ��ʹ��TCP/IPЭ���壻
                                                                        //SOCK_STREAM, IPPROTO_TCP����ָ��ʹ��TCPЭ��
            // ָ��Զ�̷������ĵ�ַ��Ϣ(�˿ںš�IP��ַ��)
            SOCKADDR_IN server;
            memset(&server, 0, sizeof(SOCKADDR_IN)); //�Ƚ������ַ��server��Ϊȫ0
            server.sin_family = PF_INET;             //������ַ��ʽ��TCP/IP��ַ��ʽ
            int port = DEFAULT_PORT;
            server.sin_port = htons(port);                         //ָ�����ӷ������Ķ˿ںţ�htons()���� converts values between the host and network byte order
            server.sin_addr.s_addr = inet_addr(Real_Addr.c_str()); //ָ�����ӷ�������IP��ַ
                                                                   //�ṹSOCKADDR_IN��sin_addr�ֶ����ڱ���IP��ַ��sin_addr�ֶ�Ҳ��һ���ṹ�壬sin_addr.s_addr�������ձ���IP��ַ
                                                                   //inet_addr()���ڽ� �����"127.0.0.1"�ַ���ת��ΪIP��ַ��ʽ
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