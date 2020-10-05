#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

using namespace std;

template < typename T>
class ArrayList {
    T* tab;
    int msize; // najwieksza mozliwa liczba elementow
    int last; // pierwsza wolna pozycja
public:
    ArrayList(int s) : msize(s), last(0) {
        tab = new T[s];
        assert( tab != nullptr );
    } // default constructor
    ~ArrayList() { delete [] tab; }
    ArrayList(const ArrayList& other); // copy constructor
    ArrayList& operator=(const ArrayList& other); // copy assignment operator, return *this
    bool empty() const { return last == 0; } // checks if the container has no elements
    int size() const { return last; } // liczba elementow na liscie
    int max_size() const { return msize; } // najwieksza mozliwa liczba elementow
    void push_front(const T& item){
        for(int i=last;i>0;i--)
            tab[i]=tab[i-1];
        tab[0]=item;
        last++;
    } // dodanie na poczatek
    void push_back(const T& item){
        tab[last]=item;
        last++;
    } // dodanie na koniec
    T& front(){
        return tab[0];
    } // zwraca poczatek, nie usuwa
    T& back(){
        return tab[last-1];
    } // zwraca koniec, nie usuwa
    void pop_front(){
        for(int i=0;i<last-1;i++)
            tab[i]=tab[i+1];
        if(last!=0)last--;
    } // usuwa poczatek
    void pop_back(){
        tab[last-1]=0;
        if(last!=0)last--;
    } // usuwa koniec
    void clear(){
        for(int i=last-1;i<=0;i++)
            tab[last]=0;
        last=0;
    } // czyszczenie listy z elementow
    void display(){
        for(int i=0;i<last;i++)
            cout << tab[i] << " ";
        cout << endl;
    } // lepiej zdefiniowac operator<<
    void reverse(){
        for(int i=0;i<(last/2); i++){
            T test = tab[i];
            tab[i]=tab[last-1-i];
            tab[last-1-i] = test;
        }
    } // odwracanie kolejnosci
    void sort(){
        for( int i=0; i<last ;i++)
            for(auto j= i + 1 ; j < last ; j++ )
                if( tab[j] < tab[i] )
                {
                    T temp = tab[i] ;
                    tab[i] = tab[j] ;
                    tab[j] = temp ;
                }
    } // sortowanie listy
    void merge(ArrayList& other){
        for(int i=0; i< other.size(); i++)
            tab[last+i] = other[i];
        last+=other.size();
        sort();
    } //  merges two sorted lists into one
    // Operacje z indeksami.
    int erase(int pos){
        for(int check = pos;check<last;check++)
            tab[check]=tab[check+1];
        last--;
        return pos;
    } // return Iterator following the last removed element,
    // czyli u mnie pos, bo ten element za usunietym sie przesunie na pos;
    // ale jak usune ostatni, to chyba powinien zwrocic -1 (niewlasciwy indeks)
    //
    // https://en.cppreference.com/w/cpp/language/operators
    // Array subscript operator
    T& operator[](int pos){
        return tab[pos];
    } // podstawienie L[pos]=item
    const T& operator[](int pos) const{
        return tab[pos];
    } // odczyt L[pos]
    int index(const T& item){
        for(int i=0;i<last;i++)
            if(tab[i] == item)
                return i;
            return -1;
    } // jaki index na liscie (-1 gdy nie ma)
    int insert(int pos, const T& item){
        for(int i=last;i>pos;i--)
            tab[i]=tab[i-1];
        tab[pos] = item;
        last++;
        return pos+1;
    } // inserts item before pos,
    // zwraca pozycje wstawionego elementu
//    friend std::ostream& operator<<(std::ostream& os, const ArrayList& L);
};

void automatic(){
    ArrayList <int> Obj(20);
    Obj.push_front(2);
    Obj.push_front(3);
    Obj.push_front(5);
    Obj.push_back(8);
    Obj.display();
    cout << "Pierwsza liczba wynosi: " << Obj.front() << endl;
    cout << "Ostatnia liczba wynosi: " << Obj.back() << endl;
    cout << "Usuwamy 1 obiekt: " << endl;
    Obj.pop_front();
    Obj.display();
    cout << "Usuwamy element z konca: " << endl;
    Obj.pop_back();
    Obj.display();
    cout << "Czyscimy liste: "<< endl;
    Obj.clear();
    Obj.display();
    Obj.push_front(2);
    Obj.push_front(3);
    Obj.push_front(5);
    Obj.push_back(8);
    cout << "Odwracamy kolejnosc: " << endl;
    Obj.display();
    Obj.reverse();
    Obj.display();
    cout << "Sortujemy liste: " << endl;
    Obj.sort();
    Obj.display();
    cout << "Laczymy 2 list: " << endl;
    ArrayList <int> El(5);
    El.push_front(1);
    El.push_front(9);
    El.push_front(53);
    El.display();
    Obj.merge(El);
    Obj.display();
    cout << "Usuwamy element na pozycji :" << Obj.erase(2) << endl;
    Obj.display();
    cout << "Nadajemy wartosc 20 elementowi 1: " << endl;
    Obj.operator[](1) = 20;
    Obj.display();
    cout << "Element na pozycji 5 ma wartosc: " << endl;
    cout << Obj.operator[](5) << endl;
    cout << "Pozycja elemntu z wartoscia 8  wynosi: "<< endl;
    cout << Obj.index(8) << endl;
    cout << "Wstawiamy element o wartosci 99 przed element 3" << endl;
    cout << "Elemnt przyjmie pozycje: " << Obj.insert(3,99) << endl;
    Obj.display();



}

