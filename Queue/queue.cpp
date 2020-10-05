#include <iostream>
#include <assert.h>

using namespace std;

// myqueue.h
template <typename T>
class MyQueue {
    T* tab;
    int msize; // największa możliwa liczba elementów plus jeden
    int head; // pierwszy do pobrania
    int tail; // pierwsza wolna pozycja
public:
    MyQueue(int s) : msize(s+1), head(0), tail(0) {
        tab = new T[s+1];
        assert( tab != nullptr );
    } // default constructor
    ~MyQueue() { delete [] tab; }
    MyQueue(const MyQueue& other); // copy constructor
    MyQueue& operator=(const MyQueue& other); // copy assignment operator, return *this
    bool empty() const { return head == tail; }
    bool full() const { return (head + msize -1) % msize == tail; }
    int size() const { return (tail - head + msize) % msize; }
    int max_size() const { return msize-1; }
    void push(const T& item); // dodanie na koniec
    T& front() { return tab[head]; } // zwraca poczatek
    T& back() { return tab[(tail + msize -1) % msize]; } // zwraca koniec
    void pop(); // usuwa poczatek
    void clear(); // czyszczenie listy z elementow
    void display();
};

template <typename T>
void MyQueue<T>::display() {
    for (int i = head; i != tail; i=(i+1) % msize) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void MyQueue<T>::push(const T& item) {
    tab[tail] = item;
    tail = (tail + 1) % msize;
}

template <typename T>
void MyQueue<T>::pop() {
    tab[head] = 0;
    head = (head+1) % msize;
}

template <typename T>
void MyQueue<T>::clear() {
    for (head; head != tail; head=(head+1) % msize)
        tab[head] = 0;
}


void test(){
    cout << "Tworzymy kolejke z 10 elementow \n";
    int s = 10;
    MyQueue <int> Train(s);
    cout << "Sprawdzamy, czy jest pusta: \n";
    cout << Train.empty() << endl;
    cout << "Dodajemy maksymalna liczbe elementow\n";
    Train.push(10);
    Train.push(9);
    Train.push(8);
    Train.push(7);
    Train.push(6);
    Train.push(5);
    Train.push(4);
    Train.push(3);
    Train.push(2);
    Train.push(1);
    Train.display();
    cout << "Sprawdzamy, czy kolejka jest pelna: \n";
    cout << Train.full() << endl;
    cout << "Sprawdzamy obecny rozmiar kolejki: \n";
    cout << Train.size() << endl;
    cout << "Sprawdzamy maksymalny rozmiar kolejki: \n";
    cout << Train.max_size() << endl;
    cout << "Wypisujemy pierwszy element w kolejce \n";
    cout << Train.front() << endl;
    cout << "Wypisujemy ostatni element w kolejce \n";
    cout << Train.back() << endl;
    cout << "Usuwamy pare elementow: \n";
    Train.pop();
    Train.pop();
    Train.pop();
    Train.pop();
    Train.display();
    cout << "Dodajemy pare elementow: \n";
    Train.push(11);
    Train.push(13);
    Train.push(135);
    Train.display();
    cout << "Czyscimy \n";
    Train.clear();
    cout << "Sprawdzamy, czy wyczyszczona: ";
    cout << Train.empty() << endl;

    cout << endl;
    cout << endl;

    cout << "Test dla jednego elementu " << endl;
    cout << endl;
    cout << "Dodajemy jeden element\n";
    Train.push(99);
    Train.display();
    cout << "Sprawdzamy, czy kolejka jest pelna: \n";
    cout << Train.full() << endl;
    cout << "Sprawdzamy obecny rozmiar kolejki: \n";
    cout << Train.size() << endl;
    cout << "Sprawdzamy maksymalny rozmiar kolejki: \n";
    cout << Train.max_size() << endl;
    cout << "Wypisujemy pierwszy element w kolejce \n";
    cout << Train.front() << endl;
    cout << "Wypisujemy ostatni element w kolejce \n";
    cout << Train.back() << endl;
    cout << "Usuwamy element: \n";
    Train.pop();
    Train.display();
    cout << "Dodajemy element: \n";
    Train.push(515);
    Train.display();
    cout << "Czyscimy \n";
    Train.clear();
    cout << "Sprawdzamy, czy wyczyszczona: ";
    cout << Train.empty() << endl;

}

int main() {
    test();
}