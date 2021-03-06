#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>

///// List of Depths:  Given a binary tree, design an algorithm which creates a linked list of all the nodes
///// at each depth.  (e.g., if you have a tree with depth D, you'll have D linked lists).

///// Note, nothing was mentioned about maintaining this list.  This is a good thing because this could potentially
///// be quite complicated, unless we're willing to store tons of pointers and perform tons of maintainance operations.


///// This solution is pretty ugly - I'd rather not have functions with so many input arguments; I'd also rather
///// the functions be shorter.  BUT I just wanted to get the algorithm up and running.  Not too worried about fixing
///// this one up - this was an easy enough problem so there's not much to learn from making it super readable and modular.




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



Node * createTreeFromArray(int * ourArray, int start, int end, int depth = 0)
{
	if (start > end)
		return nullptr;
	int length = end + 1 - start;
	int midIndex = start + length / 2;
	int data = ourArray[midIndex];
	
	Node * current = new Node(data);

//	std::cout << "The Node with m_data = " << current->m_data << " occurs at depth " << depth << " in the tree.\n";
	
	Node * left = createTreeFromArray(ourArray, start, midIndex - 1, depth + 1);
	Node * right = createTreeFromArray(ourArray, midIndex + 1, end, depth + 1);

	current->m_left = left;
	current->m_right = right;
	if (left != nullptr)
		left->m_parent = current;
	if (right != nullptr)
		right->m_parent = current;

	return current;
}



void treeToVectorOfDepthLists(Node * someNode, int depth, std::vector<std::list<Node>> &ourVec)
{
	// Follow the in-order traversal because the depth of the call stack is the depth of the current node.

	if (someNode == nullptr)
		return;

	treeToVectorOfDepthLists(someNode->m_left, depth + 1, ourVec);
	ourVec[depth].push_back(*someNode);
//	std::cout << "The Node with m_data " << someNode->m_data << " occurs at depth " << depth << " in the tree.\n";
	treeToVectorOfDepthLists(someNode->m_right, depth + 1, ourVec);
}


int main()
{
	std::vector<std::list<Node>> depthLists;
	depthLists.resize(10);

	int myArray[20];
	for (int i = 0; i < 20; i++)
		myArray[i] = i;

	Node * head = createTreeFromArray(myArray, 0, 19);
	treeToVectorOfDepthLists(head, 0, depthLists);

	for (unsigned i = 0; i < depthLists.size(); i++)
		for (auto it = depthLists[i].begin(); it != depthLists[i].end(); it++)
		{
			Node current = *it;

			std::cout << "In the depth " << i << " depthList.  The current m_data value is "
				<< current.m_data << ".\n";
		}
	
	
    return 0;
}

