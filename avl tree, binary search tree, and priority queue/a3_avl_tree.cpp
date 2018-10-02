// Sunghoon Ahn 20615061

#include "a3_avl_tree.hpp"
#include <stdio.h>
#include <iostream>
#include <cmath>

bool AVLTree::insert(DataType val){
	if (!BinarySearchTree::insert(val))			// binary search tree insert without balance
		return false;
	BinarySearchTree::updateNodeBalance(BinarySearchTree::getRootNode());	// update node balance so next function will work
	balanceAVLTree();														// balance tree
	BinarySearchTree::updateNodeBalance(BinarySearchTree::getRootNode());	// update node balance again incase balance needs to be checked
	return true;
}

bool AVLTree::remove(DataType val){
	if (!BinarySearchTree::remove(val))			// binary search tree remove without balance
		return false;
	if (!size())								// return true of no balancing required becasue empty tree
		return true;
	BinarySearchTree::updateNodeBalance(BinarySearchTree::getRootNode());	// update node balance so next function will work
	balanceAVLTree();														// balance tree
	BinarySearchTree::updateNodeBalance(BinarySearchTree::getRootNode());	// update node balance again incase balance needs to be checked
	return true;
}

void AVLTree::balanceAVLTree(){
	Node* temp = findNode(getRootNode());			// find first node from root with AVL balance greater than 1

	if (!getRootNode() || !temp)					// return if node not found or root does not exist
		return;

	Node* prevNode = getRootNode();
	DataType tempVal = temp->val;

	bool right = 0;									// bool to keep track of if previous node is pointing to current node from right
	bool isRoot = 0;								// bool to keep track of if current node is root

	if (temp == prevNode)
		isRoot = 1;

	if (!isRoot)									// iterate through tree to find previous node since findNode function only returns curent node
	{
		while (prevNode->right != temp && prevNode->left != temp)
			if (prevNode->val > tempVal)
				prevNode = prevNode->left;
			else
				prevNode = prevNode->right;
	}

	bool found = 0;

	while (!found)									// ensure that both direct children of current node have absolute value of AVL balance less than 2
	{
		if (temp->avlBalance == 2 && abs(temp->left->avlBalance) > 1)			// if child of current node has absolute AVL balance greater than 2
		{																		// child becomes new current node
			isRoot = 0;
			prevNode = temp;
			temp = temp->left;
		}
		else if (temp->avlBalance == -2 && abs(temp->right->avlBalance) > 1)	// if child of current node has absolute AVL balance greater than 2
		{																		// child becomes new current node
			isRoot = 0;
			prevNode = temp;
			temp = temp->right;
		}
		else
			found = 1;
	}

	if (prevNode->right == temp)										// check if previous node is pointing to current node from right
		right = 1;

	if (temp->avlBalance == 2 && temp->left->avlBalance >= 0)			// Single right
		rotateRight(prevNode, right, isRoot);
	else if (temp->avlBalance == 2 && temp->left->avlBalance <= 0)		// Double left-right
	{
		rotateLeft(temp, 0, 0);
		rotateRight(prevNode, right, isRoot);
	}
	else if (temp->avlBalance == -2 && temp->right->avlBalance <= 0)	// Single left
		rotateLeft(prevNode, right, isRoot);
	else if (temp->avlBalance ==-2 && temp->right->avlBalance >= 0)		// Double right-left
	{
		rotateRight(temp, 1, 0);
		rotateLeft(prevNode, right, isRoot);
	}
}

BinarySearchTree::Node* AVLTree::findNode(Node* n){
	if (abs(n->avlBalance) > 1)										// return pointer if node has absolute value of AVl balance greater than 1
		return n;
	if (!n->left && !n->right)
		return NULL;												// return NULL for node with no children
	else if (n->left && !n->right)
		return findNode(n->left);									// return function called on left child if right child does not exist
	else if (!n->left && n->right)
		return findNode(n->right);									// return function called on right child if left child does not exist
	else if (abs(n->left->avlBalance) >= abs(n->right->avlBalance))
		return findNode(n->left);									// return function called on left child if left child has more imbalanced subtrees
	else
		return findNode(n->right);									// return function called on right child if right child has more imbalanced subtrees
}

void AVLTree::rotateRight(Node* n, bool right, bool isRoot){
	Node* temp = n;
	Node* curNode = n;

	// following if else does the same thing for three cases: sets previous pointer to left child of current pointer, then current pointer to the child of the previous pointer
	if (isRoot)				// previous pointer is root
	{
		Node** rootPnt = BinarySearchTree::getRootNodeAddress();
		temp = *rootPnt;
		*rootPnt = temp->left;
		curNode = *rootPnt;
	}
	else if (right)			// current pointer is right child of previous pointer
	{
		temp = n->right;
		n->right = temp->left;
		curNode = n->right;
	}
	else					// current pointer is right child of previous pointer
	{
		temp = n->left;
		n->left = temp->left;
		curNode = n->left;
	}

	temp->left = temp->left->right;		// move middle subtree over to other side of current pointer
	curNode->right = temp;				// set right side of current pointer to new right side of tree
}

void AVLTree::rotateLeft(Node* n, bool right, bool isRoot){
	Node* temp = n;
	Node* curNode = n;

	// following if else does the same thing for three cases: sets previous pointer to right child of current pointer, then current pointer to the child of the previous pointer
	if (isRoot)				// previous pointer is root
	{
		Node** rootPnt = BinarySearchTree::getRootNodeAddress();
		temp = *rootPnt;
		*rootPnt = temp->right;
		curNode = *rootPnt;
	}
	else if (right)			// current pointer is right child of previous pointer
	{
		temp = n->right;
		n->right = temp->right;
		curNode = n->right;
	}
	else					// current pointer is right child of previous pointer
	{
		temp = n->left;
		n->left = temp->right;
		curNode = n->left;
	}

	temp->right = temp->right->left;	// move middle subtree over to other side of current pointer
	curNode->left = temp;				// set left side of current pointer to new left side of tree
}
