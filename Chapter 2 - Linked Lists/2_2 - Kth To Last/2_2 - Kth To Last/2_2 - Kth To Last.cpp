#include "stdafx.h"
#include <iostream>
#include <list>
#include <forward_list>

std::forward_list<int> inputExampleList1 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
int inputExampleK1 = 3;
int outputExample1 = 9;

std::forward_list<int> inputExampleList2 = { 12, 7, 8, 33, -42, 7, 200 };
int inputExampleK2 = 1;
int outputExample2 = 7;

///// There are several ways to interpret out-of-bounds K values.  Let's say that if K < 0, we simply want the last element of the list, 
///// and if K is larger than or equal to the length of the list, we want the zero'th element of the list.
///// If the list is empty, we want to return the default object of class T.

std::forward_list<int> inputExampleList3 = { 6, 8, 10, 3, 5, 7 };
int inputExampleK3 = -4;
int outputExample3 = 7;

std::forward_list<int> inputExampleList4 = { 12, 14, 16, 18, 20, 11, 13, 15, 17, 19, 43 };
int inputExampleK4 = 30;
int outputExample4 = 12;

std::forward_list<int> inputExampleList5 = {};
int inputExampleK5 = 2;
int outputExample5 = 0;


template<class T>
T KthToLastElt(std::forward_list<T> &ourList, int K)
{
	if (ourList.empty())
		return T();
	
	auto firstFinger = ourList.begin();
	firstFinger++;
	auto secondFinger = ourList.begin();
	auto last = ourList.end();
	
	for (int i = 0; i < K; i++)
	{
		if (firstFinger == last)		// We've reached the end of the list before K steps
		{
			return *secondFinger;
		}
		else
		{
			firstFinger++;
		}
	}

	// Our first finger has moved K times.  Now move both fingers in each step until the first one hits the end.
	while (firstFinger != last)
	{
		firstFinger++;
		secondFinger++;
	}

	if ( (secondFinger == ourList.end()) or (secondFinger == ourList.before_begin()))
		return T();
	return *secondFinger;
}


int main()
{
	if (KthToLastElt(inputExampleList1, inputExampleK1) == outputExample1)
		std::cout << "Passed the first test!\n";
	if (KthToLastElt(inputExampleList2, inputExampleK2) == outputExample2)
		std::cout << "Passed the second test!\n";
	if (KthToLastElt(inputExampleList3, inputExampleK3) == outputExample3)
		std::cout << "Passed the third test!\n";
	if (KthToLastElt(inputExampleList4, inputExampleK4) == outputExample4)
		std::cout << "Passed the fourth test!\n";
	if (KthToLastElt(inputExampleList5, inputExampleK5) == outputExample5)
		std::cout << "Passed the fifth test!\n";

    return 0;
}

