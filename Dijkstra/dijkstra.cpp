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
    int **weigh;

public:
    GraphList(int maxV, int maxE); // konsturktor
    ~GraphList();
    void addEdge(int v, int w, int m); // dodaj krawedz
    int outEdges( int v);
    int getEdges(int v);
    void Dijkstra(int s);
    std::list<int> listEdges(int v);
    std::list<int> listGetEdges(int v);

};

void GraphList::Dijkstra(int s)
{

    std::priority_queue<int, std::vector<int>, std::greater<int> > que; //rosnąco
    std::map<int,int> mapa;

    bool known[V];
    int distance[V];
    int predecessor[V];

    for (int i = 0; i < V; i++)
    {
        known[i] = false;
        distance[i]= INT_MAX;
        predecessor[i] = -1;
    }

    distance[s] = 0;
    que.push(0);
    mapa.insert(std::pair<int,int>(que.top(),s));


    while(!que.empty())
    {
        int v =  mapa.find(que.top())->second;
        que.pop();

        if(!known[v])
        {
            known[v] = true;
            std::list<int>::iterator e;
            std::list<int> tab = listEdges(v);

            for(e = tab.begin(); e != tab.end(); ++e)
            {
                int w = *e;
                int d = distance[v] + weigh[v][w];

                if(distance[w] > d)
                {
                    distance[w] = d;
                    predecessor[w] = v;
                    que.push(d);
                    mapa.insert(std::pair<int,int>(d,w));
                }
            }
        }

    }

    std::cout << "Dla wierzcholka " << s << " odleglosc do  poszczegolnych wierzcholkow wynosza: ";
    std::cout << std::endl;
    for(int i = 0; i < V; i++)
    {
        if(i != s)
        {
            std::cout << "Do " << i << " dystans wynosi " << distance[i] << " i prowadzi od tylu przez ";
            int k = predecessor[i];
            while(k != -1)
            {
                std::cout << k << "\t ";
                k = predecessor[k];
            }
            std::cout << std::endl;
        }
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
    weigh = new int*[V];
    adj = new std::list<int>[V];

    for(int i = 0; i < V; ++i)
        weigh[i] = new int[V];

    for(int i = 0; i < V; i++)
        for(int j = 0; j < V; j++)
            if(i != j)
                weigh[i][j] = INT_MAX;
            else
                weigh[i][j] = 0;
}

void GraphList::addEdge(int v, int w, int m)
{
    assert(v < V);
    assert(w < V);
    adj[v].push_back(w);
    weigh[v][w] = m;
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

    graph.Dijkstra(1);
}


int main() {
    test();
}