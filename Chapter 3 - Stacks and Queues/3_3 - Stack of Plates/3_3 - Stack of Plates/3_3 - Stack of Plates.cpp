#include "stdafx.h"
#include <iostream>


// Implement a stack of stacks.  When one stack fills up, we start pushing items onto the next one.
// Follow-up:  Allow the user to pop() from a given stack in the collection.

class Node
{
public:
	Node * m_prev = nullptr;
	float m_data = 0;

	Node(float data) : m_data(data) {}
};


class Stack
{
private:
	int m_capacity = 10;
	int m_usedCapacity = 0;
	Node * m_topOfStack = nullptr;

public:
	Stack(int capacity) : m_capacity(capacity) {}

	bool isEmpty() { return (m_usedCapacity == 0); }
	bool isFull() { return (m_usedCapacity == m_capacity); }

	float pop() 
	{
		if (this->isEmpty())
			throw - 1;

		float answer = m_topOfStack->m_data;
		Node * temp = m_topOfStack;
		m_topOfStack = temp->m_prev;
		m_usedCapacity -= 1;
		delete temp;
		return answer;
	}

	void push(float newData)
	{
		if (this->isFull())		
			return;
		
		Node * newNode = new Node(newData);

		newNode->m_prev = m_topOfStack;
		m_topOfStack = newNode;
		m_usedCapacity += 1;
	}
};



class StackNode
{
public:					//Would be private but let's avoid having a million getters and setters since this is just an exercise
	Stack * m_currentStack = nullptr;
	StackNode * m_previousStackNode = nullptr;

public:
	StackNode(int capacity = 10) 
	{
		Stack * newStack = new Stack(capacity);
		m_currentStack = newStack;
	}

	bool isEmpty() { return m_currentStack->isEmpty(); }
	bool isFull() { return m_currentStack->isFull(); }
	void push(float newData) { m_currentStack->push(newData); }
	float pop() { return m_currentStack->pop(); }


};


class StackOfStacks
{
private:
	StackNode * m_headStack = nullptr;
	int m_capacity = 0;

public:
	StackOfStacks(int capacity) : m_capacity(capacity)
	{
		m_headStack = new StackNode(m_capacity);
	}

	void push(float newData)
	{
		if (!m_headStack->isFull())
		{
			m_headStack->push(newData);
			return;
		}

		else
		{				
			std::cout << "Old stack's full, so creating a new one.\n";
			StackNode * newNode = new StackNode(m_capacity);
			newNode->m_previousStackNode = m_headStack;
			m_headStack = newNode;
			m_headStack->push(newData);
		}
	}

	float pop()
	{
		if (!m_headStack->isEmpty())
			return m_headStack->pop();

		else
		{
			std::cout << "A stack just emptied, so deleting it.\n";
			StackNode * temp = m_headStack;
			m_headStack = temp->m_previousStackNode;
			delete temp;
			return m_headStack->pop();
		}

	}


};




int main()
{
	StackOfStacks myObj = StackOfStacks(12);

	for (int i = 0; i < 100; i++)
		myObj.push(i);

	for (int i = 0; i < 100; i++)
		std::cout << myObj.pop() << "  ";



    return 0;
}

