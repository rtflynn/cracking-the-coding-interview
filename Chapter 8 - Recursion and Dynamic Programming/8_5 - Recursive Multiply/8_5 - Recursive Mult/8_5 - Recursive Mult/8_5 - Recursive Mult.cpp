// 8_5 - Recursive Mult.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

unsigned int recursiveMultiply(unsigned int a, unsigned int b)
{
	if (a == 0)
		return 0;
	if (a % 2 == 0)
		return recursiveMultiply(a >> 1, b) << 1;
	if (a % 2 == 1)
		return recursiveMultiply(a - 1, b) + b;
}


unsigned int slightlySmarterRecursiveMultiply(unsigned int a, unsigned int b)
{
	unsigned int smaller = a < b ? a : b;
	unsigned int larger = a < b ? b : a;
	return recursiveMultiply(smaller, larger);

}

/* the slightly smarter approach is to make sure that the first input is smaller... well, really, it would be to consider which of the inputs has fewer 1's.  And smarter
than that would be to recursively decide over and over again which argument goes first.  But all these checks may very easily cost us more than we gain from them.  */


int main()
{
	unsigned int myInt = recursiveMultiply(12, 5);
	std::cout << myInt << std::endl;

	unsigned int newInt = slightlySmarterRecursiveMultiply(12, 15);
	std::cout << newInt << std::endl;


    return 0;
}

