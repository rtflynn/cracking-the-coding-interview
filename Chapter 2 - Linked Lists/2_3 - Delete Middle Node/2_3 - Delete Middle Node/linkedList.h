#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>


class Node
{
public:
	Node * next = nullptr;
	int m_data;
public:
	Node(int data) : m_data(data) {};

	void appendToTail(int data)
	{
		Node * last = new Node(data);
		Node * current = this;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		current->next = last;
	}


	void saySomething()
	{
		Node * current = this;
		while (current != nullptr)
		{
			std::cout << current->m_data << "  ";
			current = current->next;
		}
		std::cout << std::endl;
	}


};









#endif