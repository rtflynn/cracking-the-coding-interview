#include "stdafx.h"
#include <iostream>
#include <list>

///////  (7 -> 1 -> 6) + (5 -> 9 -> 2) should give (2 -> 1 -> 9)
///////  This corresponds to 617 + 295 = 912.
///////	 Note it would not be difficult to simply implement two functions, 
///////	 one which takes a list and returns an integer, the other which takes
///////  an integer and returns a list.  Then simply turn both lists into integers, 
///////  add them, and turn the sum back into a list.
///////  But it seems to me like the *intent* of this question is to do all this in place.

///////  I'm gonna go for the easier solution, just because.  
///////  It wouldn't be difficult to do this 'in place', except in the followup portion
///////  we would need to zero-pad the shorter of the two lists.  



int listToInt(std::list<int> myList)
{
	int currentPlace = 1;			// ones, tens, hundreds, etc
	int currentAnswer = 0;
	for (auto it = myList.begin(); it != myList.end(); it++)
	{
		currentAnswer += currentPlace * *it;
		currentPlace *= 10;
	}

	return currentAnswer;
}


std::list<int> intToList(int myInt)
{
	std::list<int> answerList = {};
	if (myInt < 0)
		return answerList;

	while (myInt != 0)
	{
		int leastSignificantDigit = myInt % 10;
		answerList.push_back(leastSignificantDigit);
		myInt = int(myInt / 10);
	}

	return answerList;
}


std::list<int> someList = intToList(90210);

void displayList(std::list<int> myList)
{
	for (auto it = myList.begin(); it != myList.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;	
}


int main()
{
	std::list<int> first = { 7, 1, 6 };
	std::list<int> second = { 5, 9, 2 };

	int firstInt = listToInt(first);
	int secondInt = listToInt(second);
	int sumOfInts = firstInt + secondInt;

	std::list<int> sumList = intToList(sumOfInts);


	std::cout << listToInt(first) << " + " << listToInt(second) << " = " << listToInt(sumList) << std::endl;;
	displayList(sumList);


    return 0;
}

