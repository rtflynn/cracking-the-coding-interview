#include "stdafx.h"
#include <iostream>

// Write a program to sort a stack such that the smallest items are on the top.  We can use an additional 
// temporary stack, but we may not copy the elements to any other data structure (such as an array).
// The stack should support push, peek, pop, and isEmpty.


class Node
{
public:
	Node * m_prev = nullptr;
	float m_data = 0;

	Node(float data = 0) : m_data(data) {}
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

	float peek()
	{
		if (this->isEmpty())
			return -1;
		return m_topOfStack->m_data;
	}
};


void sort(Stack * ourStack)
{
	Stack * helperStack = new Stack();
	
	float currentMin = INFINITY;
	int currentMinMultiplicity = 0;

	while (!ourStack->isEmpty())		// See end of function for explanatory comments on the structure of this code
	{
		while (!ourStack->isEmpty())		// Transfer everything to the helper stack
		{
			float currentValue = ourStack->peek();

			if (currentValue < currentMin)
			{
				currentMin = currentValue;
				currentMinMultiplicity = 1;
			}

			else if (currentValue == currentMin)
			{
				currentMinMultiplicity += 1;
			}

			helperStack->push(ourStack->pop());
		}
		
		while (!helperStack->isEmpty())		// Transfer everything except the minimum elements back to the original stack
		{
			if (helperStack->peek() > currentMin)
				ourStack->push(helperStack->pop());
			else if (helperStack->peek() == currentMin)
				helperStack->pop();
			else break;
		}

		for (int i = 0; i < currentMinMultiplicity; i++)
			helperStack->push(currentMin);

		currentMin = INFINITY;
		currentMinMultiplicity = 0;
	}


	while (!helperStack->isEmpty())
	{
		ourStack->push(helperStack->pop());
	}




///// The idea isn't difficult, though.
///// We use a second 'helper Stack' as follows:
///// pop() all elements from the original stack into the helper stack, keeping track of the current minimum
///// value and its multiplicity.  Next pop() everything except the minimum values back to the original stack.
///// Finally push() 'multiplicity'-many copies of our minimum value onto our helper stack.
/////
///// Repeat this process, with the caveat that we will never pop() past the most recent minimum values in 
///// the helper stack.  Once the original stack has been exhausted (i.e. after popping all the elements
///// back to the first stack, it's still empty), we know that our helper stack has our elements sorted backwards.
///// 
///// So, just pop them all back to the original stack and we're done.



}















int main()
{
	Stack  myStack = Stack();

	for (int i = 0; i < 20; i++)
		myStack.push(i);

	for (int i = 0; i < 20; i++)
		myStack.push(i);

	sort(&myStack);

	for (int i = 0; i < 40; i++)
		std::cout << myStack.pop() << " ";





    return 0;
}

