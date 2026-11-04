#include <string>
#include <stdexcept>
#include "RedBlackTree.h"

using namespace std;

RedBlackTree::RedBlackTree() {
    root = nullptr;

}

RedBlackTree::RedBlackTree(int n) {
    Insert(n);
}

RedBlackTree::RedBlackTree(const RedBlackTree& rbt1) {
    // TODO
}

RedBlackTree::~RedBlackTree() {
    // TODO
}

void RedBlackTree::Insert(int n) {
    if (root == nullptr) {
        RBTNode *temp = new RBTNode();
        temp->value = n;
        root = temp;
        numItems++;
    } else {
        Insert(n, root);
    }


}

bool RedBlackTree::Contains(int n) {
    // TODO
    return false;
}

int RedBlackTree::GetMin() {
    // TODO
    return 0;
}

int RedBlackTree::GetMax() {
    // TODO
    return 0;
}

size_t RedBlackTree::Size() {
    // TODO
    return 0;
}

string RedBlackTree::ToInfixString(RBTNode* node) const {
    if (node == nullptr) {
        return "";
    }
    return ToInfixString(node->left_child) + NodeToString(node) + ToInfixString(node->right_child);
}

string RedBlackTree::ToPrefixString(RBTNode* node) const {
    if (node == nullptr) {
        return "";
    }
    return NodeToString(node) + ToPrefixString(node->left_child) + ToPrefixString(node->right_child);
}

string RedBlackTree::ToPostfixString(RBTNode* node) const {
    if (node == nullptr) {
        return "";
    }
    return ToPostfixString(node->left_child) + ToPostfixString(node->right_child) + NodeToString(node);
}

string RedBlackTree::NodeToString(RBTNode* node) const {
    string color;
    if (node->color == COLOR_BLACK) {
        color = "B";
    } else {
        color = "R";
    }
    return " " + color + to_string(node->value) + " ";
}

bool RedBlackTree::HasLeftChild(RBTNode* node) const {
    return node->left_child != nullptr;
}

bool RedBlackTree::HasRightChild(RBTNode* node) const {
    return node->right_child != nullptr;
}

bool RedBlackTree::HasParent(RBTNode* node) const {
    return node->parent != nullptr;
}

void RedBlackTree::Insert(int n, RBTNode* node) {
    if (n == node->value) {
        throw invalid_argument("Value: " + to_string(n) + " already exists inside the tree.");
    }
    if (n < node->value) {
        if (HasLeftChild(node)) {
            Insert(n, node->left_child);
        } else {
            RBTNode* temp = new RBTNode();
            temp->color = COLOR_RED;
            temp->value = n;
            temp->parent = node;
            node->left_child = temp;
            numItems++;
        }
    } else {
        if (HasRightChild(node)) {
            Insert(n, node->right_child);
        } else {
            RBTNode* temp = new RBTNode();
            temp->color = COLOR_RED;
            temp->value = n;
            temp->parent = node;
            node->right_child = temp;
            numItems++;

        }
    }
}