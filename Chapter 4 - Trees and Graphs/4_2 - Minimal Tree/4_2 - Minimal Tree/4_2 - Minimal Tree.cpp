#include "stdafx.h"
#include <iostream>


///// Minimal Tree:  Given a sorted (increasing order) array with unique integer elements, write an algorithm
///// to create a binary search tree with minimal height.



struct Node
{
	Node * m_parent = nullptr;
	Node * m_left = nullptr;
	Node * m_right = nullptr;
	int m_data;

	Node(int data = 0) : m_data(data) { std::cout << "Constructing node with m_data " << m_data << ".\n"; }

	Node * getHead()
	{
		Node * current = this;
		while (current->m_parent != nullptr)
			current = current->m_parent;
		return current;
	}
};


void inOrderTraversal(Node * someNode)
{
	if (someNode == nullptr)
		return;
	inOrderTraversal(someNode->m_left);
	std::cout << someNode->m_data << "  ";
	inOrderTraversal(someNode->m_right);
}


Node * createTreeFromArray(int * someArray, int start, int end)
{
	if (end < start)
		return nullptr;
	if (end == start)
		return new Node(someArray[start]);
	int length = end + 1 - start;
	int middleIndex = start + length / 2 ;
	int data = someArray[middleIndex];


	Node * current = new Node(data);
	Node * left = createTreeFromArray(someArray, start, middleIndex - 1);
	Node * right = createTreeFromArray(someArray, middleIndex + 1, end);

	current->m_left = left;
	current->m_right = right;
	if (left != nullptr)
		left->m_parent = current;
	if (right != nullptr)
		right->m_parent = current;

	return current;
}






int main()
{
	const int arraySize = 16;
	int myArray[arraySize];
	for (int i = 0; i < arraySize; i++)
		myArray[i] = i;
	
	Node * head = createTreeFromArray(myArray, 0, arraySize - 1);
	inOrderTraversal(head);



    return 0;
}

