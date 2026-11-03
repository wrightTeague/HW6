#include <string>
#include "RedBlackTree.h"

using namespace std;

RedBlackTree::RedBlackTree() {
    root = nullptr;

}

RedBlackTree::RedBlackTree(int n) {
    // TODO
}

RedBlackTree::RedBlackTree(const RedBlackTree& rbt1) {
    // TODO
}

RedBlackTree::~RedBlackTree() {
    // TODO
}

void RedBlackTree::Insert(int n) {
    RBTNode *temp = new RBTNode();
    temp->value = n;
    root = temp;
    numItems++;
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

string RedBlackTree::ToInfixString(RBTNode* root) const {
    if (root == nullptr) {
        return "";
    }
    return NodeToString(root);
}

string RedBlackTree::ToPrefixString(RBTNode* root) const {
    // TODO
    return "";
}

string RedBlackTree::ToPostfixString(RBTNode* root) const {
    // TODO
    return "";
}

string RedBlackTree::NodeToString(RBTNode* node) const {
    string color;
    if (node->color == 0) {
        color = "B";
    } else {
        color = "R";
    }
    return " " + color + to_string(node->value) + " ";
}
