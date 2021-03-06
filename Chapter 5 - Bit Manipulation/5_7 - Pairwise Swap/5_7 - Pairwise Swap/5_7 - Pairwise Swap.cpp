#include "stdafx.h"
#include <iostream>

/*
Pairwise Swap:  Write a program to swap odd and even bits in an integer with as few instructions as possible.
(e.g. bits 0 and 1 are swapped, bits 2 and 3 are swapped, and so on).
*/


/*
Well, this could be referring to 'as few machine instructions as possible', or 'as few lines of code as possible', and
these are very different metrics.
*/

/*
Turns out, this problem was a good learning experience.  I tried all kinds of dumb ways to do this, and finally 
read the answer in the book.  Wow, was I way off.  Maybe it was dumb not to see the trick, but I'll definitely
be able to use similar tricks now that I've seen it once.
*/

unsigned pairwiseSwap(unsigned x)			// This works but takes a lot of steps.
{
	unsigned firstFinger = 1;
	unsigned secondFinger = 2;

	while (secondFinger < UINT_MAX / 2)
	{
		if (!((firstFinger & x) == (secondFinger & x)))
		{
			std::cout << "First finger AND x = " << (firstFinger & x) << ".\n";
			std::cout << "Second finger AND x = " << (secondFinger & x) << ".\n";
			x += (firstFinger & x) - ((secondFinger & x)>>1);

		}
				
		firstFinger = secondFinger << 1;
		secondFinger = firstFinger << 1;
	}

	return x;
}

unsigned pairwiseSwap2(unsigned x)
{
	int oddBits = (x & 1431655765);
	int evenBits = (x & -1431655766);
	return (oddBits << 1) + (evenBits >> 1);
}


int main()
{
	for (int i = 0; i < 15; i++)
		std::cout << "The pairwise swap of " << i << " is " << pairwiseSwap2(i) << ".\n";

    return 0;
}

