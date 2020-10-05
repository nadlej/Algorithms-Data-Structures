#include <iostream>
#include <stack>
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
class BinarySearchTree {
    BSTNode<T> *root;
public:
    BinarySearchTree() : root(nullptr) {} // konstruktor domyslny
    ~BinarySearchTree() { clear(); } // trzeba wyczyscic
    bool empty() const { return root == nullptr; }
    T& top() { return root->value; } // podglad korzenia
    void insert(const T& item) { root = insert(root, item); }
    void remove(const T& item); // usuwanie przez złączanie
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
    int find_max();
    int find_min();
    // Metody bezpośrednio odwołujące się do node.
    // Mogą działać na poddrzewie.
    void clear(BSTNode<T> *node);
    BSTNode<T> * insert(BSTNode<T> *node, const T& item); // zwraca nowy korzeń
    BSTNode<T> * search(BSTNode<T> *node, const T& item) const; // zwraca węzeł
    BSTNode<T> * remove(BSTNode<T> *node); // zwraca nowy korzeń poddrzewa
    void preorder(BSTNode<T> *node);
    void inorder(BSTNode<T> *node);
    void postorder(BSTNode<T> *node);
    void display(BSTNode<T> *node, int level);
    virtual void visit(BSTNode<T> *node) {
        std::cout << "visiting " << node->value << std::endl;
    }
};

template <typename T>
BSTNode<T> * BinarySearchTree<T>::insert(BSTNode<T> *node, const T& item) {
    if (node == nullptr) {
        return new BSTNode<T>(item);
    }
    if (item < node->value) {
        node->left = insert(node->left, item);
    } else {
        node->right = insert(node->right, item);
    }
    return node; // zwraca nowy korzen
}

template <typename T>
BSTNode<T> * BinarySearchTree<T>::search(BSTNode<T> *node, const T& item) const {
    if (node == nullptr) {
        return nullptr;
    } else if (node->value == item) {
        return node;
    } else if (item < node->value) {
        return search(node->left, item);
    } else {
        return search(node->right, item);
    }
}

template <typename T>
void BinarySearchTree<T>::iter_preorder() {
    std::stack<BSTNode<T>*> S; // wskazniki do wezlow
    BSTNode<T> *node = root;
    if (root == nullptr)
        return;
    S.push(node);
    while (!S.empty()) {
        node = S.top(); // podgladamy
        S.pop();        // usuwamy ze stosu
        visit(node);
        if (node->right != nullptr) // najpierw prawe poddrzewo!
            S.push(node->right);
        if (node->left != nullptr)
            S.push(node->left);
    }
}

template <typename T>
int BinarySearchTree<T>::find_max() {
    std::stack<BSTNode<T>*> S; // wskazniki do wezlow
    BSTNode<T> *node = root;
    assert(root != nullptr);
    S.push(node);
    while (!S.empty()) {
        node = S.top(); // podgladamy
        S.pop();        // usuwamy ze stosu
        visit(node);
        if (node->right != nullptr) // najpierw prawe poddrzewo!
            S.push(node->right);
    }
    return node->value;
}

template <typename T>
int BinarySearchTree<T>::find_min() {
    assert(root != nullptr);
    std::stack<BSTNode<T>*> S; // wskazniki do wezlow
    BSTNode<T> *node = root;
    S.push(node);
    while (!S.empty()) {
        node = S.top(); // podgladamy
        S.pop();        // usuwamy ze stosu
        visit(node);
        if (node->left != nullptr) // najpierw prawe poddrzewo!
            S.push(node->left);
    }
    return node->value;
}


int main(){
    BinarySearchTree<int> Tree;
    cout << "Test dla wielu elementow: " << endl;
    Tree.insert(50);
    Tree.insert(504);
    Tree.insert(530);
    Tree.insert(6);
    Tree.insert(63);
    Tree.insert(61);
    cout << "Element najwiekszy wynosi: " <<  Tree.find_max() << endl;
    cout << "Element najmniejszy wynosi: " << Tree.find_min() << endl;

    Tree.clear();

    cout << endl;
    cout << endl;

    cout << "Test dla jednego elementu: " << endl;
    Tree.insert(504);
    cout << "Element najwiekszy wynosi: " <<  Tree.find_max() << endl;
    cout << "Element najmniejszy wynosi: " << Tree.find_min() << endl;


}
