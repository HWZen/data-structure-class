#pragma once
#include <Windows.h>

class bathroom
{
private:
    int nums = 0;
    bool semaphone_for_nums = 1;
    void up() { semaphone_for_nums = 1; };
    void down()
    { 
        while (semaphone_for_nums != 1)
            Sleep(1);
        semaphone_for_nums = 0;
    }

public:
    bathroom(){};
    ~bathroom(){};
    bool isEmpty()
    {
        down();
        bool res = nums == 0;
        up();
        return res;
    };
    bool isMen()
    {
        down();
        bool res = nums > 0;
        up();
        return res;
    };
    bool isWomen()
    {
        down();
        bool res = nums < 0;
        up();
        return res;
    };
    void woman_wants_to_enter();
    void man_wants_to_enter();
    void woman_leaves();
    void man_leaves();
};

void bathroom::man_wants_to_enter()
{
    while(isWomen())
        Sleep(1);
    down();
    nums++;
    up();
}

void bathroom::woman_wants_to_enter()
{
    while(isMen())
        Sleep(1);
    down();
    nums--;
    up();
}

void bathroom::man_leaves()
{
    down();
    nums--;
    up();
}

void bathroom::woman_leaves()
{
    down();
    nums++;
    up();
}
