#include <iostream>
#include <assert.h>
#include <queue>
#include <list>
#include <map>


class GraphList
{
    int V = 0 ; // liczba wierzchołków
    int E = 0; // liczba krawedzi
    std::list<int> *adj; // pointer na nasza liste wszystkich wierzcholkow
    int **distance;

public:
    GraphList(int maxV, int maxE); // konsturktor
    ~GraphList();
    void addEdge(int v, int w, int m); // dodaj krawedz
    int outEdges( int v);
    int getEdges(int v);
    void Floyd();
    std::list<int> listEdges(int v);
    std::list<int> listGetEdges(int v);

};

void GraphList::Floyd()
{
    int intermediary[V][V];

    for(int i = 0; i < V; i++)
        for(int j = 0; j < V; j++)
            intermediary[i][j] = - 1;

    for(int i = 0; i < V; i++)
        for(int v = 0; v < V; v++)
            for(int w = 0; w < V; w++)
            {
                if(distance[v][i] != INT_MAX && distance[i][w] != INT_MAX)
                {
                    int d = distance[v][i] + distance[i][w];

                    if(distance[v][w] > d)
                    {
                        distance[v][w] = d;
                        intermediary[v][w] = i;
                    }
                }
            }


    std::cout << std::endl;
    std::cout << "\t";
    for(int i = 0; i < V; i++)
        std::cout << i << "\t";
    std::cout << std::endl << std::endl;

    for(int i = 0; i < V; i++){
        std::cout << i << "\t";
        for(int j = 0; j < V; j++)
        {
            if(distance[i][j] != INT_MAX)
                std::cout << distance[i][j] << "\t";
            else
                std::cout << "INF" << "\t";
        }
        std::cout << std::endl;
    }

}

std::list<int> GraphList::listGetEdges(int v)
{
    assert(v < V);
    std::list<int> returnList;
    std::list<int>::iterator j;
    for(int i = 0; i < V; i++)
    {

        for (j = adj[i].begin(); j != adj[i].end(); ++j)
            if(*j == v)
                returnList.push_back(i);
    }
    return returnList;
}

std::list<int> GraphList::listEdges(int v)
{
    assert(v < V);
    return adj[v];
}

int GraphList::getEdges(int v)
{
    assert(v < V);
    int counter = 0;
    std::list<int>::iterator j;
    for(int i = 0; i < V; i++)
    {
        for (j = adj[i].begin(); j != adj[i].end(); ++j)
            if(*j == v)
                counter++;
    }
    return counter;
}

int GraphList::outEdges(int v)
{
    assert(v < V);
    return adj[v].size();
}

GraphList::GraphList(int maxV, int maxE)
{
    assert(maxV != 0);
    this->V = maxV;
    this->E = maxE;
    distance = new int*[V];
    adj = new std::list<int>[V];

    for(int i = 0; i < V; ++i)
        distance[i] = new int[V];

    for(int i = 0; i < V; i++)
        for(int j = 0; j < V; j++)
            if(i != j)
                distance[i][j] = INT_MAX;
            else
                distance[i][j] = 0;
}

void GraphList::addEdge(int v, int w, int m)
{
    assert(v < V);
    assert(w < V);
    adj[v].push_back(w);
    distance[v][w] = m;
}
GraphList::~GraphList()
{
    delete adj;
}

int test()
{
    GraphList graph(6, 8);
    graph.addEdge(1, 0, 3);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 2, 5);
    graph.addEdge(2, 3, 2);
    graph.addEdge(3, 0, 5);
    graph.addEdge(2, 4, 4);
    graph.addEdge(4, 5, 1);
    graph.addEdge(3, 5, 5);

    graph.Floyd();

}


int main() {
    test();
}