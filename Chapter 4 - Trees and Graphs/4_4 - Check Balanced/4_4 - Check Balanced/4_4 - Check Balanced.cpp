#include "stdafx.h"
#include <iostream>


///// Check Balanced:  Implement a function to check if a binary tree is balanced.  For the purposes of this question, 
///// a balanced tree is defined to be a tree such that the heights of the two subtrees of any node never
///// differ by more than one.



class Node
{
public:
	Node * m_left = nullptr;
	Node * m_right = nullptr;
	Node * m_parent = nullptr;
	int m_data;
public:
	Node(int data = 0) :m_data(data) {}
};

int max(int a, int b) { return (a > b) ? a : b; }
int abs(int x) { return (x > 0) ? x : -x; }


int height(Node * someNode)
{
	if (someNode == nullptr)
		return -1;

	return 1 + max(height(someNode->m_left), height(someNode->m_right));
}


Node * getHead(Node * someNode)
{
	if (someNode == nullptr)
		return nullptr;

	Node * current = someNode;
	while (current->m_parent != nullptr)
		current = current->m_parent;

	return current;
}


bool nodeIsBalanced(Node * someNode)
{
	if (someNode == nullptr)
		return true;

	int deltaHeight = abs(height(someNode->m_left) - height(someNode->m_right));
	return (deltaHeight <= 1);
}


struct BalanceAndHeightData
{
	int m_height;
	bool m_isBalanced;

	BalanceAndHeightData(int height = 0, bool isBalanced = true) : m_height(height), m_isBalanced(isBalanced) {}
};


BalanceAndHeightData getBalanceAndHeight(Node * someNode)
{
	if (someNode == nullptr)
		return BalanceAndHeightData(-1, true);

	BalanceAndHeightData leftData = getBalanceAndHeight(someNode->m_left);
	BalanceAndHeightData rightData = getBalanceAndHeight(someNode->m_right);

	int height = 1 + max(leftData.m_height, rightData.m_height);
	bool isBalanced = leftData.m_isBalanced and rightData.m_isBalanced 
		and (abs(leftData.m_height - rightData.m_height) <= 1);

	return BalanceAndHeightData(height, isBalanced);
}

bool isBalanced(Node * someNode)
{
	return (getBalanceAndHeight(someNode).m_isBalanced);
}




int main()
{
	/*
	Given a Node pointer nodePtr, call isBalanced(nodePtr) to see if the tree rooted at nodePtr is balanced.
	To check whether the entire tree is balanced, either ensure that nodePtr points to the root of the tree, 
	or call isBalanced(getHead(nodePtr)).

	Simple examples below.	
	*/






	Node * head = new Node(5);
	Node * left = new Node(3);
	Node * leftLeft = new Node(1);


	head->m_left = left;
	left->m_left = leftLeft;

	leftLeft->m_parent = left;
	left->m_parent = head;


	if (isBalanced(head))
		std::cout << "Balanced\n";
	else
		std::cout << "Not balanced\n";



	Node * newHead = new Node(10);
	Node * newLeft = new Node(15);
	Node * newRight = new Node(20);

	newHead->m_left = newLeft;
	newHead->m_right = newRight;
	newLeft->m_parent = newHead;
	newRight->m_parent = newHead;

	if (isBalanced(newHead))
		std::cout << "Balanced\n";
	else
		std::cout << "Not balanced\n";




    return 0;
}

