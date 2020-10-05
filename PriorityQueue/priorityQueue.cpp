
#include <algorithm>
#include <iostream>

using namespace std;

class Container {
    public:
        virtual ~Container() {};
        virtual int Count() const = 0;
        virtual bool IsEmply() const { return Count() == 0;}
        virtual bool IsFull() const { return false;}
        virtual void MakeNull() = 0;
};

template <typename T>
class PriorityQueue : public Container
{
    virtual void Enqueue(T element, int prio) = 0;
    virtual T FindMax() = 0;
    virtual T DequeueMax() = 0;
};

template <typename T>
class ArrayHP : public PriorityQueue<T>{

public:
    struct cells{
        T e[100];
        int p[100]{};
        int i = 0;
    };
    cells st;
    void Enqueue( T element, int prio);
    T FindMax();
    T DequeueMax();
    int Count() const  { return st.i;}
    void MakeNull();
};

template <typename T>
void ArrayHP<T>::MakeNull()
{
    for(int i = 0; i <  st.i; i++)
        DequeueMax();
}

template <typename T>
void ArrayHP<T>::Enqueue( T element, int prio)
{
    if(st.i < 100){
        st.p = prio;
        st.e = std::move(element);
        st.i++;
    }
}

template <typename T>
T  ArrayHP<T>::FindMax()
{
        int max = 0;
        T maxE;
        for(int i = 0; i < st.i; i++)
            if(st.p[i] > max){
                max = st.p[i];
                maxE = st.e[i];
            }

        return maxE;
}

template <typename T>
T ArrayHP<T>::DequeueMax()
{
    int max = 0;
    T maxE;
    int position = 0;
    for(int i = 0; i < st.i; i++)
        if(st.p[i] > max){
            max = st.p[i];
            maxE = st.e[i];
            position = i;
        }

    for(position; position < st.i-1; position++){
        st.e[position] = st.e[position+1];
        st.p[position] = st.p[position+1];
    }

    st.i--;
    return maxE;
}


template <typename T>
class BinaryHP : public PriorityQueue<T>{

public:
    T element [100];
    int priority[100];
    int size = 0;
    BinaryHP();
    void Enqueue(T element, int prio);
    T FindMax(){ return element[0];}
    T DequeueMax();
    int Count() const  { return size;}
    void MakeNull();

};

template <typename T>
void BinaryHP<T>::MakeNull()
{
    for(int i = 0; i < size; i++)
        DequeueMax();
}
template <typename T>
BinaryHP<T>::BinaryHP() {
    for(int & i : priority )
        i = 0;
}

template <typename T>
void BinaryHP<T>::Enqueue(T el, int prio) {

    priority[size] = prio;
    element[size] = std::move(el);
    int i = size;
    size++;

    while(i != 0 && priority [(i-1)/2] < priority [i]){
        int k = priority [(i-1)/2];
        priority [(i-1)/2] = priority [i];
        priority [i] = k;
        T s = element [(i-1)/2];
        element[(i-1)/2] =  element[i];
        element[i] = s;
        i = (i-1)/2;
    }
}

template <typename T>
T BinaryHP<T>::DequeueMax() {
    int i, j, v;
    T s;

    T heapMax = element[0];
    if (size--) {
        v = priority[size];
        s = element[size];
        i = 0;
        j = 1;

        while (j < size) {
            if (j+1 < size && priority[j+1] > priority[j]) j++;
            if (v >= priority[j]) break;
            priority[i] = priority[j];
            element[i] = element[j];
            i = j;
            j = 2 * j + 1;
        }

        priority[i] = v;
        element[i] = s;
    }
    return heapMax;
}

void test1(){
    cout << "Rozpoczynam test I dla kolejki priorytetowej zaimplementownej tablicowo:" << endl;
    BinaryHP<string> lista;
    lista.Enqueue("K",4);
    lista.Enqueue("A",1);
    lista.Enqueue("A",9);
    lista.Enqueue("O",3);
    lista.Enqueue("L",8);
    lista.Enqueue("A",5);
    lista.Enqueue("T",2);
    lista.Enqueue("A",7);
    lista.Enqueue("M",6);

    cout << lista.FindMax() << endl;
    cout << lista.DequeueMax() << endl;
    cout << lista.DequeueMax() << endl;

    cout << endl;
}

void test2(){
    cout << "Rozpoczynam test II dla kolejki priorytetowej zaimplementownej przez kopiec binarny:" << endl;
    BinaryHP<string> kopiec;
    kopiec.Enqueue("K",4);
    kopiec.Enqueue("A",1);
    kopiec.Enqueue("A",9);
    kopiec.Enqueue("O",3);
    kopiec.Enqueue("L",8);
    kopiec.Enqueue("A",5);
    kopiec.Enqueue("T",2);
    kopiec.Enqueue("A",7);
    kopiec.Enqueue("M",6);

    cout << kopiec.FindMax() << endl;
    cout << kopiec.DequeueMax() << endl;
    cout << kopiec.DequeueMax() << endl;

    cout << endl;

}


int main() {

    test1();
    test2();

}

