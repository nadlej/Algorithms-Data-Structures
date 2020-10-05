
#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

using namespace std;

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

void interface(){

    cout << "Tworzymy pusty stos" << endl;
    DoubleStack<int> list;
    cout << "Sprawdzamy, czy stos jest pusty(zwraca 1): " << list.empty() << endl;
    cout << "Dodajemy pare elementow na stos\n";
    list.push(5);
    list.push(2);
    list.push(99);
    list.push(224);
    list.push(992);
    cout << "Zwracamy element ze stosu: \n";
    cout << list.top() << endl;
    cout << "Sprawdzamy ilosc elementow\n";
    cout << list.size() << endl;
    cout << "Usuwamy element ze stosu\n";
    list.pop();
    cout << "Sprawdzamy ilosc elementow\n";
    cout << list.size() << endl;
    cout << "Sprawdzamy, czy stos jest pusty(zwraca 1): " << list.empty() << endl;
    cout << "Zwracamy element ze stosu: \n";
    cout << list.top() << endl;
    cout << "Czyscimy stos" << endl;
    list.clear();
    cout << "Sprawdzamy, czy stos jest pusty(zwraca 1): " << list.empty() << endl;
    cout << endl;
    cout << endl;

    cout << "Testujemy dla jednego elementu" << endl;
    cout << endl;
    cout << endl;
    cout << "Sprawdzamy, czy stos jest pusty(zwraca 1): " << list.empty() << endl;
    cout << "Dodajemy element na stos\n";
    list.push(5);
    cout << "Sprawdzamy ilosc elementow\n";
    cout << list.size() << endl;
    cout << "Sprawdzamy, czy stos jest pusty(zwraca 1): " << list.empty() << endl;
    cout << "Zwracamy element ze stosu: \n";
    cout << list.top() << endl;
    cout << "Usuwamy element ze stosu\n";
    list.pop();
    cout << "Sprawdzamy, czy stos jest pusty(zwraca 1): " << list.empty() << endl;
    cout << endl;
    cout << endl;
}

int main(){
    interface();
}
