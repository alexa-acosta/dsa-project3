#include "bst.h"
#include <algorithm>

// constructor
BST::BST() : root(nullptr), node_count(0) {}

BST::~BST() {
    destroy(root);
}

void BST::destroy(Node* node) {
    if (node) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

int BST::height(Node* node) {
    if (!node) {
        return 0;
    }
    return node->height;
}

int BST::getBalanceFactor(Node* node) {
    if (!node) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

Node* BST::rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // rotations
    x->right = y;
    y->left = T2;

    // update heights
    y->height = 1 + std::max(height(y->left), height(y->right));
    x->height = 1 + std::max(height(x->left), height(x->right));

    return x;
}

Node* BST::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // rotations
    y->left = x;
    x->right = T2;

    // update heights
    x->height = 1 + std::max(height(x->left), height(x->right));
    y->height = 1 + std::max(height(y->left), height(y->right));

    return y;
}

Node* BST::insert(Node* node, const std::string& key) {
    // standard BST insertion
    if (!node) {
        node_count++; 
        return new Node(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;
    }

    // update height of the current node
    node->height = 1 + std::max(height(node->left), height(node->right));

    // get balance factor
    int balance = getBalanceFactor(node);

    // perform rotations if unbalanced
    // left left case
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    // right right case
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    // left right case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // right left case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* BST::search(Node* node, const std::string& key) {
    if (!node || node->key == key) {
        return node;
    }
    if (key < node->key) {
        return search(node->left, key);
    }
    return search(node->right, key);
}

void BST::insert(const std::string& key) {
    root = insert(root, key);
}

bool BST::search(const std::string& key) {
    return search(root, key) != nullptr;
}

size_t BST::size() const {
    return node_count;
}

size_t BST::get_memory_usage() const {
    return sizeof(BST) + node_count * (sizeof(Node) + sizeof(std::string));
}