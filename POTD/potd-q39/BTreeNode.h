#ifndef BTREENODE_H
#define BTREENODE_H

#include <string>
#include <algorithm>
#include <vector>

struct BTreeNode {
    bool is_leaf_=true;
    std::vector<int> elements_;
    std::vector<BTreeNode*> children_;
    BTreeNode() {}
    BTreeNode (std::vector<int> v) {
      this->elements_ = v;
    }
};

std::vector<int> traverse(BTreeNode* root);

std::vector<int> traversehelper(BTreeNode* root, std::vector<int> v);

#endif
