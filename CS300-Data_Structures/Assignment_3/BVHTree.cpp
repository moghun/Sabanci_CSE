//Muhammed Orhun Gale - 26754

#include "BVHTree.h"

//TODO:	Default constructor
BVHTree::BVHTree()
{
	this->root = nullptr;
	
	std::unordered_map<std::string, BVHTreeNode*> aMap; //Creates hash table
	this->map = aMap;
}
//END:	BVHTree constructed via setting root nullptr and created its hash table

//TODO:	Destructor
BVHTree::~BVHTree()
{
	makeEmpty(this->root); //Calls static makeEmpty function that deletes nodes recursively
}
//END:	All nodes of tree which are dynamically allocated in the memory are deleted

//TODO: Adds a new hitbox to the respective agent's BVHTree
void BVHTree::addBVHMember(AABB objectArea, std::string name)
{
	if (this->root == nullptr) //If tree is empty ,i.e., the object that we insert is the first node
	{
		BVHTreeNode* newNode = new BVHTreeNode(objectArea, name, true); //Create a new node
		this->root = newNode;			//Set tree's root as new node
		(this->map)[name] = newNode;	//Insert its location in the heap to the hash table
	}

	else if ((this->root)->isLeaf == true)  //If adding object is the second object that we insert into the tree
										    //If the current root is leaf this means there exist only one node in the tree
	{
		BVHTreeNode* oldNode = this->root;	//Node that we added first
		BVHTreeNode* newNode = new BVHTreeNode(objectArea, name, true); //Create a new node
		(this->map)[name] = newNode;		//Insert its location in the heap to the hash table

		BVHTreeNode* newBranch = new BVHTreeNode(((oldNode->aabb) + (objectArea)), "branch", false); //Create a new branch node that will be 
																									 //		two leaf nodes parent, set its size as union of leafs
		this->root = newBranch;				//Set new root as freshly created branch
		oldNode->parent = newBranch;		//Set new parent node
		newNode->parent = newBranch;		//Set new parent node
		newBranch->leftChild = newNode;		//Set children of branch
		newBranch->rightChild = oldNode;	//Set children of branch
	}

	else {									//If there exist more than 2 leaf nodes in the tree
		BVHTreeNode* newNode = new BVHTreeNode(objectArea, name, true); //Create a new node
		(this->map)[name] = newNode;	//Insert its location in the heap to the hash table

		BVHTreeNode* insertionNode = min2Insert(newNode); //Find a suitable place to insert new leaf
		BVHTreeNode* newBranch = new BVHTreeNode(((insertionNode->aabb) + (objectArea)), "branch", false);	//Create new branch to set insertionNode and newNode's parent
		newBranch->parent = insertionNode->parent;		  //Set newBranch's parent as insertionNode's parent
		
		char direction = whichDirection(insertionNode);   //Find which children of insertion node's parent is the insertion node 
		if (direction == 'r')
		{
			(insertionNode->parent)->rightChild = newBranch;
		}

		else {
			(insertionNode->parent)->leftChild = newBranch;
		}

		insertionNode->parent = newBranch;	//Set new parent node
		newNode->parent = newBranch;		//Set new parent node
		newBranch->leftChild = newNode;		//Set children of branch
		newBranch->rightChild = insertionNode; //Set children of branch

		adjustBox(newBranch->parent);		//Adjust each ancestor's size 
	}
}

//TODO:	Moves a hitbox to the specified location in the space
void BVHTree::moveBVHMember(std::string name, AABB newLocation)
{
	BVHTreeNode* node2bMove = (this->map)[name]; //Find the location of the node that will be moved
	BVHTreeNode* siblingNode;					 //Find its sibling to calculate changes in the area when the node is moved
	
	char direction = whichDirection(node2bMove); //Find which children of moving node's parent is the moving node 	
	if (direction == 'r')
	{
		siblingNode = node2bMove->parent->leftChild;
	}

	else {
		siblingNode = node2bMove->parent->rightChild;
	}

	AABB uni = newLocation + siblingNode->aabb; //Box that moving box and its sibling forms after hitbox is moved
	if (!(uni != node2bMove->parent->aabb))		//If the new box is inside in the current box or equal to it
	{
		node2bMove->aabb = newLocation;			//Just change the location of the box
	}

	else {										//If new box is on outside of the current box
		this->removeBVHMember(name);			//Remove moving box from the agent
		this->addBVHMember(newLocation, name);	//Then insert it back to the new location in order to adjust outter box size
	}
}
//END:	Hitbox is moved

