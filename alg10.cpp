//
// Created by sava on 26.11.18.
//

#include <cstdint>
#include <cstdlib>
#include <gtest/gtest.h>
template<class T>
class SearchNode {
 public:
    SearchNode() : key(0), left(nullptr), right(nullptr) {}
    SearchNode(const T &value, SearchNode *node) : key(value),
                                                   left(nullptr),
                                                   right(nullptr) {}
    T key;
    SearchNode *left;
    SearchNode *right;
};
template<class T>
class SearchTree {
 public:
    SearchTree() : size(0), root(nullptr) {}
    void insert(const T &newValue);
    bool empty() const { return size == 0; }
    int height(SearchNode<T> *);
    int get_max_height();
 private:
    size_t size;
    SearchNode<T> *root;
};
template<class T>
void SearchTree<T>::insert(const T &newValue) {
    SearchNode<T> *node = root;
    bool isFound = false;
    if (empty()) {
        root = new SearchNode<T>;
        root->key = newValue;
        isFound = true;
    }
    while (!isFound) {
        if (newValue < node->key) {
            if (node->left == nullptr) {
                node->left = new SearchNode<T>(newValue, node);
                isFound = true;
            } else {
                node = node->left;
            }
        } else {
            if (node->right == nullptr) {
                node->right = new SearchNode<T>(newValue, node);
                isFound = true;
            } else {
                node = node->right;
            }
        }
    }
    size++;
}
template<class T>
int SearchTree<T>::height(SearchNode<T> *node) {
    int height1 = 0, height2 = 0;
    if (node == nullptr) {
        return 0;
    }
    if (node->left) {
        height1 = height(node->left);
    }
    if (node->right) {
        height2 = height(node->right);
    }
    return height2 > height1 ? height2 + 1 : height1 + 1;
}
template<class T>
int SearchTree<T>::get_max_height() {
    return height(root);
}
template<class T>
class TreapNode {
 public:
    TreapNode() : key(0),
                  priority(0),
                  left(nullptr),
                  right(nullptr) {}
    TreapNode(const T &value, const uint64_t &prior) : key(value),
                                                       priority(prior),
                                                       left(nullptr),
                                                       right(nullptr) {}
    T key;
    uint64_t priority;
    TreapNode *left;
    TreapNode *right;
};
template<class T>
class Treap {
 public:
    Treap() : root(nullptr) {}
    void split(TreapNode<T> *, uint64_t, TreapNode<T> *&, TreapNode<T> *&);
    void insert(TreapNode<T> *&, TreapNode<T> *);
    void add(T, uint64_t);
    int height(TreapNode<T> *);
    int get_max_height();
    bool empty() { return size == 0; }
 private:
    TreapNode<T> *root;
    size_t size;
};
template<class T>
void Treap<T>::split(TreapNode<T> *current, uint64_t key, TreapNode<T> *&left, TreapNode<T> *&right) {
    if (current == nullptr) {
        left = nullptr;
        right = nullptr;
    } else if (current->key < key) {
        split(current->right, key, current->right, right);
        left = current;
    } else {
        split(current->left, key, left, current->left);
        right = current;
    }
}
template<class T>
void Treap<T>::insert(TreapNode<T> *&cur_root, TreapNode<T> *newNode) {
    if (cur_root == nullptr) {
        cur_root = newNode;
        return;
    }
    if (cur_root->priority > newNode->priority) {
        if (newNode->key < cur_root->key) {
            insert(cur_root->left, newNode);
        } else {
            insert(cur_root->right, newNode);
        }
        return;
    }
    split(cur_root, newNode->key, newNode->left, newNode->right);
    cur_root = newNode;
}
template<class T>
void Treap<T>::add(T x, uint64_t priority) {
    auto *newNode = new TreapNode<T>(x, priority);
    insert(root, newNode);
}
template<class T>
int Treap<T>::height(TreapNode<T> *node) {
    int height1 = 0, height2 = 0;
    if (node == nullptr) {
        return 0;
    }
    if (node->left) {
        height1 = height(node->left);
    }
    if (node->right) {
        height2 = height(node->right);
    }
    return height2 > height1 ? height2 + 1 : height1 + 1;
}
template<class T>
int Treap<T>::get_max_height() {
    return height(root);
}
TEST(SearchTree, height_test1) {
    SearchTree<int> tree;
    Treap<int> treap;
    tree.insert(5);
    treap.add(5, 11);
    tree.insert(18);
    treap.add(18, 8);
    tree.insert(25);
    treap.add(25, 7);
    tree.insert(50);
    treap.add(50, 12);
    tree.insert(30);
    treap.add(30, 30);
    tree.insert(15);
    treap.add(15, 15);
    tree.insert(20);
    treap.add(20, 10);
    tree.insert(22);
    treap.add(22, 5);
    tree.insert(40);
    treap.add(40, 20);
    tree.insert(45);
    treap.add(45, 9);
    ASSERT_EQ(abs(tree.get_max_height() - treap.get_max_height()), 2);
}
TEST(SearchTree, height_test2) {
    SearchTree<int> tree;
    Treap<int> treap;
    tree.insert(38);
    treap.add(38, 19);
    tree.insert(37);
    treap.add(37, 5);
    tree.insert(47);
    treap.add(47, 15);
    tree.insert(35);
    treap.add(35, 0);
    tree.insert(12);
    treap.add(12, 3);
    tree.insert(0);
    treap.add(0, 42);
    tree.insert(31);
    treap.add(31, 37);
    tree.insert(21);
    treap.add(21, 45);
    tree.insert(30);
    treap.add(30, 26);
    tree.insert(41);
    treap.add(41, 6);
    ASSERT_EQ(abs(tree.get_max_height() - treap.get_max_height()), 2);
}

