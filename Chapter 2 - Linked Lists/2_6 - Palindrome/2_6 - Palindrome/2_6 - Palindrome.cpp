#include "stdafx.h"
#include <iostream>
#include <list>


// Once again (this is becoming an annoying theme...) it has not been made clear whether the list is
// singly or doubly linked, nor has it been made clear what information we have available - for example,
// do we know the length of the list, etc.

// Whether the list is singly or doubly linked makes no difference in 'big oh' runtime, since both implementations will be O(n),
// where n is the length of the list.  However the implementations will be very different.  Let's just assume the list is 
// singly-linked, because doubly-linked is trivial.

std::list<int> reverse(std::list<int> const &original)
{
	std::list<int> tempAnswer;
	for (auto it = original.begin(); it != original.end(); it++)
		tempAnswer.push_front(*it);
	return tempAnswer;
}


bool listsAreEqual(std::list<int> list1, std::list<int> list2)
{
	auto it1 = list1.begin();
	auto end1 = list1.end();
	for (auto it2 = list2.begin(); it2 != list2.end(); it2++)
	{
		if (it1 == end1)		// We've reached the end of list1 but not the end of list2/
			return false;		// Note that we don't really have to worry about this happening because list2 and list1 have the same length.
								// But it's safe, in case in the future we want to apply this method in a wider context.
		if (*it1 != *it2)
			return false;

		it1++;
	}
	return true;
}


bool isPalindrome(std::list<int> someList)
{
	return listsAreEqual(someList, reverse(someList));
}

std::list<int> palindromicListOdd = { 1, 0, 5, 6, 4, 6, 5, 0, 1 };
std::list<int> palindromicListEven = { 2, 4, 6, 8, 10, 10, 8, 6, 4, 2 };
std::list<int> nonPalindromic = { 1, 3, 5, 7, 9, 11 };


int main()
{
	if (isPalindrome(palindromicListOdd))
		std::cout << "Passed the first test!\n";
	if (isPalindrome(palindromicListEven))
		std::cout << "Passed the second test!\n";
	if (!isPalindrome(nonPalindromic))
		std::cout << "Passed the third test!\n";



    return 0;
}

