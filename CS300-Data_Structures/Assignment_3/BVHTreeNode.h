//Muhammed Orhun Gale - 26754

#include<vector>
#include "AABB.h"
#ifndef _BVH_TREE_NODE
#define _BVH_TREE_NODE

struct BVHTreeNode{
    BVHTreeNode *parent, *leftChild, *rightChild;
    AABB aabb;
    std::string name;
    bool isLeaf;
    BVHTreeNode(AABB _aabb, std::string _name, bool _isLeaf): aabb(_aabb), name(_name), isLeaf(_isLeaf){
        parent = leftChild = rightChild = 0;
    }
};
#endif