void mechanical(){
    int n;
    int k;
    cout << "Podaj maksymalny rozmar tablicy: \n";
    cin >> n;
    ArrayList <int> Obj(n);
    cout << "Podaj ile elemnetow chcesz wczytac : \n";
    cin >> n;
    while(n > Obj.max_size()){
        cout << "Podaj ile elemnetow chcesz wczytac : \n";
        cin >> n;
    }
    cout << "Podawaj elementy (kazdy zatwierdz enterem) :\n";
    for(int i=0;i<n;i++){
        cin >> k;
        Obj.push_front(k);
    }
    Obj.display();
    cout << "Pierwsza liczba wynosi: " << Obj.front() << endl;
    cout << "Ostatnia liczba wynosi: " << Obj.back() << endl;
    cout << "Usuwamy zerowy obiekt: " << endl;
    Obj.pop_front();
    Obj.display();
    cout << "Usuwamy element z konca: " << endl;
    Obj.pop_back();
    Obj.display();
    cout << "Odwracamy kolejnosc: " << endl;
    Obj.display();
    Obj.reverse();
    Obj.display();
    cout << "Sortujemy liste: " << endl;
    Obj.sort();
    Obj.display();
    cout << "Podaj rozmiar II tablicy o wymiarach max " << Obj.max_size()-Obj.size() << endl;
    int l;
    cin >> l;
    while(l> Obj.max_size()-Obj.size()){
        cout << "Podaj rozmiar II tablicy o wymiarach max " << Obj.max_size()-Obj.size() << endl;
        cin >> l;
    }
    ArrayList <int> El(l);
    cout << "Podawaj elementy (kazda zatwierdz enterem) :\n";
    for(int i=0;i<l;i++){
        cin >> k;
        El.push_front(k);
    }
    El.display();
    cout << "Laczymy 2 list: " << endl;
    Obj.merge(El);
    Obj.display();
    cout << "Wybierz pozycje elementu do usuniecia o maksymalnym indeksie " << Obj.size()-1 << endl;
    cin>> k;
    while(k>Obj.size()-1){
        cout << "Wybierz pozycje elementu do usuniecia o maksymalnym indeksie " << Obj.size()-1 << endl;
        cin>> k;
    }
    cout << "Usuwamy element na pozycji : " << Obj.erase(k) << endl;
    Obj.display();
    cout << "Podaj wartosc do nadania elementowi: " << endl;
    cin >> k;
    cout << "Podaj indeks elementu, ktorego wartosc zmienimy: " << endl;
    cin>> n;
    while(n>Obj.size()-1){
        cout << "Podaj indeks elementu, ktorego wartosc zmienimy: " << endl;
        cin>> n;
    }
    Obj.operator[](n) = k;
    Obj.display();
    cout << "Podaj pozycje elementu, ktorego wartosc chcesz sprawdzic: " << endl;
    cin >> n;
    while(n>Obj.size()-1){
        cout << "Podaj pozycje elementu, ktorego wartosc chcesz sprawdzic: " << endl;
        cin>> n;
    }
    cout << Obj.operator[](n) << endl;
    cout << "Podaj wartosc, ktorej szukasz, a zostanie zwrocony indeks, jezeli pozycja istnieje lub -1, gdy jej nie ma: " << endl;
    cin >> k;
    cout << Obj.index(k) << endl;
    cout << "Podaj wartosc elementu, ktory zostanie wstawiony przed obiekt: " << endl;
    cin>> k;
    cout << "Podaj indeks elementu przed ktory liczba ma zostac wstawiona: " << endl;
    cin >> n;
    while(n>Obj.size()-1){
        cout << "Podaj indeks elementu przed ktory liczba ma zostac wstawiona: " << endl;
        cin>> n;
    }
    cout << "Elemnt przyjmie pozycje (od 1): " << Obj.insert(n,k) << endl;
    Obj.display();
    cout << "Czyscimy liste";
    Obj.clear();
    Obj.display();
}

int main(){
    int i;
    cout << "wybierz \n 1. By przeprowadzic test automatyczny \n 2. Przeprowadzic test wlasnorecznie\n";
    cin >> i;
    if(i==1)
    automatic();
    else{
    mechanical();
        }



}


// EOF
