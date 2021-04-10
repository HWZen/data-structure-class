#include "bathroom.h"
#include <iostream>
#include <windows.h>
#include <thread>
using namespace std;
bathroom MickeyMouseClubhouse;

void oneMan()
{
    cout << "man will in." << endl;
    MickeyMouseClubhouse.man_wants_to_enter();
    cout << "man in." << endl;
    Sleep(2000);
    MickeyMouseClubhouse.man_leaves();
    cout << "man out." << endl;
}

void oneWoman()
{
    cout << "woman will in." << endl;
    MickeyMouseClubhouse.woman_wants_to_enter();
    cout << "woman in" << endl;
    Sleep(4000);
    MickeyMouseClubhouse.woman_leaves();
    cout << "woman out." << endl;
}

int main()
{
    thread man1(oneMan);
    thread woman1(oneWoman);
    Sleep(1000);
    thread woman2(oneWoman);
    thread man2(oneMan);
    man1.join();
    woman1.join();
    woman1.join();
    man2.join();
    return 0;
}