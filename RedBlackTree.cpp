#include <iostream>
#include <cassert>
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

// Copying node by node instead of re-inserting the values keeps the colors and
// shape identical. Re-inserting in a different order could balance differently.
RedBlackTree::RedBlackTree(const RedBlackTree& rbt1) {
    root = CopySubtree(rbt1.root, nullptr);
    numItems = rbt1.numItems;
}

RedBlackTree::~RedBlackTree() {
    DeleteSubtree(root);
}

// Without this, a = b would copy b's root pointer, and both destructors would
// delete the same nodes.
RedBlackTree& RedBlackTree::operator=(const RedBlackTree& rbt1) {
    if (this != &rbt1) {
        DeleteSubtree(root);
        root = CopySubtree(rbt1.root, nullptr);
        numItems = rbt1.numItems;
    }
    return *this;
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
                    // Zig-zag: node is a right child of a left child, which the
                    // provided tests call "Right Left". Rotating the parent
                    // straightens it into the Left Left shape below.
                    node = parent;
                    RotateLeft(node);
                    parent = node->parent;
                }
                // Left Left
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
                    // "Left Right" (node is a left child of a right child)
                    node = parent;
                    RotateRight(node);
                    parent = node->parent;
                }
                // Right Right
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
// Returns a new copy of node and everything below it. parent is passed in
// because the copy needs to point up to the new tree, not the original.
RBTNode* RedBlackTree::CopySubtree(RBTNode* node, RBTNode* parent) {
    if (node == nullptr) {
        return nullptr;
    }
    RBTNode* copy = new RBTNode();
    copy->value = node->value;
    copy->color = node->color;
    copy->parent = parent;
    copy->left_child = CopySubtree(node->left_child, copy);
    copy->right_child = CopySubtree(node->right_child, copy);
    return copy;
}

// Postfix order: both children have to be deleted before the node holding
// the only pointers to them.
void RedBlackTree::DeleteSubtree(RBTNode* node) {
    if (node == nullptr) {
        return;
    }
    DeleteSubtree(node->left_child);
    DeleteSubtree(node->right_child);
    delete node;
}

// Returns the black-height of node's subtree, or -1 if anything below it
// breaks a red-black rule. Only used by the tests, to check that the tree is
// still valid after many inserts.
int RedBlackTree::BlackHeight(RBTNode* node) const {
    if (node == nullptr) {
        // Empty leaves count as black.
        return 1;
    }
    if (node->color == COLOR_RED) {
        if ((HasLeftChild(node) && node->left_child->color == COLOR_RED) ||
            (HasRightChild(node) && node->right_child->color == COLOR_RED)) {
            return -1;
        }
    }
    if ((HasLeftChild(node) && node->left_child->parent != node) ||
        (HasRightChild(node) && node->right_child->parent != node)) {
        return -1;
    }

    int left = BlackHeight(node->left_child);
    int right = BlackHeight(node->right_child);
    if (left == -1 || right == -1 || left != right) {
        return -1;
    }
    if (node->color == COLOR_BLACK) {
        return left + 1;
    }
    return left;
}

// Lives inside the class so it can reach the private helpers. Each test
// builds its own tree, since rotating by hand can leave a tree that breaks
// the red-black rules.
void RedBlackTree::PrivateTests() {
    cout << "Testing Private Methods..." << endl;

    RBTNode black;
    black.value = 8;
    RBTNode red;
    red.value = 42;
    red.color = COLOR_RED;
    assert(NodeToString(&black) == " B8 ");
    assert(NodeToString(&red) == " R42 ");

    RedBlackTree rbt = RedBlackTree();
    rbt.Insert(10);
    rbt.Insert(5);
    rbt.Insert(15);
    rbt.Insert(3);
    rbt.Insert(7);
    assert(rbt.ToPrefixString() == " B10  B5  R3  R7  B15 ");

    assert(rbt.HasLeftChild(rbt.root));
    assert(rbt.HasRightChild(rbt.root));
    assert(!rbt.HasParent(rbt.root));
    RBTNode* fifteen = rbt.root->right_child;
    assert(rbt.HasParent(fifteen));
    assert(!rbt.HasLeftChild(fifteen));
    assert(!rbt.HasRightChild(fifteen));
    assert(rbt.BlackHeight(rbt.root) == 3);

    // 5 moves up to the root and 7 switches from 5's right to 10's left.
    rbt.RotateRight(rbt.root);
    assert(rbt.ToPrefixString() == " B5  R3  B10  R7  B15 ");
    assert(rbt.root->value == 5);
    assert(rbt.root->parent == nullptr);
    RBTNode* ten = rbt.root->right_child;
    assert(ten->parent == rbt.root);
    assert(ten->left_child->value == 7);
    assert(ten->left_child->parent == ten);
    // Rotating changes the shape without recoloring, so the rules break.
    assert(rbt.BlackHeight(rbt.root) == -1);

    rbt.RotateLeft(rbt.root);
    assert(rbt.ToPrefixString() == " B10  B5  R3  R7  B15 ");
    assert(rbt.root->value == 10);
    assert(rbt.root->parent == nullptr);
    assert(rbt.root->left_child->right_child->parent == rbt.root->left_child);
    assert(rbt.BlackHeight(rbt.root) == 3);

    // Rotating below the root has to relink the parent instead of root.
    RBTNode* five = rbt.root->left_child;
    rbt.RotateLeft(five);
    assert(rbt.root->value == 10);
    assert(rbt.root->left_child->value == 7);
    assert(rbt.root->left_child->parent == rbt.root);
    assert(rbt.ToPrefixString() == " B10  R7  B5  R3  B15 ");

    RBTNode* copy = CopySubtree(rbt.root, nullptr);
    assert(copy != rbt.root);
    assert(copy->parent == nullptr);
    assert(copy->left_child->parent == copy);
    assert(copy->left_child->left_child->parent == copy->left_child);
    assert(ToPrefixString(copy) == rbt.ToPrefixString());
    DeleteSubtree(copy);

    // A red root with a red child, and two sides with different black counts.
    RBTNode a;
    a.value = 2;
    a.color = COLOR_RED;
    RBTNode b;
    b.value = 1;
    b.color = COLOR_RED;
    b.parent = &a;
    a.left_child = &b;
    assert(BlackHeight(&a) == -1);
    b.color = COLOR_BLACK;
    assert(BlackHeight(&a) == -1);
    assert(BlackHeight(nullptr) == 1);

    RedBlackTree big = RedBlackTree();
    for (int i = 1; i <= 1000; i++) {
        big.Insert(i);
        assert(big.BlackHeight(big.root) != -1);
    }
    big = RedBlackTree();
    for (int i = 1000; i >= 1; i--) {
        big.Insert(i);
    }
    assert(big.BlackHeight(big.root) != -1);
    // A shuffled order hits all four rotation cases many times.
    for (int i = 0; i < 1000; i++) {
        int value = (i * 7919) % 1009 + 2000;
        if (!big.Contains(value)) {
            big.Insert(value);
        }
    }
    assert(big.BlackHeight(big.root) != -1);
    assert(big.root->color == COLOR_BLACK);

    cout << "PASSED!" << endl << endl;
}
