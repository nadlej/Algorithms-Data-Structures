// Piotr Przemielewski 

#include<iostream>
#include<list>
#include <assert.h>


class Graph
{

    int V = 0; // liczba wierzchołków
    int E = 0; // liczba krawedzi
    std::list<int> *adj; // pointer na nasza liste wszystkich wierzcholkow
    std::list<int> *getBFS; // lista z wiezcholkami na której użyliśmy BFS
    std::list<int> *getDFS; // lista z wierzcholkami na ktorej uzylismy DFS

    void DFSRecursion(int v, bool visited[]);

public:
    explicit Graph(int V); // konsturktor
    ~Graph();
    bool addEdge(int v, int w); // dodaj krawedz
    int getV(); // zwroc liczbe wierzcholkow
    int getE(); // zwroc liczbe krawedzi
    bool hasEdge(int v, int w); // sprawdzamczy czy istnieje polaczenie
    bool remEdge(int v, int w);
    void clear();
    bool isClear();
    void DFS(int v);
    void BFS(int s);
};

bool Graph::isClear()
{
    if(adj->size() != 0)
        return false;
    else
        return true;
}

void Graph::clear()
{
    for(int i = V; i >0; i--)
        for(int j = adj[i-1].size(); j !=0; j--)
            adj[i-1].pop_back();
    E = 0;

}

bool Graph::remEdge(int v, int w)
{
    assert(v >= 0 && v < V);
    assert(w >= 0 && w < V);
    std::list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if(*i == w)
        {
            adj[v].erase(i);
            return true;
        }
    return false;
}

bool Graph::hasEdge(int v, int w)
{
    assert(v >= 0 && v < V);
    assert(w >= 0 && w < V);
    std::list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if(*i == w)
            return true;
        return false;
}

int Graph::getE()
{
    return E;
}

int Graph::getV()
{
    return V;

}

void Graph::printDFS()
{
    std::list<int>::iterator it;
    for( it = getDFS->begin(); it != getDFS->end(); ++it)
        std::cout << *it << " ";

    std::cout << std::endl;
}

void Graph::printBFS()
{
    std::list<int>::iterator it;
    for( it = getBFS->begin(); it != getBFS->end(); ++it)
        std::cout << *it << " ";

    std::cout << std::endl;
}

Graph::Graph(int V)
{
    assert(V > 0);
    this->V = V;
    adj = new std::list<int>[V]; // tworzymy liste tylu elementow ile podalismy, numerowane od 0
    getBFS = new std::list<int>[V]; // tworzymy liste na wierzcholki BFS
    getDFS = new std::list<int>[V]; // tworzymy liste na wierzcholki DFS
}

bool Graph::addEdge(int v, int w)
{
    assert(v >= 0 && v < V);
    assert(w >= 0 && w < V);
    std::list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if(*i == w)
            return false;
    adj[v].push_back(w); // do konkretnego wierzcholka dodaj krawedz
    E++;
    return true;
}

void Graph::DFSRecursion(int v, bool visited[])
{
    visited[v] = true; // kolejna krawedz oznaczamy jak odwiedzona
    std::cout << v << " "; // wypisz
    getDFS->push_back(v); // dodaj do listy DFS

    std::list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) // poki lista polaczen danego wierzcholka nie bedzie pusta
        if (!visited[*i])  // sprawdzamy czy nie jest odwiedzony juz
            DFSRecursion(*i, visited); // rekurencja
}

void Graph::DFS(int v)
{
    assert(v >= 0 && v < V);
    getDFS->clear(); // czyscimy w razie gdyby wczesniej lista była używana
    bool *visited = new bool[V];  // ustawienie wszystkich wierzcholkow na false
    for (int i = 0; i < V; i++)
        visited[i] = false;

    DFSRecursion(v, visited); // rozpoczynamy dzialanie przekazujac nr wierzcholka i odwiedzona tablice
    std::cout << std::endl;
}

void Graph::BFS(int s)
{
    assert(s >= 0 && s < V);
    getBFS->clear(); // czyscimy w razie gdyby wczesniej lista była używana
    // oznaczamy wszystkie wierzcholki jako nieodwiedzone
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    // tworzymy liste dla BFS
    std::list<int> queue;

    // oznaczamy obecny wierzcholek jako odwiedzony i dodajemy go do "kolejki"
    visited[s] = true;
    queue.push_back(s);

    std::list<int>::iterator i; // posłuży nam do iterowania

    while(!queue.empty())
    {
        // dodajemy wierzcholek do list getBFS i usuwamy go z "kolejki"
        s = queue.front();
        std::cout << s << " ";
        getBFS->push_back(s); // dodaj do listy BFS

        queue.pop_front();

        // sprawdzamy czy dzieci obecnego wierzcholka są odwiedzone
        // jeżeli nie, to oznaczamy je jako odwiedzone i dodajemy
        // do kolejki po której iterujemy
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
    std::cout << std::endl;
}

Graph::~Graph() {
    delete adj;
    delete getBFS;
    delete getDFS;
}

int main()
{

} 