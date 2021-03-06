#include "stdafx.h"
#include <iostream>
#include <string>

// The problem statement is: To implement three stacks within one array.
// Not really sure why anyone would want to do this.  Anyhow there's the obvious solution
// of dividing the array into three equal or roughly equal parts.  The problem with this
// is that one of the stacks might fill up while the other two barely have anything in them.
// There are all sorts of ways to deal with this, and they all have drawbacks.  So I'm going to assume
// that there isn't really a correct answer here, and that the point is to be able to discuss these tradeoffs
// and to design a solution which does well at one aspect, without worrying much about the others.


class StackException
{
public:
	std::string m_exceptionDescription;
public:
	StackException(std::string s) : m_exceptionDescription(s) {}
};


class SimpleStack
{
private:

	float * m_stackBegin;
	float * m_currentHeadPtr;
	int m_capacity;
	int m_usedCapacity;

public:
	SimpleStack() { m_stackBegin = nullptr; m_currentHeadPtr = nullptr; m_capacity = 0; m_usedCapacity = 0; }
	SimpleStack(float * begin, int capacity) : m_stackBegin(begin), m_currentHeadPtr(nullptr), m_capacity(capacity), m_usedCapacity(0) {}

	bool isEmpty() { return (m_usedCapacity == 0); }		// Can also use m_usedCapacity.

	float peek() 
	{ 
		if (!isEmpty())
			return *m_currentHeadPtr;
		else
			throw StackException("Can't peek --- There's nothing there!");	
	}

	void push(float newItem)
	{
		if (m_usedCapacity >= m_capacity)
			throw StackException("Can't push --- the stack's full!");

		if (m_currentHeadPtr == nullptr)
		{
			m_usedCapacity = 1;
			m_currentHeadPtr = m_stackBegin;
			*m_currentHeadPtr = newItem;
		}
		else
		{
			m_usedCapacity += 1;
			m_currentHeadPtr += 1;
			*m_currentHeadPtr = newItem;
		}
	}

	float pop()
	{		
		if (isEmpty())
			throw StackException("Can't pop --- there's nothing there!");

		float answer = *m_currentHeadPtr;
		if (m_usedCapacity == 1)
		{
			m_usedCapacity -= 1;
			m_currentHeadPtr = nullptr;
			return answer;
		}
		else
		{
			m_currentHeadPtr -= 1;
			m_usedCapacity -= 1;
			return answer;
		}
	}
};


class TripleStackRigid
{
public:
	int m_stackSize;
	float * underlyingArray;
	SimpleStack firstStack, secondStack, thirdStack;

	TripleStackRigid(int stackSize)
	{
		m_stackSize = stackSize;
		underlyingArray = new float[3 * m_stackSize];
		firstStack = SimpleStack(underlyingArray, m_stackSize);
		secondStack = SimpleStack(underlyingArray + m_stackSize, m_stackSize);
		thirdStack = SimpleStack(underlyingArray + 2 * m_stackSize, m_stackSize);
	}

};



int main()
{
	TripleStackRigid myTripleStack = TripleStackRigid(10);
	myTripleStack.firstStack.push(3.21f);
	myTripleStack.firstStack.push(4.32f);
	myTripleStack.firstStack.push(5.43f);

	myTripleStack.secondStack.push(1.35f);
	myTripleStack.secondStack.push(2.46f);

	myTripleStack.thirdStack.push(987.654f);


	try 
	{
		std::cout << myTripleStack.firstStack.pop() << " " << myTripleStack.secondStack.pop() << " " <<
			myTripleStack.thirdStack.pop() << std::endl;

		std::cout << myTripleStack.thirdStack.pop() << std::endl;

	}

	catch (StackException &e)
	{
		std::cout << e.m_exceptionDescription << std::endl;
	}




    return 0;
}

