/* 垃 圾 图 类*/
#include "Graph.h"
#include <iostream>
#include <algorithm>
using namespace std;

/*图*/
Graph G(10);

/* dijkstra算法(一开始不小心把Prime写成dijkstra) */
/*表，[*][0]表示是否被找过，[*][1]表示到根节点的距离，[*][2]表示父节点*/
int tab[10][3];
int find_next_Vertex(); // 找到下一个应该走的节点（到根节点最近的节点）
void tabing_Vertex_edge(int Vertex);// 把节点的各边打印到tab上
bool finish(); // 判断是否全部走完
void dijkstra(); // 算法初始化及入口
/* End dijkstra */



/* Prime算法 */
/* 下列各函数功能和dijkstra基本一致，只是把tab换成tab2 */
int tab2[10][3];
int find_next_Vertex2();
void tabing_Vertex_edge2(int Vertex);
bool finish2();
void Prime();
/* End Prime */


/* Kruskal算法 */
vector<Graph::Edge> KEV; // 储存已选择的边【集】
int pre[10]; // 储存节点的根
bool cnt(Graph::Edge a,Graph::Edge b); // 给std::sort用的判断函数
int Find(int x); // 查找x的根节点【查】
bool Combine(int x, int y); // 将两颗根节点不同的树合并，如果无需合并返回false,否则true 【并】
void Kruskal(); //算法初始化及入口
/* End Kuska */



int main()
{
    //录入边的数据
    G.add_edges(0, 1, 3, 0);
    G.add_edges(0, 4, 4, 0);
    G.add_edges(0, 3, 4, 0);
    G.add_edges(3, 4, 5, 0);
    G.add_edges(3, 7, 6, 0);
    G.add_edges(4, 1, 2, 0);
    G.add_edges(4, 8, 1, 0);
    G.add_edges(4, 7, 2, 0);
    G.add_edges(4, 5, 11, 0);
    G.add_edges(7, 8, 4, 0);
    G.add_edges(1, 2, 10, 0);
    G.add_edges(1, 5, 3, 0);
    G.add_edges(8, 5, 3, 0);
    G.add_edges(8, 9, 7, 0);
    G.add_edges(5,2,6,0);
    G.add_edges(5,9,11,0);
    G.add_edges(5, 6, 2, 0);
    G.add_edges(2,6,1,0);
    G.add_edges(9, 6, 8, 0);

    //执行Prime算法
    Prime();

    cout << "W  P:" << endl;
    for (int i = 0; i < 10; i++)
        cout << tab2[i][1] << "  " << tab2[i][2] << endl;
    cout << endl
         << endl;

    Kruskal();

    cout<<"edges:"<<endl;
    for(Graph::Edge t:KEV)
        cout << t.from_to[0] << "  " << t.from_to[1] << endl;

    return 0;
}

bool finish()
{
    for(int i=0;i<10;i++)
        if(!tab[i][0])
            return false;
    return true;
}

bool finish2()
{
    for (int i = 0; i < 10; i++)
        if (!tab2[i][0])
            return false;
    return true;
}

int find_next_Vertex()
{
    int next_vertex = -1;
    int next_weight = 0xfff;
    for (int i = 0; i < 10; i++)
    {
        if(tab[i][0]==0&&tab[i][1]<next_weight)
        {
            next_vertex = i;
            next_weight = tab[i][1];
        }
    }
    return next_vertex;
}

int find_next_Vertex2()
{
    int next_vertex = -1;
    int next_weight = 0xfff;
    for (int i = 0; i < 10; i++)
    {
        if (tab2[i][0] == 0 && tab2[i][1] < next_weight)
        {
            next_vertex = i;
            next_weight = tab2[i][1];
        }
    }
    return next_vertex;
}

void tabing_Vertex_edge(int Vertex)
{
    tab[Vertex][0] = 1;
    for (int i = 0; i < 10; i++)
    {
        if(i==Vertex)
            continue;
        int w = G.find_edge(Vertex, i).weight;
        if (w != -1)
        {
            if(tab[i][0]==0)
            {
                if(tab[i][1]>w+tab[Vertex][1])
                {
                    tab[i][1] = w + tab[Vertex][1];
                    tab[i][2] = Vertex;
                }
            }
        }
    }
}

void tabing_Vertex_edge2(int Vertex)
{
    tab2[Vertex][0] = 1;
    for (int i = 0; i < 10; i++)
    {
        if (i == Vertex) // 跳过自己
            continue;
        int w = G.find_edge(Vertex, i).weight; // 从 Vertex 到 i 的权值，如果边不存在，则返回-1
        if (w != -1)
        {
            if (tab2[i][0] == 0)
            {
                if (tab2[i][1] > w) // 三个if：当边存在；当i点没被走过；当i点记录的权值大于w
                {
                    tab2[i][1] = w;
                    tab2[i][2] = Vertex;
                }
            }
        }
    }
}

void dijkstra()
{
    tab[0][0] = 0;
    tab[0][1] = 0;
    tab[0][1] = 0;

    for(int i=1;i<10;i++)
    {
        tab[i][0]=0;
        tab[i][1] = 0xffff;
        tab[i][2] = 0xffff;
    }

    while (!finish())
        tabing_Vertex_edge(find_next_Vertex());
}

void Prime()
{
    /*初始化表格*/
    tab2[0][0] = 0;
    tab2[0][1] = 0;
    tab2[0][1] = 0;

    for (int i = 1; i < 10; i++)
    {
        tab2[i][0] = 0;
        tab2[i][1] = 0xffff;
        tab2[i][2] = 0xffff;
    }
    /* 初始化完成 */

    /* 当还没有完成 */
    while (!finish2())
        tabing_Vertex_edge2(find_next_Vertex2());/* 找到下一个节点并打表 */
}

    //int temp[10] = {0};
    bool cnt(Graph::Edge a, Graph::Edge b)
{
    return a.weight < b.weight;
}

int Find(int x)
{
    int r = x;
    while (r != pre[r]) //判断是否为根节点
        r = pre[r];

    int i = x, j;
    while (pre[i] != r) //优化过程，最终pre[i]都指向根节点
    {
        j = pre[i];
        pre[i] = r;
        i = j;
    }
    return r; //返回根节点
}

bool Combine(int x, int y)
{
    int fx = Find(x), fy = Find(y);
    if (fx != fy) //若根节点不同
    {
        pre[fy] = fx; //将其中一个置为另一个的根节点，实现合并
        return true;
    }
    return false;
}

void Kruskal()
{

    /* Kruskal初始化 */
    sort(G.edges.begin(), G.edges.end(), cnt);

    for(int i=0;i<10;i++)
        pre[i] = i;
    /* 初始化完成 */
    


    /* 从最小边开始遍历 */
    for(int i=0;i<G.edges.size();i++)
    {
        int *temp = G.edges.at(i).from_to;
        if(Combine(temp[0], temp[1]))
            KEV.push_back(G.edges.at(i));// 如果合并成功，将边推入vector
    }
}