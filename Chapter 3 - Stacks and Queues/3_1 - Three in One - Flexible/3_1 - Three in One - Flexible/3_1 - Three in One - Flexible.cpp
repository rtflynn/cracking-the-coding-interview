#include "stdafx.h"
#include <iostream>


class CircularArray
{
private:
	float * m_someArray;
	int m_sizeOfArray;
public:
	CircularArray(int sizeOfArray = 0)
	{
		m_sizeOfArray = sizeOfArray;
		m_someArray = new float[m_sizeOfArray] {0.0f};
	}

	~CircularArray()
	{
		delete[] m_someArray;
	}

	CircularArray& operator=(const CircularArray& otherArray)
	{
		m_sizeOfArray = otherArray.m_sizeOfArray;
		m_someArray = new float[m_sizeOfArray] {0.0f};
		for (int i = 0; i < m_sizeOfArray; i++)
			m_someArray[i] = otherArray.m_someArray[i];
		return *this;
	}

	CircularArray(const CircularArray &otherArray)
	{
		m_sizeOfArray = otherArray.m_sizeOfArray;
		m_someArray = new float[m_sizeOfArray] {0.0f};
		for (int i = 0; i < m_sizeOfArray; i++)
			m_someArray[i] = otherArray.m_someArray[i];
	}

	float &operator[] (int index)
	{
		return m_someArray[(index % m_sizeOfArray)];
	}

	int getSize() { return m_sizeOfArray; }

	void saySomething() 
	{
		for (int i = 0; i < m_sizeOfArray; i++)
			std::cout << m_someArray[i] << " ";
		std::cout << std::endl;
	}
};

class SubArray
{
private:
	CircularArray &m_circArray;
	int m_beginIndex;
	int m_endIndex;

public:
	SubArray(CircularArray &circArray, int begin, int end) : m_circArray(circArray), m_beginIndex(begin), m_endIndex(end) {}

	float &operator[] (int index)
	{
		return m_circArray[m_beginIndex + index];
	}

	int getBegin() { return m_beginIndex; }
	int getEnd() { return m_endIndex; }
	void setBegin(int begin) { m_beginIndex = begin; }
	void setEnd(int end) { m_endIndex = end; }
};


class Stack : public SubArray
{
private:
	int m_capacity;
	int m_usedCapacity;

public:
	Stack(CircularArray & circArray, int begin, int end) : SubArray(circArray, begin, end)
	{
		std::cout << "Constructing a Stack object...\n";

		m_capacity = (end - begin + 1 % circArray.getSize());
		m_usedCapacity = 0;
	}

	void push(float newItem)
	{
		if (m_usedCapacity >= m_capacity)
			throw - 5;
		
		(*this)[m_usedCapacity] = newItem;
		m_usedCapacity += 1;

		std::cout << "Pushing " << newItem << " onto the stack.\n";
	}

	float peek()
	{
		if (m_usedCapacity == 0)
			throw - 1;
		return (*this)[m_usedCapacity-1];
	}

	float pop()
	{
		std::cout << "Current used capacity is " << m_usedCapacity << std::endl;
		if (m_usedCapacity == 0)
			throw - 2;
		m_usedCapacity -= 1;
		float answer = (*this)[m_usedCapacity];
		return answer;
	}

	bool isEmpty()
	{
		return (m_usedCapacity == 0);
	}

	bool isFull()
	{
		return (m_usedCapacity == m_capacity);
	}

	int freeSpace() { return m_capacity - m_usedCapacity; }
	int getCapacity() { return m_capacity; }
	int getUsedCapacity() { return m_usedCapacity; }
	void setCapacity(int cap) {	m_capacity = cap; }
};


class TripleStackContainer
{
public:
	CircularArray & m_circularArray;
	Stack * m_ourStacks;

public:
	TripleStackContainer(CircularArray &someArray) : m_circularArray(someArray) 
	{
		int totalSize = m_circularArray.getSize();
		int secondStart = totalSize / 3;
		int thirdStart = 2 * totalSize / 3;
		
		Stack zerothStack = Stack(m_circularArray, 0, secondStart - 1);
		Stack firstStack = Stack(m_circularArray, secondStart, thirdStart - 1);
		Stack secondStack = Stack(m_circularArray, thirdStart, totalSize - 1);

		m_ourStacks = new Stack[3]{ zerothStack, firstStack, secondStack };
	}

	int totalFreeSpace()
	{
		int ans = 0;

		for (int i = 0; i < 3; i++)
			ans += m_ourStacks[i].freeSpace();
		return ans;
	}	

	void rotate(int stackIndex, int distance)
	{
		Stack &currentStack = m_ourStacks[stackIndex];
		if (currentStack.freeSpace() < distance)
		{
			std::cout << "Trying to rotate one stack past another --- therefore doing nothing and returning.\n";
			return;
		}

		for (int i = currentStack.getUsedCapacity() - 1; i >= 0; i--)
		{
			currentStack[i + distance] = currentStack[i];
			currentStack[i] = 0;
		}

		currentStack.setBegin((currentStack.getBegin() + distance) % m_circularArray.getSize());
		currentStack.setCapacity(currentStack.getCapacity() - distance);

		Stack &previousStack = m_ourStacks[(stackIndex + 2) % 3];

		previousStack.setEnd((previousStack.getEnd() + distance) % m_circularArray.getSize());
		previousStack.setCapacity(previousStack.getCapacity() + distance);

	}	

	void saySomething()
	{
		m_circularArray.saySomething(); 
	}
};



class RotationController : public TripleStackContainer
{
public:
	RotationController(CircularArray &someArray) : TripleStackContainer(someArray) {}
	
	void rotateOtherStacks(int stationaryStackIndex)
	{
		int nextStackIndex = (stationaryStackIndex + 1) % 3;
		int nextNextStackIndex = (stationaryStackIndex + 2) % 3;

		Stack & nextStack = m_ourStacks[nextStackIndex];
		Stack & nextNextStack = m_ourStacks[nextNextStackIndex];

		int rotateAmount = totalFreeSpace() / 2;

		if (nextNextStack.freeSpace() >= rotateAmount)
			rotate(nextNextStackIndex, (nextNextStack.freeSpace() - rotateAmount));

		rotate(nextStackIndex, rotateAmount);
	}
};



class UserInterface
{
private:
	CircularArray &m_ourArray;
	RotationController m_ourController;

public:
	UserInterface(CircularArray &someArray) : m_ourArray(someArray), m_ourController(m_ourArray) {}
	
private:
	Stack * ourStacks = m_ourController.m_ourStacks;

public:

	float peek(int stackNo)
	{
		return ourStacks[stackNo].peek();
	}

	float pop(int stackNo)
	{
		return ourStacks[stackNo].pop();
	}

	bool isEmpty(int stackNo)
	{
		return ourStacks[stackNo].isEmpty();
	}

	void push(int stackNo, float newData)
	{
		if (ourStacks[stackNo].isFull())
			m_ourController.rotateOtherStacks(stackNo);
		
		ourStacks[stackNo].push(newData);	
	}

	void saySomething()
	{
		m_ourController.saySomething();
	}
};







int main()
{
	CircularArray myArray = CircularArray(15);
	UserInterface ourTripleStack = UserInterface(myArray);

	ourTripleStack.saySomething();
	ourTripleStack.push(0, 1);
	ourTripleStack.push(1, 1);
	ourTripleStack.push(2, 1);
	ourTripleStack.saySomething();
	
	// NOT FUNCTIONAL.  Come back and fix this if there's free time.
	// Ideally, just start over from scratch and avoid the PITA mistakes I made this time through.

    return 0;
}