//
#include <iostream>
#include <stack>

template <class T>
class Node {
 public:
    Node() : parent(nullptr), left(nullptr), right(nullptr) {}
    Node(T value, Node* parent) : parent(parent), left(nullptr),
    right(nullptr), value(value) {}

    T value;
    Node* parent;
    Node* left;
    Node* right;
};

template <class T>
class SearchTree {
 public:
    SearchTree() : size(0), root(nullptr) {}
    void insert(const T& newValue);
    void preOrdPrint() const ;
    bool empty() const { return size == 0; }
    virtual ~SearchTree();

 private:
    size_t size;
    Node<T>* root;
};

template<class T>
void SearchTree<T>::insert(const T &newValue) {
    Node<T>* node = root;

    bool isFound = false;

    if (empty()) {
        root = new Node<T>;
        root->value = newValue;
        isFound = true;
    }

    while (!isFound) {
        if (newValue < node->value) {
            if (node->left == nullptr) {
                node->left = new Node<T>(newValue, node);
                isFound = true;
            } else {
                node = node->left;
            }
        } else {
            if (node->right == nullptr) {
                    node->right = new Node<T>(newValue, node);
                    isFound = true;
                } else {
                    node = node->right;
                }
        }
    }
    size++;
}

template<class T>
void SearchTree<T>::preOrdPrint() {
    std::stack<Node<T>*> stack;
    stack.push(root);
    size_t pseudoSize = size;
    while (pseudoSize != 0) {
        Node<T>* node = stack.top();
        std::cout << node->value << " ";
        stack.pop();
        pseudoSize--;
        if (node->right != nullptr)
            stack.push(node->right);
        if (node->left != nullptr)
            stack.push(node->left);
    }
    std::cout << std::endl;
}

template<class T>
SearchTree<T>::~SearchTree() {
    std::stack<Node<T>*> stack;
    stack.push(root);

    while (!empty()) {
        Node<T>* node = stack.top();
        delete node;
        stack.pop();
        size--;
        if (node->right != nullptr)
            stack.push(node->right);
        if (node->left != nullptr)
            stack.push(node->left);
    }
}


int main() {
    int size = 0;
    int64_t value = 0;
    SearchTree<int64_t> tree;
    std::cin >> size;
    for (int i = 0; i < size; ++i) {
        std::cin >> value;
        tree.insert(value);
    }
    tree.preOrdPrint();
    return 0;
}


