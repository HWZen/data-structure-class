#include <iostream>
#include <map>
#include <stack>
#include <vector>
using namespace std;

/*节点数*/
#define Vertex_num 11
#define V_num Vertex_num

/* 录入边 */
bool unsign_edges[Vertex_num][Vertex_num] = {
/*A*/    {0,0,1,1,},
/*B*/    {0,0,1,0,1},
/*C*/    {1,1,0,1,0,1},
/*D*/    {1,0,1},
/*E*/    {0,1,0,0,0,1,0,1,1},
/*F*/    {0,0,1,0,1,0,1},
/*G*/    {0,0,0,0,0,1},
/*H*/    {0,0,0,0,1,0,0,0,0,1},
/*I*/    {0,0,0,0,1,0,0,0,0,0,1},
/*J*/    {0,0,0,0,0,0,0,1,0,0,1},
/*K*/    {0,0,0,0,0,0,0,0,1,1,0}
    };


/* DFS类 */
class DFS
{
private:
    int son[Vertex_num];
    int father[Vertex_num];
    int Num[Vertex_num];
    int Low[Vertex_num];
    stack<int> DFS_stack; // 用于遍历的堆
    void Num_Low_Init(); // Num，Low数据初始化
    void Build_Low(int it,int low); // 更新Low

public:
    DFS(); // 构造时便完成了所有计算
    ~DFS(){}
    bool Is_cut_point(int V); // 割点判断
    int *get_low() { return Low; }
    int *get_num() { return Num; }
};

void DFS::Num_Low_Init()
{
    for (int i = 0;i<V_num;i++)
    {
        Num[i] = Low[i] = -1;
        father[i] = son[i] = -1;
    }
    father[0] = 0;
}

void DFS::Build_Low(int end,int low)
{
    int it = end;
    while (Num[it] != Num[low])
    {
        Low[it] = Num[low];
        it = father[it];
    }
}

bool DFS::Is_cut_point(int V)
{
    for (int i = 0; i < V_num;i++)
        if (unsign_edges[V][i] && Num[V] < Num[i] && Low[V]!=Low[i])
            return true;
    return false;
}

DFS::DFS()
{
    /* 构造完成，计算完成 */
    Num_Low_Init();

    int it = 0;
    int cnt = 0;
    do
    {
        if(DFS_stack.empty())
            DFS_stack.push(it);
        else if(DFS_stack.top()!=it)
            DFS_stack.push(it);
        int next = it;
        for (int i = 0; i < V_num; i++)
        {
            if(i ==father[it]) continue;
            if(unsign_edges[it][i])
            {
                if(Num[i]!=-1)
                {
                    if((( Num[i] < Num[it]) && (Low[it]!=i)) || Num[it] == -1)
                        Build_Low(it, i);
                    continue;
                }
                next = i;
                break;
            }
        }

        Low[it] = (Low[it] == -1) ? cnt : Low[it];
        Num[it] = (Num[it] == -1) ? cnt++ : Num[it];

        if (next == it)
        {
            DFS_stack.pop();
            it = (DFS_stack.empty()) ? 0 : DFS_stack.top();
        }
        else
        {
            son[it] = next;
            father[next] = it; 
            it = next;
        }

    } while (!DFS_stack.empty());
}

int main()
{
    DFS dfs;

    cout<<"Num: "<<endl;
    for (int i = 0; i < V_num; i++)
        cout<< dfs.get_num()[i]<<" ";
    cout << endl << endl;

    cout << "Low: " << endl;
    for (int i = 0; i < V_num; i++)
        cout << dfs.get_low()[i] << " ";

    cout << endl << endl;

    cout << "find cut point:" << endl;
    for (int i = 0; i < V_num; i++)
        cout << i << ": " << ((dfs.Is_cut_point(i)) ? "Is cut point." : "Is not a cut point.") << endl;
    return 0;
}