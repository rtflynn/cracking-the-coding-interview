#include "stdafx.h"
#include <iostream>

///// Successor:  Write an algorithm to find the 'next' node (i.e. in-order successor) of a given
///// node in a binary search tree.  You may assume that each node has a link to its parent.


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


Node * leftmostNodeInSubtree(Node * someNode)
{
	Node * current = someNode;
	while (current->m_left != nullptr)
		current = current->m_left;
	return current;
}


Node * successor(Node * someNode)			// Quite an ugly implementation!
{
	Node * current = someNode;
	if (current->m_right != nullptr)	// then the successor is guaranteed to be in the right subtree
		return leftmostNodeInSubtree(current->m_right);

	else if (current->m_parent == nullptr)	// then we're already looking at the rightmost Node.
		return nullptr;
	
	if (current->m_parent->m_data > current->m_data)	// the parent is the successor
		return current->m_parent;
		
	while (current->m_parent->m_data < current->m_data)
	{										// go up the tree until we reach a 'up-right' edge
		current = current->m_parent;
		if (current->m_parent == nullptr)
			return nullptr;					// If we can only go up-left, then we're already at the rightmost Node
	}
	
	current = current->m_parent;		// We can finally go to the right

	return current;
}



int main()
{
    return 0;
}

