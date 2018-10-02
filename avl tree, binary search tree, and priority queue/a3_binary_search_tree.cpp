// Sunghoon Ahn 20615061

#include "a3_binary_search_tree.hpp"
#include <stdio.h>
#include <iostream>

BinarySearchTree::Node::Node(DataType newval){
	val = newval;		// initialize val to function input newval
	left = NULL;		// initialize pointers to NULL
	right = NULL;
	avlBalance = 0;		// initialize AVL balance to 0
}

BinarySearchTree::BinarySearchTree(){
	root_ = NULL;		// initialize root to NULL
	size_ = 0;			// initialize size to 0
}

BinarySearchTree::~BinarySearchTree(){
	deleteTree(root_);	// recursivley delete all of tree except root

	delete root_;		// delete root node
	root_ = NULL;		// set root pointer to NULL
	size_ = 0;
}

void BinarySearchTree::deleteTree(Node* n){
	if (!root_)			// return if root
		return;

	if (n->left)		// if left child exists
	{
		deleteTree(n->left);	// call deleteTree on left subtree
		delete n->left;			// delete left node
		n->left = NULL;			// set left pointer to NULL
	}
	if (n->right)		// if right child exists
	{
		deleteTree(n->right);	// call deleteTree on right subtree
		delete n->right;		// delete right node
		n->right = NULL;		// set right pointer to NULL
	}
}

unsigned int BinarySearchTree::size() const{
	return size_;		// return size
}

BinarySearchTree::DataType BinarySearchTree::max() const{
	Node* curNode = root_;		// create temporary node

	while (curNode->right)		// iterate through tree to find right most node
		curNode = curNode->right;

	return curNode->val;		// return value of right most node
}

BinarySearchTree::DataType BinarySearchTree::min() const{
	Node* curNode = root_;		// create temporary node

	while (curNode->left)		// iterate through tree to find left most node
		curNode = curNode->left;

	return curNode->val;		// return value of left mose node
}

unsigned int BinarySearchTree::depth() const{
	return curDepth(root_);		// return depth from recursive function
}

int BinarySearchTree::curDepth(Node* n) const{
	if (!n->left && !n->right)
		return 0;								// return 0 if leaf
	else if (n->left && !n->right)
		return curDepth(n->left) + 1;			// return depth of left child + 1 given that left child exists but right does not
	else if (n->right && !n->left)
		return curDepth(n->right) + 1;			// return depth of right child + 1 given that right child exists but left does not
	else if (curDepth(n->left) >= curDepth(n->right))
		return curDepth(n->left) + 1;			// return depth of left child + 1 given that depth of left child is greater than depth of right child
	else
		return curDepth(n->right) + 1;			// return depth of right child + 1 given that depth of right child is greater than depth of left child
}

void BinarySearchTree::printRecursive(Node* n) const{
	std::cout << n->val << " ";					// recursive print function (in order) which prints itself
	if (n->left)
		printRecursive(n->left);				// calls print on left child given that left child exists

	if (n->right)
		printRecursive(n->right);				// calls print on right child given that right child exists

}

void BinarySearchTree::print() const{
	printRecursive(root_);				// call recursive print
	std::cout << std::endl;				// final new line for visability
}

bool BinarySearchTree::exists(DataType val) const{
	if (!root_)								// return false if tree is empty
		return false;

	Node* curNode = root_;

	while (true)
		if (curNode->val == val)
			return true;					// return true if correct value found
		else if (curNode->val > val)		// check left subtree if search value is less than current node value
			if (curNode->left)				// iterate through list if not leaf node
				curNode = curNode->left;
			else
				return false;				// return false if value not found, but leaf node found
		else								// check right subtree if search value is greater than current node value
			if (curNode->right)				// iterate through list if not leaf node
				curNode = curNode->right;
			else
				return false;				// return false if value not found, but leaf node found
}

