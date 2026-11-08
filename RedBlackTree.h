#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <string>
using namespace std;

#define COLOR_BLACK 0
#define COLOR_RED 1

struct RBTNode {
    int color = COLOR_BLACK;
    int value;
    RBTNode* parent = nullptr;
    RBTNode* left_child = nullptr;
    RBTNode* right_child = nullptr;

};

class RedBlackTree {
    public:

    RedBlackTree();
    RedBlackTree(int n);
    RedBlackTree(const RedBlackTree& rbt1);
    ~RedBlackTree();
    RedBlackTree& operator=(const RedBlackTree& rbt1);

    string ToInfixString() const {return ToInfixString(root);};
    string ToPrefixString() const { return ToPrefixString(root);};
    string ToPostfixString() const { return ToPostfixString(root);};
    
    void Insert(int n);
    bool Contains(int n);

    int GetMin();
    int GetMax();
    size_t Size();

    private:
    unsigned long long int numItems = 0;
    RBTNode *root = nullptr;
    string ToInfixString(RBTNode* node) const;
    string ToPrefixString(RBTNode* node) const;
    string ToPostfixString(RBTNode* node) const;
    string NodeToString(RBTNode*) const;
    bool HasLeftChild(RBTNode* node) const;
    bool HasRightChild(RBTNode* node) const;
    bool HasParent(RBTNode* node) const;
    void Insert(int n, RBTNode* node);
    void InsertFixUp(RBTNode* node);
    void RotateLeft(RBTNode* node);
    void RotateRight(RBTNode* node);
    RBTNode* CopySubtree(RBTNode* node, RBTNode* parent);
    void DeleteSubtree(RBTNode* node);
};
#endif