//TODO:	Remove a given hitbox
void BVHTree::removeBVHMember(std::string name)
{
	BVHTreeNode* node2bDeleted = (this->map)[name]; //Find the location of the node that will be deleted
	
	if (node2bDeleted->parent == nullptr)			//If there exist only one node in the tree
	{
		delete node2bDeleted;
		node2bDeleted = nullptr;
		(this->map).erase(name);					//Delete its entry from the hash table
	}

	else {											//If there exist more than one node
		if (node2bDeleted->parent->parent == nullptr)	//If there exist exactly 2 leaf nodes and 1 branch node in the tree
		{
			char direction = whichDirection(node2bDeleted); //Find which children of deletion node's parent is the deletion node

			if (direction == 'r')
			{
				this->root = node2bDeleted->parent->leftChild;
				this->root->parent = nullptr;				//Set sibling node as root of the tree
			}

			else {
				this->root = node2bDeleted->parent->rightChild;
				this->root->parent = nullptr;				//Set sibling node as root of the tree
			}

			delete node2bDeleted->parent;
			node2bDeleted->parent = nullptr;

			delete node2bDeleted;
			node2bDeleted = nullptr;

			(this->map).erase(name);						//Delete its entry from the hash table
		}

		else {												//If there exist more than 2 leaf nodes
			char direction = whichDirection(node2bDeleted); //Find which children of deletion node's parent is the deletion node
			
			BVHTreeNode* siblingNode;	//Set its sibling node
			if (direction == 'r')
			{
				siblingNode = node2bDeleted->parent->leftChild;
			}

			else {
				siblingNode = node2bDeleted->parent->rightChild;
			}

			delete node2bDeleted;
			node2bDeleted = nullptr; 
			
			BVHTreeNode* oldParent = siblingNode->parent;	
		
			char direction2 = whichDirection(siblingNode->parent);	 //Find which children of deletion node's parent's parent is the deletion node's parent
			if (direction2 == 'r')
			{
				(siblingNode->parent)->parent->rightChild = siblingNode;
			}

			else {
				(siblingNode->parent)->parent->leftChild = siblingNode;
			}

			siblingNode->parent = oldParent->parent;  //Set deleted nodes' parent's parent as the sibling node's parent to complete tree
			delete oldParent;
			oldParent = nullptr;

			adjustBox(siblingNode->parent);	//Adjust each ancestor's size 
			(this->map).erase(name);		//Delete its entry from the hash table
		}
	}
}
//END:	Given hitbox is removed from the tree, also it is deallocated from the heap

//TODO:	Find names of the hitboxes of an agent that is collides with a projectile that its location is given
//		Recursively finds the names of the hitboxes via using searchCollusion function
std::vector<std::string> BVHTree::getCollidingObjects(AABB object)
{
	std::vector<std::string> names; //Create the vector that will be passed by reference
	searchCollusion(this->root, object, names); //Get names of the colliding objects recursively

	return names;
}
//END:	Return the vector that includes names of the hitboxes that collide with the given projectile


void BVHTree::printNode(std::ostream &out, BVHTreeNode *node, int level) {
	if (root == nullptr) return;
	for (int i = 0; i < level; i++) {
		out << "  ";
	}
	if (!node->isLeaf) {
		out << "+ branch || ";
		node->aabb.printAABB(out);
		out << std::endl;
		printNode(out, node->rightChild, level + 1);
		printNode(out, node->leftChild, level + 1);
	}
	else {
		out << "- ";
		if (node->parent) {
			if (node->parent->rightChild == node)
				out << "R ";
			else
				out << "L ";
		}
		out << "- leaf: " << node->name << " || ";
		node->aabb.printAABB(out);
		out << std::endl;
	}
}

std::ostream &operator<<(std::ostream &out, BVHTree &tree) {
	tree.printNode(out, tree.root, 0);
	return out;
}

//TODO: Adjust the size of a box's all ancestors recursively
void BVHTree::adjustBox(BVHTreeNode* current)
{
	if (current == nullptr) //Exit condition
	{
		return;
	}

	current->aabb = (current->rightChild)->aabb + (current->leftChild)->aabb;	//Update box size via taking union of the children
	adjustBox(current->parent);				//Recursively call the function with current nodes parent
}
//END:	Size of all ancestors of a given node is adjusted

//TODO:	Find a suitable place to insert new leaf node
BVHTreeNode* BVHTree::min2Insert(BVHTreeNode* &node2bInserted) const
{
	BVHTreeNode* itr = this->root;	
	while (itr->isLeaf == false)	//Until hit a leaf node
	{
		//Calculate the difference in area to select the direction that gives minimum increase
		int rightSize = AABB::unionArea(node2bInserted->aabb, itr->rightChild->aabb) - (itr->rightChild->aabb).getArea(); 
		int leftSize = AABB::unionArea(node2bInserted->aabb, itr->leftChild->aabb) - (itr->leftChild->aabb).getArea();

		if (rightSize < leftSize) 
		{
			itr = itr->rightChild;
		}

		else {
			itr = itr->leftChild;
		}
	}
	return itr;
}
//END:	Return the place that is suitable to insert new leaf node

//TODO:	Find which children of current node's parent is the current node
char BVHTree::whichDirection(BVHTreeNode* &node) const
{
	BVHTreeNode* parent = node->parent;

	if (parent->leftChild == node)
	{
		return 'l';
	}

	else
	{
		return 'r';
	}
}
//END:	Direction is returned


	//TODO: Recursively finds that if a projectile collides with an agent
	//      If collides with a branch, recursively calls function until find a leaf
	//      Push name of the colliding hitbox (leaf) and return
void BVHTree::searchCollusion(BVHTreeNode* current, AABB location, std::vector<std::string>& nameVector)
{

	if (current->aabb.collide(location) == false) //Exit condition for the case that projectile do not collide with the current node
	{
		return;
	}

	if (current->isLeaf == true)                  //Exit condition for the case that we reach a leaf node
	{
		nameVector.push_back(current->name);
		return;
	}

	searchCollusion(current->leftChild, location, nameVector); //Recursivelly search for collisons in leftChild if we are at a branch node
	searchCollusion(current->rightChild, location, nameVector);//Recursivelly search for collisons in rightChild if we are at a branch node

	return;
}
//END: Names of the hitboxes that collides with the projectile are pushed back to the names vector that is passed by reference 

//TODO: Deletes all nodes of the tree recursively
void BVHTree::makeEmpty(BVHTreeNode*& toDeleted)
{
	if (toDeleted == nullptr)  //Exit condition
	{
		return;
	}

	makeEmpty(toDeleted->leftChild); //Clears left child
	makeEmpty(toDeleted->rightChild);//Clears left child
	delete toDeleted;
	toDeleted = nullptr;
}
//END:  All nodes of the tree is deleted