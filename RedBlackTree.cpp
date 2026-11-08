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
    RBTNode* current = root;
    while (current != nullptr) {
        if (n == current->value) {
            return true;
        }
        if (n < current->value) {
            current = current->left_child;
        } else {
            current = current->right_child;
        }
    }
    return false;
}

int RedBlackTree::GetMin() {
    // No value would be a correct answer here, and returning 0 would look
    // like a real minimum.
    if (root == nullptr) {
        throw invalid_argument("GetMin() called on an empty tree.");
    }
    RBTNode* current = root;
    while (HasLeftChild(current)) {
        current = current->left_child;
    }
    return current->value;
}

int RedBlackTree::GetMax() {
    if (root == nullptr) {
        throw invalid_argument("GetMax() called on an empty tree.");
    }
    RBTNode* current = root;
    while (HasRightChild(current)) {
        current = current->right_child;
    }
    return current->value;
}

size_t RedBlackTree::Size() {
    return numItems;
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
            InsertFixUp(temp);
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
            InsertFixUp(temp);
        }
    }
}

// Inserting a red node can only break one rule: a red node with a red parent.
// Each pass either fixes it with rotations or pushes the problem two levels up.
void RedBlackTree::InsertFixUp(RBTNode* node) {
    while (HasParent(node) && node->parent->color == COLOR_RED) {
        // The parent is red, so it can't be the root, so the grandparent exists.
        RBTNode* parent = node->parent;
        RBTNode* grandparent = parent->parent;

        if (parent == grandparent->left_child) {
            RBTNode* uncle = grandparent->right_child;
            if (uncle != nullptr && uncle->color == COLOR_RED) {
                // Red uncle: recolor only. The grandparent turns red, so it may
                // now clash with its own parent, and the loop checks it next.
                parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                node = grandparent;
            } else {
                if (node == parent->right_child) {
                    // LR case: rotate it into the LL shape first.
                    node = parent;
                    RotateLeft(node);
                    parent = node->parent;
                }
                // LL case
                parent->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                RotateRight(grandparent);
            }
        } else {
            // Mirror image of the branch above.
            RBTNode* uncle = grandparent->left_child;
            if (uncle != nullptr && uncle->color == COLOR_RED) {
                parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                node = grandparent;
            } else {
                if (node == parent->left_child) {
                    // RL case
                    node = parent;
                    RotateRight(node);
                    parent = node->parent;
                }
                // RR case
                parent->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                RotateLeft(grandparent);
            }
        }
    }
    // Recoloring can turn the root red; making it black never breaks anything.
    root->color = COLOR_BLACK;
}

// node's right child moves up into node's place, and node becomes its left child.
void RedBlackTree::RotateLeft(RBTNode* node) {
    RBTNode* child = node->right_child;

    // child's left subtree sits between node and child in value, so it moves
    // over to become node's right subtree.
    node->right_child = child->left_child;
    if (HasLeftChild(child)) {
        child->left_child->parent = node;
    }

    child->parent = node->parent;
    if (!HasParent(node)) {
        root = child;
    } else if (node == node->parent->left_child) {
        node->parent->left_child = child;
    } else {
        node->parent->right_child = child;
    }

    child->left_child = node;
    node->parent = child;
}

// Mirror image of RotateLeft.
void RedBlackTree::RotateRight(RBTNode* node) {
    RBTNode* child = node->left_child;

    node->left_child = child->right_child;
    if (HasRightChild(child)) {
        child->right_child->parent = node;
    }

    child->parent = node->parent;
    if (!HasParent(node)) {
        root = child;
    } else if (node == node->parent->right_child) {
        node->parent->right_child = child;
    } else {
        node->parent->left_child = child;
    }

    child->right_child = node;
    node->parent = child;
}