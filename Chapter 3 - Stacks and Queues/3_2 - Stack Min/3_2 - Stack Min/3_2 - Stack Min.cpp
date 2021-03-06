#include "stdafx.h"
#include <iostream>

// Question prompt:
// How would you design a stack which, in addition to push and pop, has a function min
// which returns the minimum element?  Push, pop and min should all operate in O(1) time.

class Node
{
public:			
	Node * m_previous = nullptr;
	float m_minimumSoFar;
	float m_data;

	Node(float data) : m_data(data), m_minimumSoFar(data) {}
};


float min(float x, float y)     { return ((x < y) ? x : y); }


class MinStack
{
private:
	Node * m_topOfStack = nullptr;	

public:
	MinStack() {}
	~MinStack() {
		Node * current = m_topOfStack;
		Node * temp;
		while (current != nullptr)
		{
			temp = current->m_previous;
			delete current;
			current = temp;
		}
	}

	bool isEmpty() { return (m_topOfStack == nullptr); }

	void push(float newData)
	{
		Node * newNode = new Node(newData);
		if (this->isEmpty())
		{
			m_topOfStack = newNode;
			return;
		}

		newNode->m_minimumSoFar = min(newNode->m_minimumSoFar, m_topOfStack->m_minimumSoFar);
		newNode->m_previous = m_topOfStack;		

		m_topOfStack = newNode;
	}

	float pop()
	{
		if (m_topOfStack == nullptr)
			throw - 1;
		float ourValue = m_topOfStack->m_data;
		Node * prev = m_topOfStack->m_previous;
		delete m_topOfStack;
		m_topOfStack = prev;

		return ourValue;
	}

	float currentMin()
	{
		if (m_topOfStack == nullptr)
			return INFINITY;
		return m_topOfStack->m_minimumSoFar;
	}


};







int main()
{
	MinStack ourStack = MinStack();
	ourStack.push(5);
	std::cout << "The minimum is currently " << ourStack.currentMin() << ".\n";
	ourStack.push(3.14);
	std::cout << "The minimum is currently " << ourStack.currentMin() << ".\n";
	ourStack.push(2.67);
	std::cout << "The minimum is currently " << ourStack.currentMin() << ".\n";
	ourStack.push(123.456);
	std::cout << "The minimum is currently " << ourStack.currentMin() << ".\n";
	ourStack.push(-12.8);
	std::cout << "The minimum is currently " << ourStack.currentMin() << ".\n";



	while (!ourStack.isEmpty())
	{
	std::cout << "Popping the top element... which has value " << ourStack.pop() << ".";
	std::cout << " The minimum value among remaining elements is " << ourStack.currentMin() << ".\n";
	}
	std::cout << std::endl;


	for (int i = 0; i < 10; i++)
	{
		ourStack.push(-i);
		std::cout << "The minimum is currently " << ourStack.currentMin() << ".\n";		
	}

	while (!ourStack.isEmpty())
	{
		std::cout << "Popping the top element... which has value " << ourStack.pop() << ".";
		std::cout << " The minimum value among remaining elements is " << ourStack.currentMin() << ".\n";
	}


    return 0;
}

