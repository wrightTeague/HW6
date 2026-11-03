#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <string>
using namespace std;

struct RBTNode {
    int color = 0; // black by default
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
    string ToInfixString(RBTNode* root) const;
    string ToPrefixString(RBTNode* root) const;
    string ToPostfixString(RBTNode* root) const;
    string NodeToString(RBTNode*) const;
};
#endif