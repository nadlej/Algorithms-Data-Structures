
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
class DoubleList {
    DoubleNode<T> *head, *tail;
public:
    DoubleList() : head(nullptr), tail(nullptr) {}
    ~DoubleList(); // tu trzeba wyczyscic wezly
    bool empty() const { return head == nullptr; }
    int size() const; // O(n) bo trzeba policzyc
    void push_front(const T& item); // O(1)
    void push_back(const T& item); // O(1)
    T& front() const { return head->value; } // zwraca poczatek, nie usuwa
    T& back() const { return tail->value; } // zwraca koniec, nie usuwa
    void pop_front(); // usuwa poczatek O(1)
    void pop_back(); // usuwa koniec O(n)
    void clear(); // czyszczenie listy z elementow O(n)
    void display(); // O(n)
    void display_reversed(); // O(n)
    void reverse(); // O(n)
    // Operacje z indeksami. NIEOBOWIAZKOWE
    int erase(int pos); // return Iterator following the last removed element,
    T& operator[](int pos); // podstawienie L[pos]=item
    const T& operator[](int pos) const; // odczyt L[pos]
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma) O(n)
    int insert(int pos, const T& item); // inserts item before pos,
    // zwraca pozycje wstawionego elementu
};

template <typename T>
DoubleList<T>::~DoubleList() {
    for (DoubleNode<T> *node; !empty(); ) {
        node = head->next; // zapamietujemy
        delete head;
        head = node; // kopiowanie wskaznika
    }
}
template <typename T>
void DoubleList<T>::push_front(const T& item) {
    if (!empty()) {
        head = new DoubleNode<T>(item, head);
        head->next->prev = head;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
}
template <typename T>
void DoubleList<T>::push_back(const T& item) {
    if (!empty()) {
        tail->next = new DoubleNode<T>(item, nullptr,tail);
        tail = tail->next;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
}
template <typename T>
int DoubleList<T>::size() const{
    DoubleNode<T> *node = head;
    int i=0;
    while (node != nullptr){
        node = node->next;
        i++;
    }
    return i;
}
template <typename T>
void DoubleList<T>::pop_front() {
    if (head == tail) { // jeden wezel na liscie
        head = tail = nullptr;
    } else { // wiecej niz jeden wezel na liscie
        head = head->next;
        head->prev = nullptr;
    }
}
template <typename T>
void DoubleList<T>::pop_back(){
    if (tail == head) { // jeden wezel na liscie
        tail = head = nullptr;
    }else {
       tail = tail->prev;
       tail->next = nullptr;
    }
}
template <typename T>
void DoubleList<T>::clear() {
    DoubleNode<T> *node = head;
    while(node != 0){
        head = node->next;
        delete node;
        node = head;
    }
    delete head;
}
template <typename T>
void DoubleList<T>::display() {
    DoubleNode<T> *node = head;
    while (node != nullptr){
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << std::endl;
}
template <typename T>
void DoubleList<T>::reverse() {

    DoubleNode<T> *current = head;
    DoubleNode<T> *temp;
     while(current != NULL) {
         temp = current->next;
         current->next = current->prev;
         current->prev = temp;
         current = temp;
     }
     temp = head;
    head = tail;
    tail = temp;
    }



template <typename T>
void DoubleList<T>::display_reversed() {

    DoubleNode<T> *type = tail;
    while(type != NULL) {
        cout << type->value << " ";
        type = type->prev;
    }
    cout << endl;


}

void interface(){
    DoubleList<int> list;
    cout << endl;
    cout << "Test dla wielu elementow\n";
    cout << endl;
    cout << "Dolaczamy pare elementow do naszej listy \n";
    list.push_front(55);
    list.push_front(4);
    list.push_front(242);
    list.push_front(6);
    list.push_front(1);
    list.push_front(199);
    list.display();
    cout << "Gdyby odwrocic tablice \n";
    list.display_reversed();
    cout << "Dolaczmy element o wartosci 66 na koncu listy \n";
    list.push_back(66);
    list.display();
    cout << "Pierwszy element ma wartosc: \n";
    cout << list.front() << endl;
    cout << "Ostatni element ma wartosc: \n";
    cout << list.back() << endl;
    cout << "Usuwamy pierwszy element: \n";
    list.pop_front();
    list.display();
    cout << "Usuwamy ostatni element: \n";
    list.pop_back();
    list.display();
    cout << "Rozmiar listy wynosi: \n";
    cout << list.size() << endl;
    cout << "Zamieniamy kolejnosc: \n";
    list.reverse();
    list.display();
    cout << "Czyscimy liste: \n";
    list.clear();
    list.display();
    cout << "Sprawdzamy czy lista jest pusta (wartosc 1): \n";
    cout << list.empty() << endl;
    cout << endl;
    cout << "Test dla I elementu\n";
    cout << endl;
    cout << "Dolaczamy element do wyczyszonej listy\n";
    list.push_front(55);
    list.display();
    cout << "Gdyby odwrocic tablice \n";
    list.display_reversed();
    cout << "Dolaczmy element o wartosci 66 na koncu listy \n";
    list.push_back(66);
    list.display();
    cout << "Pierwszy element ma wartosc: \n";
    cout << list.front() << endl;
    cout << "Ostatni element ma wartosc: \n";
    cout << list.back() << endl;
    cout << "Usuwamy pierwszy element: \n";
    list.pop_front();
    list.display();
    cout << "Usuwamy ostatni element: \n";
    list.pop_back();
    list.display();
    cout << "Rozmiar listy wynosi: \n";
    cout << list.size() << endl;
    cout << "Zamieniamy kolejnosc: \n";
    list.reverse();
    list.display();
    cout << "Czyscimy liste: \n";
    list.clear();
    list.display();
    cout << "Sprawdzamy czy lista jest pusta (wartosc 1): \n";
    cout << list.empty() << endl;
    cout << endl;
    cout << endl;


}

int main(){
    interface();
}
