#include <iostream>
#include <assert.h>
#include <list>
#include <vector>
#include <queue>


class GraphListNON
{
    int V = 0 ; // liczba wierzchołków
    int E = 0; // liczba krawedzi
    std::list<int> *adj; // pointer na nasza liste wszystkich wierzcholkow
    int **weigh;

public:
    GraphListNON(int maxV, int maxE); // konsturktor
    ~GraphListNON();
    void addEdge(int v, int w, int m); // dodaj krawedz
    int outEdges( int v);
    std::list<int> listEdges(int v);
    GraphListNON Prim();
};

GraphListNON GraphListNON::Prim()
{

    typedef std::pair<int,std::list<int>> pi;
    std::vector<std::list<int>> T;

    std::priority_queue<pi, std::vector<pi>, std::greater<pi> > pq;  //rosnąco

    int visited[V];

    for(int i = 0; i < V; i++)
        visited[i] = false;

    int v = 0;

    visited[v] = true;

    for(int i = 1; i < V; i++)
    {
        std::list<int> neighbours = listEdges(v);

        for(auto j : neighbours)
        {
            if(visited[j] == 0)
            {
                std::list<int> get;
                get.push_back(v);
                get.push_back(j);
                pq.push(make_pair(weigh[v][j],get));

            }
        }

        std::list<int> edge;
        int dest = 0;
        int source = 0;

        do{

            std::pair<int,std::list<int>> top = pq.top();

            int licz = 0;
            edge = top.second;

            for(auto l : edge)
            {
                if(licz == 0)
                    source = l;
                else
                    dest = l;

                licz++;
            }
            pq.pop();


        }while(visited[dest] == true);

        std:: list<int> minEdge;

        minEdge.push_back(source);
        minEdge.push_back(dest);
        minEdge.push_back(weigh[v][dest]);
        T.push_back(minEdge);

        visited[dest] = true;

        v = dest;

    }

    GraphListNON graph(V, T.size());

    for(int k = 0; k  < T.size(); k++)
    {

        std::list<int> edge = T[k];

        int counter = 0;

        int firstV = 0;
        int secondV = 0;
        int w = 0;

        for(auto j : edge)
        {
            if(counter == 0)
                firstV = j;
            else if(counter == 1)
                secondV = j;
            else
                w = j;

            counter++;
        }

        graph.addEdge(firstV, secondV, w);
    }

    return graph;

}


std::list<int> GraphListNON::listEdges(int v)
{
    assert(v < V);
    return adj[v];
}


int GraphListNON::outEdges(int v)
{
    assert(v < V);
    return adj[v].size();
}

GraphListNON::GraphListNON(int maxV, int maxE)
{
    assert(maxV != 0);
    this->V = maxV;
    this->E = maxE;
    adj = new std::list<int>[V]; // tworzymy liste elementow, numerowane od 0
    weigh = new int*[V];

    for(int i = 0; i < V; ++i)
        weigh[i] = new int[V];

    for(int i = 0; i < V; i++)
        for(int j = 0; j < V; j++)
            weigh[i][j] = 0;
}

void GraphListNON::addEdge(int v, int w, int m)
{
    assert(v < V);
    assert(w < V);
    adj[v].push_back(w); // do konkretnego wierzcholka dodaj krawedz
    adj[w].push_back(v);

    weigh[v][w] = m;
    weigh[w][v] = m;
}

GraphListNON::~GraphListNON() {
    delete adj;
}

void test()
{

    GraphListNON graph(6, 8);
    graph.addEdge(0, 1, 6);
    graph.addEdge(1, 5, 3);
    graph.addEdge(0, 2, 2);
    graph.addEdge(0, 3, 5);
    graph.addEdge(2, 4, 2);
    graph.addEdge(3, 4, 3);
    graph.addEdge(4, 5, 6);
    graph.addEdge(5, 2, 1);

    GraphListNON newGraph = graph.Prim();

    std::cout << std::endl;
    std::cout << "Polaczenia w minimalnym drzewie rozpinajacego:\n";
    for(int i = 0; i < 6; i++)
    {
        std::cout << "Dla wierzcholka " << i << ": \t";
        std::list<int> check = newGraph.listEdges(i);

        for(auto j : check)
            std::cout << j << "\t";
        std::cout << std::endl;
    }


}


int main() {
    test();
}