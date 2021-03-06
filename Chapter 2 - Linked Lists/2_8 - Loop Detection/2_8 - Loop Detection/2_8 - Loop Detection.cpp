#include "stdafx.h"
#include <iostream>
#include <list>
#include <unordered_set> 
#include <set>

class Node
{
public:
	Node * next;
	int m_data;
	Node(int data = 0) : m_data(data), next(nullptr) {}
	Node(Node * prev) 
	{
		m_data = prev->m_data + 1;
		prev->next = this;
		next = nullptr;
	}
};

Node * beginningOfLoop(Node * head)
{
	std::unordered_set<Node *> seenNodePtrs;
	Node * temp = head;

	while (temp != nullptr)
	{
		if (seenNodePtrs.count(temp))
			return temp;
		seenNodePtrs.insert(temp);
		temp = temp->next;
	}



	return nullptr;
}




int main()
{
	
	Node * A = new Node(0);
	Node * B = new Node(A);
	Node * C = new Node(B);
	Node * D = new Node(C);
	Node * E = new Node(D);
	E->next = C;

	
	Node * ans = beginningOfLoop(A);
	if (ans != nullptr)
		std::cout << "The beginning of the loop is the Node with value " << ans->m_data << std::endl;
		


	/*
	Node * temp = A;
	while (temp != nullptr) {
		std::cout << temp->m_data << " ";
		temp = temp->next;
	}
	std::cout << std::endl;
	*/
	return 0;
}

