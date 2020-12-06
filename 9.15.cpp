/* �� �� ͼ ��*/
#include "Graph.h"
#include <iostream>
#include <algorithm>
using namespace std;

/*ͼ*/
Graph G(10);

/* dijkstra�㷨(һ��ʼ��С�İ�Primeд��dijkstra) */
/*��[*][0]��ʾ�Ƿ��ҹ���[*][1]��ʾ�����ڵ�ľ��룬[*][2]��ʾ���ڵ�*/
int tab[10][3];
int find_next_Vertex(); // �ҵ���һ��Ӧ���ߵĽڵ㣨�����ڵ�����Ľڵ㣩
void tabing_Vertex_edge(int Vertex);// �ѽڵ�ĸ��ߴ�ӡ��tab��
bool finish(); // �ж��Ƿ�ȫ������
void dijkstra(); // �㷨��ʼ�������
/* End dijkstra */



/* Prime�㷨 */
/* ���и��������ܺ�dijkstra����һ�£�ֻ�ǰ�tab����tab2 */
int tab2[10][3];
int find_next_Vertex2();
void tabing_Vertex_edge2(int Vertex);
bool finish2();
void Prime();
/* End Prime */


/* Kruskal�㷨 */
vector<Graph::Edge> KEV; // ������ѡ��ıߡ�����
int pre[10]; // ����ڵ�ĸ�
bool cnt(Graph::Edge a,Graph::Edge b); // ��std::sort�õ��жϺ���
int Find(int x); // ����x�ĸ��ڵ㡾�顿
bool Combine(int x, int y); // �����Ÿ��ڵ㲻ͬ�����ϲ����������ϲ�����false,����true ������
void Kruskal(); //�㷨��ʼ�������
/* End Kuska */



int main()
{
    //¼��ߵ�����
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

    //ִ��Prime�㷨
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
        if (i == Vertex) // �����Լ�
            continue;
        int w = G.find_edge(Vertex, i).weight; // �� Vertex �� i ��Ȩֵ������߲����ڣ��򷵻�-1
        if (w != -1)
        {
            if (tab2[i][0] == 0)
            {
                if (tab2[i][1] > w) // ����if�����ߴ��ڣ���i��û���߹�����i���¼��Ȩֵ����w
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
    /*��ʼ�����*/
    tab2[0][0] = 0;
    tab2[0][1] = 0;
    tab2[0][1] = 0;

    for (int i = 1; i < 10; i++)
    {
        tab2[i][0] = 0;
        tab2[i][1] = 0xffff;
        tab2[i][2] = 0xffff;
    }
    /* ��ʼ����� */

    /* ����û����� */
    while (!finish2())
        tabing_Vertex_edge2(find_next_Vertex2());/* �ҵ���һ���ڵ㲢��� */
}

    //int temp[10] = {0};
    bool cnt(Graph::Edge a, Graph::Edge b)
{
    return a.weight < b.weight;
}

int Find(int x)
{
    int r = x;
    while (r != pre[r]) //�ж��Ƿ�Ϊ���ڵ�
        r = pre[r];

    int i = x, j;
    while (pre[i] != r) //�Ż����̣�����pre[i]��ָ����ڵ�
    {
        j = pre[i];
        pre[i] = r;
        i = j;
    }
    return r; //���ظ��ڵ�
}

bool Combine(int x, int y)
{
    int fx = Find(x), fy = Find(y);
    if (fx != fy) //�����ڵ㲻ͬ
    {
        pre[fy] = fx; //������һ����Ϊ��һ���ĸ��ڵ㣬ʵ�ֺϲ�
        return true;
    }
    return false;
}

void Kruskal()
{

    /* Kruskal��ʼ�� */
    sort(G.edges.begin(), G.edges.end(), cnt);

    for(int i=0;i<10;i++)
        pre[i] = i;
    /* ��ʼ����� */
    


    /* ����С�߿�ʼ���� */
    for(int i=0;i<G.edges.size();i++)
    {
        int *temp = G.edges.at(i).from_to;
        if(Combine(temp[0], temp[1]))
            KEV.push_back(G.edges.at(i));// ����ϲ��ɹ�����������vector
    }
}