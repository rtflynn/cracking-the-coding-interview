#include "stdafx.h"
#include <iostream>
#include <algorithm>		// For std::fill


int parent(int n)
{
	return (n - 1) / 2;
}

int leftChild(int n)
{
	return 2 * n + 1;
}

int rightChild(int n)
{
	return 2 * n + 2;
}

void swap(float&a, float&b)
{
	float temp = a;
	a = b;
	b = temp;
}


// Numbered starting at 0 to keep everything simple.  Can also number starting at 1 to make the parent and left/right child
// operations efficient, because with that numbering scheme these operations are bitwise shifts / XOR operators.


class Heap
{
public:
	int m_totalSize;
	int m_currentSize;
	float * m_ourArray;			// Implement an auto-resizing array if we want an auto-resizing heap.  
								// What I mean is, don't do it in this class.  SRP and all that.

public:
	Heap(int totalSize = 255) : m_totalSize(totalSize), m_currentSize(0)
	{
		m_ourArray = new float[m_totalSize];
		std::fill(m_ourArray, m_ourArray + m_totalSize, INFINITY);
	}

	float& operator[](int n)
	{
		if ((n < 1) or (n > m_totalSize))
			throw - 1;
		return m_ourArray[n];
	}

	void insert(float fData)
	{
		if (m_currentSize >= m_totalSize)
			throw - 1;
		m_ourArray[m_currentSize] = fData;
		m_currentSize += 1;
	}

	void heapifyUp(int index)
	{
		//std::cout << "In heapifyUp with index " << index << ".\n";
		if (index == 0)
			return;
		if (m_ourArray[index] > m_ourArray[parent(index)])
			return;
		swap(m_ourArray[index], m_ourArray[parent(index)]);
		heapifyUp(parent(index));
	}

	void heapifyDown(int index)
	{
		if (2 * index + 2 >= m_totalSize)
			return;
		float left = m_ourArray[leftChild(index)];
		float right = m_ourArray[rightChild(index)];
		int smallest = (left < right) ? leftChild(index) : rightChild(index);
		if (m_ourArray[index] > m_ourArray[smallest])
		{
			swap(m_ourArray[index], m_ourArray[smallest]);
			heapifyDown(smallest);
		}
		else
			return;
	}





public:
	bool isEmpty() { return m_currentSize == 0; }
	void push(float fData)
	{
		//std::cout << "Pushing " << fData << " onto the heap.\n";
		insert(fData);
		heapifyUp(m_currentSize - 1);
	}

	float peekMin()
	{
		return m_ourArray[0];
	}

	float pop()
	{
		//std::cout << "Popping.  The current array size is " << m_currentSize << " and the current root node is " << m_ourArray[0] << ".\n";

		float answer = m_ourArray[0];
		swap(m_ourArray[0], m_ourArray[m_currentSize]);
		m_ourArray[m_currentSize] = INFINITY;
		m_currentSize -= 1;
		heapifyDown(0);
		return answer;
	}


	void speak()
	{
		for (int i = 0; i < m_currentSize; i++)
			std::cout << m_ourArray[i] << " ";
		std::cout << std::endl;

	}

};










int main()
{
	Heap ourHeap = Heap();

	ourHeap.push(5);
	ourHeap.push(10);
	ourHeap.push(-1);
	ourHeap.push(33);
	ourHeap.push(6);
	ourHeap.push(720);
	ourHeap.push(-42);
	ourHeap.push(1.23);

	for (int i = 0; i < ourHeap.m_currentSize + 2; i++)
		std::cout << ourHeap.m_ourArray[i] << " ";
	std::cout << std::endl;


	while (!ourHeap.isEmpty())
		std::cout << ourHeap.pop() << " ";
	std::cout << std::endl;


	for (int i = 0; i < 12; i++)
		ourHeap.push(i*i);
	for (int i = 0; i < 12; i++)
		ourHeap.push(-i * (i + 1));

	while (!ourHeap.isEmpty())
		std::cout << ourHeap.pop() << " ";
	std::cout << std::endl;


	



    return 0;
}

