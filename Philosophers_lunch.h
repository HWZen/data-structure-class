#include <windows.h>

class forks // 将五个叉子封装成一个类，并设置阻塞信号，同一时间只能有一个人访问和修改叉子的状态
{
private:
    bool FORKS[5];
    bool semaphore = 1;
    void down()
    {
        while(!semaphore)
            Sleep(1);
        semaphore = 0;
    };
    void up() { semaphore = 1; };

public:
    forks()
    {
        for (int i = 0; i < 5;i++)
            FORKS[i] = 1;
    };
    ~forks(){};

    bool begin_use_forks(int i, int j);
    bool end_use_forks(int i, int j);
};

bool forks::begin_use_forks(int i, int j)
{
    down();
    if(FORKS[i]!=1 || FORKS[j]!=1)
        return false;
    else
    {
        FORKS[i] = FORKS[j] = 0;
        return true;
    }
    up();
}

bool forks::end_use_forks(int i, int j)
{
    down();
    FORKS[i] = FORKS[j] = 1;
    up();
}

