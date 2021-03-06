#include "stdafx.h"
#include <iostream>
#include <vector>


class Node
{
public:
	Node * leftChild = nullptr;
	Node * rightChild = nullptr;
	Node * parent = nullptr;

	int m_value;
public:
	Node(int value = 0) : m_value(value) {}
	~Node() {}

	void createLeftChild(int value = 0)
	{
		if (leftChild != nullptr)
			return;
		Node * newChild = new Node(value);
		newChild->parent = this;
		leftChild = newChild;
	}

	void createRightChild(int value = 0)
	{
		if (rightChild != nullptr)
			return;
		Node * newChild = new Node(value);
		newChild->parent = this;
		rightChild = newChild;
	}
};


//// returns the vector slice [begin, end] - i.e. inclusive on both ends.
std::vector<int> slice(std::vector<int> originalVector, int begin, int end)
{
	if (begin > end)
	{
		std::vector<int> emptyVec(0);
		return emptyVec;
	}

	auto beginIter = originalVector.begin() + begin;
	auto endIter = originalVector.begin() + end + 1;

	std::vector<int> sliceVec(beginIter, endIter);
	return sliceVec;
}


Node * createTreeFromVector(std::vector<int> myVector)
{
	int length = myVector.size();
	if (length == 0)
		return nullptr;

	int currentVertexPosition = length / 2;
	int currentVertexLabel = myVector[currentVertexPosition];

	std::cout << currentVertexLabel << " ";

	std::vector<int> leftVector = slice(myVector, 0, currentVertexPosition - 1);
	std::vector<int> rightVector = slice(myVector, currentVertexPosition + 1, length - 1);

	Node * ourNewNode = new Node(currentVertexLabel);
	ourNewNode->leftChild = createTreeFromVector(leftVector);
	ourNewNode->rightChild = createTreeFromVector(rightVector);

	if (ourNewNode->leftChild != nullptr)
		ourNewNode->leftChild->parent = ourNewNode;
	if (ourNewNode->rightChild != nullptr)
		ourNewNode->rightChild->parent = ourNewNode;

	return ourNewNode;
}

Node * getHead(Node * someNode)
{
	if (someNode == nullptr)
		return nullptr;
	Node * current = someNode;
	while (current->parent != nullptr)
		current = current->parent;
	return current;
}


void inOrderTraversal(Node * someNode)
{
	if (someNode == nullptr)
		return;

	inOrderTraversal(someNode->leftChild);
	std::cout << " " << someNode->m_value << " ";
	inOrderTraversal(someNode->rightChild);
}

void preOrderTraversal(Node * someNode)
{
	if (someNode == nullptr)
		return;

	std::cout << " " << someNode->m_value << " ";
	preOrderTraversal(someNode->leftChild);
	preOrderTraversal(someNode->rightChild);
}

void postOrderTraversal(Node * someNode)
{
	if (someNode == nullptr)
		return;

	postOrderTraversal(someNode->leftChild);
	postOrderTraversal(someNode->rightChild);
	std::cout << " " << someNode->m_value << " ";
}


int main()
{
	std::vector<int> myVec(16);
	for (int i = 0; i < myVec.size(); i++)
		myVec[i] = i * i;	
	
	for (int i = 0; i < myVec.size(); i++)
		std::cout << myVec[i] << " ";
	std::cout << std::endl;

	Node * ourTree = createTreeFromVector(myVec);
	std::cout << std::endl;
	
	Node * head = getHead(ourTree);

	inOrderTraversal(head);
	std::cout << std::endl;

	preOrderTraversal(head);
	std::cout << std::endl;

	postOrderTraversal(head);
	std::cout << std::endl;

    return 0;
}

