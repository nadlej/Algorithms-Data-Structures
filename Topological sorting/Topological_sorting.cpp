// Piotr Przemielewski

#include<iostream>
#include<list>
#include <assert.h>
#include <vector>

template <typename T>
struct DoubleNode {
// the default access mode and default inheritance mode are public
    T value;
    DoubleNode *next, *prev;
    // konstruktor domyslny (niepotrzebny)
    DoubleNode() : value(T()), next(nullptr), prev(nullptr) {}
    DoubleNode(T item, DoubleNode *nptr=nullptr, DoubleNode *pptr=nullptr)
            : value(item), next(nptr), prev(pptr) {} // konstruktor
    ~DoubleNode() {} // destruktor
};


template <typename T>
class DoubleStack {
    DoubleNode<T> *head, *tail;
public:
    DoubleStack() : head(nullptr), tail(nullptr) {}
    ~DoubleStack(); // tu trzeba wyczyscic wezly
    bool empty() const { return head == nullptr; }
    int size() const; // O(n) bo trzeba policzyc
    void push(const T& item); // O(1)
    T& top() const { return tail->value; } // zwraca koniec, nie usuwa
    void pop(); // usuwa koniec O(n)
    void clear(); // czyszczenie listy z elementow O(n)

};

template <typename T>
DoubleStack<T>::~DoubleStack() {
    for (DoubleNode<T> *node; !empty(); ) {
        node = head->next; // zapamietujemy
        delete head;
        head = node; // kopiowanie wskaznika
    }
}

template <typename T>
int DoubleStack<T>::size() const{
    DoubleNode<T> *node = head;
    int i=0;
    while (node != nullptr){
        node = node->next;
        i++;
    }
    return i;
}

template <typename T>
void DoubleStack<T>::push(const T& item) {
    if (!empty()) {
        tail->next = new DoubleNode<T>(item, nullptr,tail);
        tail = tail->next;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
}
template <typename T>
void DoubleStack<T>::pop(){
    if (tail == head) { // jeden wezel na liscie
        tail = head = nullptr;
    }else {
        tail = tail->prev;
        tail->next = nullptr;
    }
}
template <typename T>
void DoubleStack<T>::clear() {
    DoubleNode<T> *node = head;
    while(node != 0){
        head = node->next;
        delete node;
        node = head;
    }
    delete head;
}

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
    DoubleStack<int> stack;
    bool *visited = new bool[V];


public:
    GraphList(int maxV, int maxE); // konsturktor
    ~GraphList();
    void addEdge(int v, int w); // dodaj krawedz
    int outEdges( int v);
    int getEdges(int v);
    std::list<int> listEdges(int v);
    std::list<int> listGetEdges(int v);
    void DFSRecursion(int k);
    void DFS();
    void printTopology();
    bool isConnected();
};

void GraphList::printTopology()
{
    int size = stack.size();

    for(int i = 0; i < size; i++)
    {
        std::cout << stack.top() << "\t";
        stack.pop();
    }

}

void GraphList::DFSRecursion(int k)
{

        visited[k] = true;

        std::list<int>::iterator i;
        for (i = adj[k].begin(); i != adj[k].end(); ++i) // poki lista polaczen danego wierzcholka nie bedzie pusta
            if (!visited[*i])  // sprawdzamy czy nie jest odwiedzony juz
                DFSRecursion(*i); // rekurencja
        stack.push(k);

}

void GraphList::DFS()
{

    for (int i = 0; i < V; i++)
        visited[i] = false;
    for(int k = 0; k < V; k++)
        if(!visited[k])
            DFSRecursion(k); // rozpoczynamy dzialanie przekazujac nr wierzcholka i odwiedzona tablice

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

void test()
{
    GraphList graph(6,10);
    graph.addEdge(0,2);
    graph.addEdge(1,0);
    graph.addEdge(1,2);
    graph.addEdge(3,0);
    graph.addEdge(3,1);
    graph.addEdge(3,4);
    graph.addEdge(4,1);
    graph.addEdge(4,2);
    graph.addEdge(5,0);
    graph.addEdge(5,4);
    graph.DFS();
    graph.printTopology();


}

int main() {
    test();

}