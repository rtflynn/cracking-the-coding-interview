#include "stdafx.h"
#include <iostream>
#include <list>

///////// This works equally well with a forward_list since we only need the push_front method.

void partition(std::list<int> &myList, int pivot)
{
	for (auto it = myList.begin(); it != myList.end(); )
	{
		if (*it < pivot)
		{
			myList.push_front(*it);
			myList.erase(it++);
		}

		else
			it++;
	}
}

void displayList(std::list<int> myList)
{
	for (auto it = myList.begin(); it != myList.end(); it++)
		std::cout << *it << "  ";
	std::cout << std::endl;
}

std::list<int> myList = { 2, 4, 6, 8, 10, 1, 3, 5, 7, 9, -42, 55, 123 };



int main()
{
	partition(myList, 4);
	displayList(myList);
    return 0;
}