BinarySearchTree::Node* BinarySearchTree::getRootNode(){
	return root_;				// return root
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress(){
	return &root_;				// return root address
}

bool BinarySearchTree::insert(DataType val){
	if (!root_){				// if tree is originally empty
		root_ = new Node(val);	// new node of value val
		size_++;
		return true;
	}

	Node* curNode = root_;

	while (true)				// iterates through to find where new node should be placed
		if (curNode->val == val)	// return false if value already exists
			return false;
		else if (curNode->val > val)	// if value of current node is greater than new value
			if (curNode->left)			// continue search along left subtree for location
				curNode = curNode->left;
			else						// or create new node there if no node exists
			{
				curNode->left = new Node(val);	// new node of value val
				size_++;
				return true;
			}
		else							// if value of current node is less than new value
			if (curNode->right)			// continue search along right subtree for location
				curNode = curNode->right;
			else						// or create new node there if no node exists
			{
				curNode->right = new Node(val);	// new node of value val
				size_++;
				return true;
			}
}

bool BinarySearchTree::remove(DataType val){
	if (!root_)						// return false if tree is empty
		return false;

	Node* prevNode = root_;			// previous node to curNode
	Node* curNode = root_;			// temporary node used to find node with value val
	bool right = 0;					// bool to indicate if previous node is pointing right to current node
	bool found = 0;					// bool to indicate if correct value was found

	while (!found)					// continue to loop value not found
	{
		if (curNode->val == val)	// value found so set bool to 1 to end while loop
			found = 1;
		else if (curNode->val > val)	// if val is less than value of current node
			if (curNode->left)			// continue search through left subtree
			{
				prevNode = curNode;
				right = 0;
				curNode = curNode->left;
			}
			else						// or return false if value does not exist (leaf not encountered before value found)
				return false;
		else							// if val is greater than value of current node
			if (curNode->right)			// continue search through right subtree
			{
				prevNode = curNode;
				right = 1;
				curNode = curNode->right;
			}
			else						// or return false if value does not exist (leaf not encountered before value found)
				return false;
	}
	// each of the following cases will also have three subcases for if the current node is the root, if the previous node is pointing from the right, or if the previous node is pointing from the left
	if (!curNode->right && !curNode->left)		// case where no child exists
	{
		if (curNode == root_)					// set respective pointers to NULL
			root_ = NULL;
		else if (right)
			prevNode->right = NULL;
		else
			prevNode->left = NULL;

		delete curNode;							// delete Node
		curNode = NULL;							// set curNode pointer to NULL
	}
	else if (!curNode->right)					// case where only left child exists
	{
		if (curNode == root_)					// set respective pointers to left child of curNode
			root_ = curNode->left;
		else if (right)
			prevNode->right = curNode->left;
		else
			prevNode->left = curNode->left;

		delete curNode;							// delete Node
		curNode = NULL;							// set curNode pointer to NULL
	}
	else if (!curNode->left)					// case where only right child exists
	{
		if (curNode == root_)					// set respective pointers to right child of curNode
			root_ = curNode->right;
		else if (right)
			prevNode->right = curNode->right;
		else
			prevNode->left = curNode->right;

		delete curNode;							// delete Node
		curNode = NULL;							// set curNode pointer to NULL
	}
	else										// case where both children exist
	{
		Node* temp = curNode->right;
		Node* tempPrev = temp;

		while (temp->left)						// search for left most child in right subtree
		{
			tempPrev = temp;
			temp = temp->left;
		}

		if (temp == tempPrev)					// implies that right child of current node is the most left most child
		{
			if (curNode == root_)				// set new right and left subtrees of respective pointers
			{
				root_ = curNode->right;
				root_->left = curNode->left;
			}
			else if (right)
			{
				prevNode->right = curNode->right;
				prevNode->right->left = curNode->left;
			}
			else
			{
				prevNode->left = curNode->right;
				prevNode->left->left = curNode->left;
			}

			delete curNode;						// delete Node
			curNode = NULL;						// set curNode pointer to NULL
		}
		else
		{
			if (temp->right)					// check if left most node has right subtree
				tempPrev->left = temp->right;	// if yes, point to it from previous node
			else
				tempPrev->left = NULL;			// else set it to NULL

			if (curNode == root_)				// replace curNode with left most node
				root_ = temp;
			else if (right)
				prevNode->right = temp;
			else
				prevNode->left = temp;

			temp->left = curNode->left;			// set left and right subtrees of new curNode to those of old curNode
			temp->right = curNode->right;

			delete curNode;						// delete Node
			curNode = NULL;						// set curNode pointer to NULL
		}
	}

	size_--;
	return true;
}

void BinarySearchTree::updateNodeBalance(Node* n){
	if (!n->left && !n->right)
		n->avlBalance = 0;								// if node is leaf, AVL balance is 0
	else if (n->left && !n->right)
	{
		n->avlBalance = curDepth(n->left) + 1;			// if right child does not exist but left does, AVL balance is depth of left child + 1
		updateNodeBalance(n->left);						// call update node balance on left subtree
	}
	else if (n->right && !n->left)
	{
		n->avlBalance = (curDepth(n->right) + 1) * -1;	// if left child does not exist but right does, AVL balance is depth of negative (right child + 1)
		updateNodeBalance(n->right);					// call update node balance on right subtree
	}
	else
	{
		n->avlBalance = curDepth(n->left) - curDepth(n->right);	// if both subtrees exist, AVL balance is left depth - right depth
		updateNodeBalance(n->left);						// call update node balance on left subtree
		updateNodeBalance(n->right);					// call update node balance on right subtree
	}
}
