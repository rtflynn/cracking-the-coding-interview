#include "stdafx.h"
#include <iostream>
#include <set>
#include <list>

/*
BST Sequences:  A binary search tree was created by traversing through an array from left to right
and inserting each element.  Given a binary search tree with distinct elements, print all possible
arrays that could have lef to this tree.

Example:
		Input:   Tree with Root 2, Left 1, Right 3
		Output:  {2, 1, 3}, {2, 3, 1}
*/




/*
It's not clear from the question whether this BST was built in a straightforward manner, always placing 
new nodes at the leaves and never rebalancing, or if balancing operations are included.  But if they are, 
there's a bit of choice about how to carry them out, so let's assume it's just a straightforward BST.

Well then, the root has to be the first item that was inserted into the tree.  To use a larger example:
Let's say the root is 50.  If there are nodes with values 42 and 78, then it doesn't matter which one is
inserted first, since one will go to the right and one will go to the left.  However, if there are nodes
with values 42 and 37, it matters a great deal which order they were placed in the tree.  

Everything needs to be inserted before its children - that much is for sure.  
The more I look at it, the more I'm starting to think that this is the only restriction.  If so, should
be easy enough to prove.

It's true - instead of a formal proof let's just go through the algorithm (which is almost a proof in itself).

Building our arrays:  We start with the root, but this is just a special case of what we do at every stage
anyway.  At any given time, there will be some Nodes we've already printed.  Populate a list consisting of
the so-far-unprinted children of these nodes.  Choose one of them and repeat this process.

Eventually we'll have printed out an order for the input array, and if we do this in such a way that we
explore every possible choice at every possible stage of this computation, we will have printed out 
every possible array leading to our specific tree.
*/


class Node
{
public:
	Node * m_parent = nullptr;
	Node * m_left = nullptr;
	Node * m_right = nullptr;
	int m_data;

	Node(int data) : m_data(data) {}
	void saySomething() { std::cout << "I'm a node with m_data value " << m_data << ".\n"; }

	bool operator<(const Node& other)
	{
		return (m_data < other.m_data);
	}

};

Node * createExample()
{
	Node * root = new Node(2);
	Node * left = new Node(1);
	Node * right = new Node(3);
	
	root->m_left = left;
	root->m_right = right;
	left->m_parent = root;
	right->m_parent = root;

	return root;
}

Node * createExample2()
{
	Node * root = new Node(50);
	Node * left = new Node(24);
	Node * right = new Node(93);
	Node * leftleft = new Node(11);
	Node * leftright = new Node(32);
	Node * rightleft = new Node(67);
	Node * rightright = new Node(112);

	root->m_left = left;
	root->m_right = right;
	left->m_left = leftleft;
	left->m_right = leftright;
	right->m_left = rightleft;
	right->m_right = rightright;

	left->m_parent = root;
	right->m_parent = root;
	leftleft->m_parent = left;
	leftright->m_parent = left;
	rightleft->m_parent = right;
	rightright->m_parent = right;

	return root;
}


void printAllArrays(std::set<Node*> nextToVisit, std::list<Node*> visitedNodesInOrder)
{
	for (auto it = nextToVisit.begin(); it != nextToVisit.end(); it++)
	{
		Node * currentNode = *it;
		int currentData = currentNode->m_data;

		std::set<Node*> newList = nextToVisit;
		newList.erase(currentNode);

		std::list<Node*> newVisitedNodesList = visitedNodesInOrder;
		newVisitedNodesList.push_back(currentNode);

		if (currentNode->m_left != nullptr)
			newList.insert(currentNode->m_left);
		if (currentNode->m_right != nullptr)
			newList.insert(currentNode->m_right);

		printAllArrays(newList, newVisitedNodesList);
	}

	if (nextToVisit.empty())
	{
		for (auto it = visitedNodesInOrder.begin(); it != visitedNodesInOrder.end(); it++)
			std::cout << (*it)->m_data << " ";
		std::cout << "\n";
	}
}


void printAllArrays(Node * head)
{
	std::set<Node*> initialVisitList;
	initialVisitList.insert(head);

	std::list<Node*> visitOrder;
	printAllArrays(initialVisitList, visitOrder);
}

int main()
{
	Node * example = createExample();
	printAllArrays(example);

	Node * example2 = createExample2();
	printAllArrays(example2);
	

    return 0;

}

