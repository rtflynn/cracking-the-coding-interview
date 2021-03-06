#include "stdafx.h"
#include <iostream>

// Implement a queue using two stacks.
// Recall briefly:  Stack obeys LIFO and requires push(), pop(), isEmpty() methods.
// Queue obeys FIFO and requires push(), pop(), isEmpty(), except we pop() from the front of the queue.


class Node
{
public:
	Node * m_prev = nullptr;
	float m_data = 0;

	Node(int data) : m_data(data) {}
};


class Stack
{
private:
	Node * m_topOfStack = nullptr;

public:
	Stack() {}
	~Stack() 
	{ 
		while (m_topOfStack != nullptr)
		{
			Node * temp = m_topOfStack;
			m_topOfStack = temp->m_prev;
			delete temp;
		}
	}

	bool isEmpty() { return (m_topOfStack == nullptr); }

	void push(float newData)
	{
		Node * newNode = new Node(newData);
		newNode->m_prev = m_topOfStack;
		m_topOfStack = newNode;
	}

	float pop()
	{
		if (this->isEmpty())
			throw - 1;
		Node * temp = m_topOfStack;
		float answer = temp->m_data;
		m_topOfStack = temp->m_prev;
		delete temp;
		return answer;
	}
};


class Queue
{
	Stack * inOrderStack = nullptr;
	Stack * reverseOrderStack = nullptr;

public:
	Queue() { inOrderStack = new Stack(); reverseOrderStack = new Stack(); }

	void push(float newData)
	{
		inOrderStack->push(newData);
	}

	float pop()
	{
		while (!inOrderStack->isEmpty())		
			reverseOrderStack->push(inOrderStack->pop());			
		
		float answer = reverseOrderStack->pop();

		while (!reverseOrderStack->isEmpty())
			inOrderStack->push(reverseOrderStack->pop());

		return answer;
	}
};



int main()
{
	Queue myQueue = Queue();

	for (int i = 0; i < 20; i++)
		myQueue.push(i);

	for (int i = 0; i < 20; i++)
		std::cout << myQueue.pop() << " ";

    return 0;
}

