#pragma once
#include <vector>
using namespace std;

class Graph
{  
public:
    class Edge
    {
    private:
    public:
        int from_to[2];
        int weight = 0;
        Edge();
        Edge(int from, int to, int Weight = 0)
        {
            from_to[0] = from;
            from_to[1] = to;
            weight = Weight;
        };
        ~Edge(){};
    };
    vector<Edge> edges;
    Graph();
    Graph(int Vertexs_num);
    ~Graph();
    inline int get_deges_num() { return edges.size(); }
    inline void add_edges(int from, int to,int Weight=0,bool directional = true)
    {
        edges.push_back(Edge(from, to,Weight)); 
        if(!directional)
            edges.push_back(Edge(to, from, Weight));
    }
    Edge find_edge(int from, int to)
    {
        for(Edge t:edges)
            if((t.from_to[0]==from&&t.from_to[1]==to)||(t.from_to[0]==to&&t.from_to[1]==from))
                return t;
        return Edge(-1, -1, -1);
    }

private:
    int Vertexs;
    
};

Graph::Graph()
{
}

Graph::Graph(int Vertex_num)
{
    Vertexs = Vertex_num;
}

Graph::~Graph()
{
}
