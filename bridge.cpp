

typedef int mutex;
#define down(x)   \
    while (x < 1) \
    {             \
    }             \
    x--

#define up(x) x++

class bridge
{
private:
    mutex from_east_to_west_mutex;
    mutex from_west_to_east_mutex;
    mutex nums_mutsx;
    int nums;

public:
    void i_want_to_cross_the_bridge_from_east_to_west()
    {
        down(nums_mutsx);
        if(nums<0)// 如果现在是自西向东
        {
            up(nums_mutsx);// 先释放nums锁
            down(from_east_to_west_mutex);// 进入down，挂起，等待被唤醒
            down(nums_mutsx);
            nums++; // 唤醒后取得nums锁，+1
            up(nums_mutsx);
            up(from_east_to_west_mutex);// 唤醒另一个被挂起的自东向西进程，没有就将锁置为一
        }
        else if(nums==0)// 如果桥上没有人
        {
            down(from_west_to_east_mutex);// 先取得对面自西向东锁
            nums++;
            up(nums_mutsx);// nums+1，然后释放nums锁
        }
        else
            up(nums_mutsx);// 如果nums>0，释放nums锁，直接过桥


        // 过桥


        down(nums_mutsx);
        nums--;// 过完桥，nums-1
        if(nums==0)// 如果过完桥后桥上没人了，
        {
            up(nums_mutsx);
            up(from_west_to_east_mutex);// 先后释放nums锁和对面自西向东锁
        }
        else
            up(nums_mutsx);
    }

    void i_want_to_cross_the_bridge_from_west_to_east()
    {
        // 前面判断是否能过桥的逻辑基本不变
        down(nums_mutsx);
        if (nums < 0) 
        {
            up(nums_mutsx);                
            down(from_west_to_east_mutex); 
            down(nums_mutsx);
            nums++; 
            up(nums_mutsx);
            // up(from_west_to_east_mutex); 获得锁后不再释放
        }
        else if (nums == 0) 
        {
            down(from_east_to_west_mutex);
            down(from_west_to_east_mutex);// 获取两把锁
            nums--;
            up(nums_mutsx);
        }
        else
        {
            up(nums_mutsx);
            down(from_west_to_east_mutex);
        }

        // 过桥

        down(nums_mutsx);
        nums++;
        up(nums_mutsx);
        up(from_east_to_west_mutex);
        up(from_west_to_east_mutex);// 释放两把锁
    }

};


