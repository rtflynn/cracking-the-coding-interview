#include "stdafx.h"
#include <iostream>

///// Validate BST: Implement a function to check if a binary tree is a binary search tree.

// Our tree is a binary search tree if, for every node, everything in the left subtree
// has m_value less than that of the current node, and everything in the right subtree
// has m_value larger than that of the current node.  

class Node
{
public:
	Node * m_left = nullptr;
	Node * m_right = nullptr;
	Node * m_parent = nullptr;
	int m_data;
public:
	Node(int data = 0) : m_data(data) {}
};


bool isBST(Node * someNode)
{
	if (someNode == nullptr)
		return true;
	if (!isBST(someNode->m_left) or !isBST(someNode->m_right))
		return false;
	bool leftGood;
	bool rightGood;
	if (someNode->m_left == nullptr)
		leftGood = true;
	else
		leftGood = (someNode->m_left->m_data <= someNode->m_data);

	if (someNode->m_right == nullptr)
		rightGood = true;
	else
		rightGood = (someNode->m_right->m_data >= someNode->m_data);

	return (leftGood and rightGood);
}






int main()
{
	// Given a Node pointer  nodePtr, call isBST(nodePtr) to determine if the tree rooted at nodePtr
	// is a binary search tree.  This doesn't determine whether the tree is balanced.
	// Simple example below.  Change the values and/or the number of nodes to experiment.


	Node * head = new Node(2);
	Node * left = new Node(3);
	Node * right = new Node(18);

	head->m_left = left;
	head->m_right = right;
	left->m_parent = head;
	right->m_parent = head;

	if (isBST(head))
		std::cout << "It's a BST\n";
	else
		std::cout << "It's not a BST\n";




    return 0;
}

