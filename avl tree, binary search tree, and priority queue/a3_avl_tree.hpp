#ifndef A3_AVL_TREE_HPP
#define A3_AVL_TREE_HPP

#include "a3_binary_search_tree.hpp"

class AVLTree: public BinarySearchTree
{
public:
	// Overriden insert and remove functions 
	// Do not modify these definitions
    bool insert(DataType val);
    bool remove(DataType val);

	// Define additional functions and attributes that you need below
	
	// Balance AVL Tree
	void balanceAVLTree();
	// Find unblanaced node
	Node* findNode(Node* n);
	// Rotate right
	void rotateRight(Node* n, bool right, bool isRoot);
	// Rotate left
	void rotateLeft(Node* n, bool right, bool isRoot);
	
};
#endif

