#include "Graph.h"
#include <iostream>
#include <algorithm>
using namespace std;

Graph G(10);
int tab[10][3];

int find_next_Vertex();
void tabing_Vertex_edge(int Vertex);
bool finish();
void Prim();

int pre[10];
vector<Graph::Edge> KEV;
bool cnt(Graph::Edge a,Graph::Edge b);
int Find(int x);
bool Combine(int x, int y);
void Kruskal();

int main()
{
    
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
    
    


    Prim();

    cout << "W  P:" << endl;
    for (int i = 0; i < 10; i++)
        cout << tab[i][1] << "  " << tab[i][2] << endl;
    cout<<endl<<endl;

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

void Prim()
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


//int temp[10] = {0};
bool cnt(Graph::Edge a,Graph::Edge b)
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


    sort(G.edges.begin(), G.edges.end(), cnt);

    for(int i=0;i<10;i++)
        pre[i] = i;
    
    for(int i=0;i<G.edges.size();i++)
    {
        int *temp = G.edges.at(i).from_to;
        if(Combine(temp[0], temp[1]))
            KEV.push_back(G.edges.at(i));
    }
}