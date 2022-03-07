//Muhammed Orhun Gale - 26754

#include "AABB.h"
#include "BVHTreeNode.h"
#include <vector>
#include <iostream>
#include <unordered_map>
#ifndef _BVH_TREE
#define _BVH_TREE

class BVHTree {
private:
	BVHTreeNode *root;
	std::unordered_map<std::string, BVHTreeNode *> map;

	void adjustBox(BVHTreeNode*);					//Adjusts all ancestor boxes of a hitbox
	BVHTreeNode* min2Insert(BVHTreeNode* &) const;	//Finds a suitable node for new insertion
	char whichDirection(BVHTreeNode* &) const;		//Finds which children of current node's parent is the current node
	void makeEmpty(BVHTreeNode*& );					//Deletes all nodes of the tree recursively
	void searchCollusion(BVHTreeNode*, AABB, std::vector<std::string>&);	//Search names of hitboxes that collides with a given projectile recursively


public:
	BVHTree();										//Default constructor
	~BVHTree();										//Destructor
	void printNode(std::ostream &out, BVHTreeNode *, int level);	
	void addBVHMember(AABB objectArea, std::string name);		//Adds a new hitbox to the current agent
	void moveBVHMember(std::string name, AABB newLocation);		//Moves a hitbox to specified place
	void removeBVHMember(std::string name);						//Removes given hitbox of the current agent
	std::vector<std::string> getCollidingObjects(AABB object);	//Finds all hitboxes that collides with a given projectile
	friend std::ostream &operator<<(std::ostream &out, BVHTree &tree);
};
#endif