#include "stdafx.h"
#include <iostream>
#include <list>
#include <unordered_set>

// Some examples to test our solution

std::list<int> inputExample1 = { 5, 5, 12, 7, 6, 3, 7, 4, 4, 2 };
std::list<int> outputExample1 = { 5, 12, 7, 6, 3, 4, 2 };

std::list<int> inputExample2 = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 4, 4, 4, 3, 4, 3, 3, 3, 4, 3 };
std::list<int> outputExample2 = { 3, 4 };

std::list<int> inputExample3 = { 2, 4, 6, 8, 10, 1, 3, 5, 7, 9 };
std::list<int> outputExample3 = { 2, 4, 6, 8, 10, 1, 3, 5, 7, 9 };


template<class T>
std::list<T> removeDuplicates(std::list<T> inputList)
{
	std::unordered_set<T> alreadySeen;
	std::list<T> outputList;
	for (const T someItem : inputList)
	{
		if (!alreadySeen.count(someItem))
		{
			alreadySeen.insert(someItem);
			//outputList.insert(someItem);
			outputList.push_back(someItem);
		}
	}

	return outputList;
}



int main()
{
	if (removeDuplicates(inputExample1) == outputExample1)
		std::cout << "First case successful!\n";
	if (removeDuplicates(inputExample2) == outputExample2)
		std::cout << "Second case successful!\n";
	if (removeDuplicates(inputExample3) == outputExample3)
		std::cout << "Third case successful!\n";

	if (removeDuplicates(inputExample1) == outputExample3)
		std::cout << "That's not supposed to happen......\n";

    return 0;
}

