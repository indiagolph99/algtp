//
#include <iostream>
#include <stack>
#include <vector>
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
    std::vector<Node<T>*> getPreOrdList();
    bool empty() const { return size == 0; }
     ~SearchTree();

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
std::vector<Node<T>*> SearchTree<T>::getPreOrdList() {
    std::vector<Node<T>*> result;
    std::stack<Node<T>*> stack;
    stack.push(root);
    size_t pseudoSize = size;
    while (pseudoSize != 0) {
        Node<T>* node = stack.top();
        result.push_back(node);
        stack.pop();
        pseudoSize--;
        if (node->right != nullptr) {
            stack.push(node->right);
        }
        if (node->left != nullptr) {
            stack.push(node->left);
        }
    }
    return result;
}

template<class T>
SearchTree<T>::~SearchTree() {
    std::vector<Node<T>*> result = getPreOrdList();
    for (auto& i : result) {
        delete i;
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
    auto print = tree.getPreOrdList();
    for (auto& i : print) {
        std::cout << i->value << ' ';
    }
    std::cout << std::endl;

    return 0;
}


