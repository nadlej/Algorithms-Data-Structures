// Piotr Przemielewski

#include<iostream>
#include<list>
#include <assert.h>


class MyQueue {
    int* tab;
    int msize; // największa możliwa liczba elementów plus jeden
    int head; // pierwszy do pobrania
    int tail; // pierwsza wolna pozycja
public:
    MyQueue(int s) : msize(s+1), head(0), tail(0) {
        tab = new int[s+1];
        assert( tab != nullptr );
    } // default constructor
    ~MyQueue() { delete [] tab; }
    MyQueue(const MyQueue& other); // copy constructor
    MyQueue& operator=(const MyQueue& other); // copy assignment operator, return *this
    bool empty() const { return head == tail; }
    bool full() const { return (head + msize -1) % msize == tail; }
    int size() const { return (tail - head + msize) % msize; }
    int max_size() const { return msize-1; }
    void push(const int& item); // dodanie na koniec
    int& front() { return tab[head]; } // zwraca poczatek
    int& back() { return tab[(tail + msize -1) % msize]; } // zwraca koniec
    void pop(); // usuwa poczatek
    void clear(); // czyszczenie listy z elementow
    void display();
};


void MyQueue::display() {
    for (int i = head; i != tail; i=(i+1) % msize) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}


void MyQueue::push(const int& item) {
    tab[tail] = item;
    tail = (tail + 1) % msize;
}


void MyQueue::pop() {
    tab[head] = 0;
    head = (head+1) % msize;
}


void MyQueue::clear() {
    for (head; head != tail; head=(head+1) % msize)
        tab[head] = 0;
}


class GraphList
{
    int V = 0 ; // liczba wierzchołków
    int E = 0; // liczba krawedzi
    std::list<int> *adj; // pointer na nasza liste wszystkich wierzcholkow
    std::list<int> *getBFS; // lista z wiezcholkami na której użyliśmy BFS
    std::list<int> *getDFS; // lista z wierzcholkami na ktorej uzylismy DFS

public:
    GraphList(int maxV, int maxE); // konsturktor
    ~GraphList();
    void addEdge(int v, int w); // dodaj krawedz
    int outEdges( int v);
    int getEdges(int v);
    std::list<int> listEdges(int v);
    std::list<int> listGetEdges(int v);
    void DFSRecursion(int v, bool visited[]);
    void DFS(int v);
    bool isConnected();
};

bool GraphList::isConnected()
{
    for(int i = 0; i < V; i++)
    {
        DFS(i);
        if(getDFS->size() != V)
            return false;
    }

    return true;
}


void GraphList::DFSRecursion(int v, bool visited[])
{
    visited[v] = true; // kolejna krawedz oznaczamy jak odwiedzona
  //  std::cout << v << " "; // wypisz
    getDFS->push_back(v); // dodaj do listy DFS

    std::list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) // poki lista polaczen danego wierzcholka nie bedzie pusta
        if (!visited[*i])  // sprawdzamy czy nie jest odwiedzony juz
            DFSRecursion(*i, visited); // rekurencja
}

void GraphList::DFS(int v)
{
    assert(v >= 0 && v < V);
    getDFS->clear(); // czyscimy w razie gdyby wczesniej lista była używana
    bool *visited = new bool[V];  // ustawienie wszystkich wierzcholkow na false
    for (int i = 0; i < V; i++)
        visited[i] = false;

    DFSRecursion(v, visited); // rozpoczynamy dzialanie przekazujac nr wierzcholka i odwiedzona tablice
   // std::cout << std::endl;
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
    adj = new std::list<int>[V];
    getBFS = new std::list<int>[V]; // tworzymy liste na wierzcholki BFS
    getDFS = new std::list<int>[V]; // tworzymy liste na wierzcholki DFS
}

void GraphList::addEdge(int v, int w)
{
    assert(v < V);
    assert(w < V);
    adj[v].push_back(w);
}
GraphList::~GraphList()
{
    delete adj;
    delete getBFS;
    delete getDFS;
}


