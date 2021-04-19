

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
        if(nums<0)// ���������������
        {
            up(nums_mutsx);// ���ͷ�nums��
            down(from_east_to_west_mutex);// ����down�����𣬵ȴ�������
            down(nums_mutsx);
            nums++; // ���Ѻ�ȡ��nums����+1
            up(nums_mutsx);
            up(from_east_to_west_mutex);// ������һ����������Զ��������̣�û�оͽ�����Ϊһ
        }
        else if(nums==0)// �������û����
        {
            down(from_west_to_east_mutex);// ��ȡ�ö�����������
            nums++;
            up(nums_mutsx);// nums+1��Ȼ���ͷ�nums��
        }
        else
            up(nums_mutsx);// ���nums>0���ͷ�nums����ֱ�ӹ���


        // ����


        down(nums_mutsx);
        nums--;// �����ţ�nums-1
        if(nums==0)// ��������ź�����û���ˣ�
        {
            up(nums_mutsx);
            up(from_west_to_east_mutex);// �Ⱥ��ͷ�nums���Ͷ�����������
        }
        else
            up(nums_mutsx);
    }

    void i_want_to_cross_the_bridge_from_west_to_east()
    {
        // ǰ���ж��Ƿ��ܹ��ŵ��߼���������
        down(nums_mutsx);
        if (nums < 0) 
        {
            up(nums_mutsx);                
            down(from_west_to_east_mutex); 
            down(nums_mutsx);
            nums++; 
            up(nums_mutsx);
            // up(from_west_to_east_mutex); ����������ͷ�
        }
        else if (nums == 0) 
        {
            down(from_east_to_west_mutex);
            down(from_west_to_east_mutex);// ��ȡ������
            nums--;
            up(nums_mutsx);
        }
        else
        {
            up(nums_mutsx);
            down(from_west_to_east_mutex);
        }

        // ����

        down(nums_mutsx);
        nums++;
        up(nums_mutsx);
        up(from_east_to_west_mutex);
        up(from_west_to_east_mutex);// �ͷ�������
    }

};


