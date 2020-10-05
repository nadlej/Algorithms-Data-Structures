#include <iostream>
#include <stack>
#include <cstdlib>   // std::rand(), RAND_MAX, std::srand()
#include <assert.h>
using namespace std;


template <typename T>
struct BSTNode {
// the default access mode and default inheritance mode are public
    T value;
    BSTNode *left, *right;
    T size = 0;
    //BSTNode *parent;   // używane w pewnych zastosowaniach
    // kostruktor domyślny
    BSTNode() : value(T()), left(nullptr), right(nullptr) {}
    BSTNode(const T& item, BSTNode *le=nullptr, BSTNode *ri=nullptr) :
            value(item), left(le), right(ri) {} // konstruktor
    ~BSTNode() {} // destruktor
};
// Szablon dla przypadkowego drzewa binarnego.
template <typename T>
class RandomBinaryTree {
    BSTNode<T> *root;
public:
    RandomBinaryTree() : root(nullptr) {} // konstruktor domyslny
    ~RandomBinaryTree() { clear(); } // trzeba wyczyscic
    bool empty() const { return root == nullptr; }
    T& top() { return root->value; } // podgląd korzenia
    void insert(const T& item) { root = insert(root, item); }
    //void remove(const T& item); // na razie nie usuwamy elementów
    // Szukając element dostajemy wskaźnik do elementu lub nullptr.
    T* search(const T& item) const { return &(search(root, item)->value); }
    void preorder() { preorder(root); }
    void inorder() { inorder(root); }
    void postorder() { postorder(root); }
    void iter_preorder();
    void iter_inorder(); // trudne
    void iter_postorder(); // trudne
    void bfs(); // przejscie poziomami (wszerz)
    void clear() { root = nullptr; }
    void display() { display(root, 0); }
    int count_leafs(int type);
    int calc_total(int type);

    // Metody bezpośrednio odwołujące się do node.
    // Mogą działać na poddrzewie.
    void clear(BSTNode<T> *node);
    BSTNode<T> * insert(BSTNode<T> *node, const T& item); // zwraca nowy korzeń
    BSTNode<T> * search(BSTNode<T> *node, const T& item) const;
    void preorder(BSTNode<T> *node);
    void inorder(BSTNode<T> *node);
    void postorder(BSTNode<T> *node);
    void display(BSTNode<T> *node, int level);
    virtual void visit(BSTNode<T> *node) {
        std::cout << "visiting " << node->value << std::endl;
    }
private:
    int LeafCounter;
    int SumOf;
};
// Wyświetlanie obróconego (counterclockwise) drzewa binarnego.
template <typename T>
void RandomBinaryTree<T>::display(BSTNode<T> *node, int level) {
    if (node == nullptr)
        return;
    display(node->right, level + 1);
    std::cout << std::string(3 * level, ' ') << node->value << std::endl;
    display(node->left, level + 1);
}


template <typename T>
BSTNode<T> * RandomBinaryTree<T>::insert(BSTNode<T> *node, const T& item) {
    if (node == nullptr) {
        return new BSTNode<T>(item);
    }
    if (std::rand() % 2) { // można lepiej
        node->left = insert(node->left, item);
    } else {
        node->right = insert(node->right, item);
    }
    return node; // zwraca nowy korzen
}
template <typename T>
BSTNode<T> * RandomBinaryTree<T>::search(BSTNode<T> *node, const T& item) const {
    if (node == nullptr || node->value == item) {
        return node;
    }
    T* ptr;
    ptr = search(node->left, item);
    if (ptr == nullptr) {
        ptr = search(node->right, item);
    }
    return ptr;
}
template <typename T>
void RandomBinaryTree<T>::preorder(BSTNode<T> *node) {
    if (node == nullptr)
        return;
    LeafCounter++;
    SumOf += node->value;
    visit(node);
    preorder(node->left);
    preorder(node->right);
}
template <typename T>
void RandomBinaryTree<T>::iter_preorder() {
    std::stack<BSTNode<T>*> S; // wskazniki do wezlow
    BSTNode<T> *node = root;
    if (root == nullptr)
        return;
    //SumOf+=node->value;
    S.push(node);
    while (!S.empty()) {
        LeafCounter++;
        node = S.top(); // podgladamy
        SumOf += node->value;
        S.pop();        // usuwamy ze stosu
        visit(node);
        if (node->right != nullptr) // najpierw prawe poddrzewo!
            S.push(node->right);
        if (node->left != nullptr)
            S.push(node->left);
    }
}

template <typename T>
int RandomBinaryTree<T>::count_leafs(int type){
    LeafCounter = 0;
    assert(root != nullptr);
    if(type == 1){
        BSTNode<T> *node = root;
        RandomBinaryTree<T>::preorder(node);
    }else if(type == 2){
        RandomBinaryTree<T>::iter_preorder();
    }
    return LeafCounter;
}
template <typename T>
int RandomBinaryTree<T>::calc_total(int type){
   SumOf = 0;
   assert(root != nullptr);
    if(type == 1){
        BSTNode<T> *node = root;
        RandomBinaryTree<T>::preorder(node);
    }else if(type == 2){
        RandomBinaryTree<T>::iter_preorder();
    }
    return SumOf;
}

int main(){
    RandomBinaryTree<int> Tree;
    cout << "Test dla wielu elementow: " << endl;
    cout << endl;
    Tree.insert(50);
    Tree.insert(504);
    Tree.insert(530);
    Tree.insert(6);
    Tree.insert(63);
    Tree.insert(61);
    cout << endl;
    cout << "Dodawanie lisci rekurencyjnie: " <<  Tree.count_leafs(1) << endl;
    cout << "Suma lisci rekurencyjnie : " << Tree.calc_total(1) << endl;
    cout << "Dodawanie lisci nierekurencyjnie: " <<  Tree.count_leafs(2) << endl;
    cout << "Suma lisci nierekurencyjnie : " << Tree.calc_total(2) << endl;
    Tree.clear();
    cout << endl;
    cout << endl;


    cout << "Test dla I elementu: " << endl;
    Tree.insert(61);
    cout << "Dodawanie lisci rekurencyjnie: " <<  Tree.count_leafs(1) << endl;
    cout << "Suma lisci rekurencyjnie : " << Tree.calc_total(1) << endl;
    cout << "Dodawanie lisci nierekurencyjnie: " <<  Tree.count_leafs(2) << endl;
    cout << "Suma lisci nierekurencyjnie : " << Tree.calc_total(2) << endl;
}