class GraphListNON
{
    int V = 0 ; // liczba wierzchołków
    int E = 0; // liczba krawedzi
    bool* visited;
    std::list<int> *adj; // pointer na nasza liste wszystkich wierzcholkow
    std::list<int> *getBFS; // lista z wiezcholkami na której użyliśmy BFS
    std::list<int> *getDFS; // lista z wierzcholkami na ktorej uzylismy DFS

public:
    GraphListNON(int maxV, int maxE); // konsturktor
    ~GraphListNON();
    void addEdge(int v, int w); // dodaj krawedz
    int outEdges( int v);
    std::list<int> listEdges(int v);
    void BFS(int startVertex);
    void DFS(int v);
    void DFSRecursion(int v, bool visited[]);
    bool isConnected();

};

void GraphListNON::DFSRecursion(int v, bool visited[])
{
    visited[v] = true; // kolejna krawedz oznaczamy jak odwiedzona
  //  std::cout << v << " "; // wypisz
    getDFS->push_back(v); // dodaj do listy DFS

    std::list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) // poki lista polaczen danego wierzcholka nie bedzie pusta
        if (!visited[*i])  // sprawdzamy czy nie jest odwiedzony juz
            DFSRecursion(*i, visited); // rekurencja
}

void GraphListNON::DFS(int v)
{
    assert(v >= 0 && v < V);
    getDFS->clear(); // czyscimy w razie gdyby wczesniej lista była używana
    bool *visited = new bool[V];  // ustawienie wszystkich wierzcholkow na false
    for (int i = 0; i < V; i++)
        visited[i] = false;

    DFSRecursion(v, visited); // rozpoczynamy dzialanie przekazujac nr wierzcholka i odwiedzona tablice
   // std::cout << std::endl;
}

bool GraphListNON::isConnected()
{
    for(int i = 0; i < V; i++)
    {
        DFS(i);
        if(getDFS->size() != V)
            return false;
    }

    return true;
}

void GraphListNON::BFS(int startVertex)
{
    visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    MyQueue queue(V);

    visited[startVertex] = true;
    queue.push(startVertex);

    std::list<int>::iterator i;

    while(!queue.empty())
    {
        int currVertex = queue.front();
        std::cout << "Visited: " << currVertex << " " << std::endl;
        queue.pop();

        for(i = adj[currVertex].begin(); i != adj[currVertex].end(); ++i)
        {
            int adjVertex = *i;
            if(!visited[adjVertex])
            {

                visited[adjVertex] = true;
                queue.push(adjVertex);
            }
        }
    }
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
    getBFS = new std::list<int>[V]; // tworzymy liste na wierzcholki BFS
    getDFS = new std::list<int>[V]; // tworzymy liste na wierzcholki DFS
}

void GraphListNON::addEdge(int v, int w)
{
    assert(v < V);
    assert(w < V);
    adj[v].push_back(w); // do konkretnego wierzcholka dodaj krawedz
    adj[w].push_back(v);
}

GraphListNON::~GraphListNON() {
    delete adj;
    delete getBFS;
    delete getDFS;
}
void test()
{
    int type, vertex, edges;
    std::cout << "Wybierz 1  - grafy skierowane, 2 - grafy nieskierowane" << std:: endl;
    std::cin >> type;
    std::cout << "Podaj liczbe wierzcholkow" << std:: endl;
    std::cin >> vertex;
    std::cout << "Podaj liczbe krawedzi" << std:: endl;
    std::cin >> edges;
    if(type == 1)
    {
        int eg1, eg2;
        std::list<int> returnList;
        std::cout << "Podawaj jakie wierzcholki maja byc polaczone" << std:: endl;
        GraphList c2(vertex, edges);
        for(int i = 0; i < edges; i++)
        {
            std::cin >> eg1 >> eg2;
            c2.addEdge(eg1, eg2);
        }
        std::cout << "Sprawdzamy czy graf jest spojny (1 = true / 0 = false): ";
        std::cout << c2.isConnected() << std::endl;
        std::cout << std::endl;
        returnList.clear();

    }
    else if(type == 2)
    {
        int eg1, eg2;
        std::list<int> returnList;
        std::cout << "Podawaj jakie wierzcholki maja byc polaczone" << std:: endl;
        GraphListNON c2(vertex, edges);
        for(int i = 0; i < edges; i++)
        {
            std::cin >> eg1 >> eg2;
            c2.addEdge(eg1, eg2);
        }
        std::cout << "Sprawdzamy czy graf jest spojny (1 = true / 0 = false): ";
        std::cout << c2.isConnected() << std::endl;
        std::cout << std::endl;
        returnList.clear();
    }
}

int main() {
    test();
}