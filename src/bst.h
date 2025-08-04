#ifndef BST_H
#define BST_H

#include <string>

struct Node {
    std::string key;
    Node* left;
    Node* right;
    int height;

    Node(const std::string& str) : key(str), left(nullptr), right(nullptr), height(1) {}
};

class BST {
private:
    Node* root;
    size_t node_count;

    int height(Node* node);
    int getBalanceFactor(Node* node);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    Node* insert(Node* node, const std::string& key);
    Node* search(Node* node, const std::string& key);
    void destroy(Node* node);

public:
    BST();
    ~BST();
    void insert(const std::string& key);
    bool search(const std::string& key);
    size_t size() const;
    size_t get_memory_usage() const;
};

#endif