#include "stdafx.h"
#include <iostream>


// Now for a flexible version.  Our array will contain 3 stacks of possibly different total capacities. 
// We may have to update the starting/ending positions of these stacks in order to fit them in there better...
// The problem that arises with this is the fact that moving a stack within our array will be expensive, so
// the insert operation no longer takes constant time.  In fact, the way this is implemented, insert can take
// linear time on average for badly chosen examples.  This could be improved to better amortized time by resizing
// our stacks as they approach their size limits instead of exactly when they hit them - similar to how it's done for 
// resizable hash tables.  But we're already past the point of using a ridiculous number of data structures built out of
// other data structures built out of other data structures... so let's not.  (Also, each time we build one structure out
// of others, we lose some efficiency to overhead and to having a large number of function calls going down the levels
// to carry out a simple operation at the top level.


//// Need to re-do the stack class.  It shouldn't know about the memory locations.  Instead it should interface with the circular array
//// class to do everything it needs to do.  Let's think about what's needed:  
//// We can assign directly to the circular array, and peek/pop, using just integer indexing.
//// We can prevent wrapping around the wrong way (i.e. 'popping backwards past the start') by keeping track of m_capacity 
//// and m_currentNumItems.  
//// So the main thing to do here is to get rid of the dependency on our pointer m_beginPtr.
//// One more thing --- this class shouldn't know that it's dealing with a circular array.  It should just think it's being built on
//// a normal ass normal array of fixed length, and building itself up starting at the 0 index, up to the final index.


//// We don't want this class to know that it can be resized.  So don't involve the 'push' operation with all that kinda stuff.
//// Rather, whenever m_currentItem approaches m_capacity, enlarge the capacity if possible from our TripleStack class.



class CircularArray
{
private:
	float * m_someArray;
	int m_sizeOfArray;
public:
	CircularArray(int sizeOfArray = 5)
	{
		m_sizeOfArray = sizeOfArray;
		m_someArray = new float[m_sizeOfArray] {0.0f};
	}

	~CircularArray()
	{
		delete[] m_someArray;
	}

	/*
	CircularArray& operator=(const CircularArray& myArray)
	{
		delete[] this->m_someArray;
		this->m_sizeOfArray = myArray.m_sizeOfArray;
		this->m_someArray = new float[m_sizeOfArray] {0.0f};
	}

	CircularArray(const CircularArray& myArray)
	{
		m_sizeOfArray = myArray.m_sizeOfArray;
		m_someArray = new float[m_sizeOfArray] {0.0f};
	}
	*/

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
			return;
		
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
private:

/*  
This class will take care of owning our 3 stacks...  This includes initializing them.  We do need to construct a circular array from outside
and feed it into the constructor.  

It also takes care of keeping track of the total free space left in the container.  I think the idea I want to go with for dynamic resizing
is to resize when the next push operation would cause a collision with the next stack, and in this case I want to rotate the other stacks 
clockwise so that the remaining space is divided up evenly between all 3 stacks.  

Example:  We've got a huge circular array, size 1,000,000.  The first stack has size 700,000. The second has size 200,000.
The third has size 10,000.  (The remaining space is thus 90,000).  The next push operation is going to cause a collision.
So, rotate all the stacks in such a way that there is 30,000 free space between any two.

This class will take care of the rotation function (and as such it will update all affected stacks' begin/end/capacity parameters.

*/

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

		//debug
	//	for (int i = 0; i < 3; i++)
	//		std::cout << "The " << i << " Stack has " << m_ourStacks[i].freeSpace() << " free space.\n";
		//end debug

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

		/*
		std::cout << "debug before\n";
		std::cout << previousStack.getEnd() << std::endl;
		std::cout << (previousStack.getEnd() + distance) % m_circularArray.getSize() << std::endl;
		*/

		previousStack.setEnd((previousStack.getEnd() + distance) % m_circularArray.getSize());
		previousStack.setCapacity(previousStack.getCapacity() + distance);

		/*
		std::cout << "debug after\n";
		std::cout << previousStack.getEnd() << std::endl;
		std::cout << (previousStack.getEnd() + distance) % m_circularArray.getSize() << std::endl;
		*/

		// Danger:  This doesn't do bounds checking, so if we rotate a stack into another and end up with more or less
		// free space than expected, this functionality will all be wrong.
	}	

	void saySomething()
	{
		m_circularArray.saySomething(); 

		/*
		std::cout << "Stack 0 has begin/end indices " << m_ourStacks[0].getBegin() << ", " << m_ourStacks[0].getEnd()
			<< ", and usedCapacity/capacity  " << m_ourStacks[0].getUsedCapacity() << "/" << m_ourStacks[0].getCapacity()
			<< ".\n";
		std::cout << "Stack 1 has begin/end indices " << m_ourStacks[1].getBegin() << ", " << m_ourStacks[1].getEnd()
			<< ", and usedCapacity/capacity  " << m_ourStacks[1].getUsedCapacity() << "/" << m_ourStacks[1].getCapacity()
			<< ".\n";
		std::cout << "Stack 2 has begin/end indices " << m_ourStacks[2].getBegin() << ", " << m_ourStacks[2].getEnd()
			<< ", and usedCapacity/capacity  " << m_ourStacks[2].getUsedCapacity() << "/" << m_ourStacks[2].getCapacity()
			<< ".\n";
			*/
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




int main()
{
	CircularArray myArray = CircularArray(15);
	//TripleStackContainer temp = TripleStackContainer(myArray);
	RotationController temp = RotationController(myArray);

    return 0;
}