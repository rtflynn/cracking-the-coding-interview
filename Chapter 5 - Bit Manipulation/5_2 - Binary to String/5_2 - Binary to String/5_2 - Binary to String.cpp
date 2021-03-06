#include "stdafx.h"
#include <iostream>

/*
Binary to String: Given a real number between 0 and 1 (e.g., 0.72) that is passed in as a double, print the binary
representation.  If the number cannot be represented accurately in binary with at most 32 characters, print "ERROR."
*/

/*
What I'm assuming is meant here is:  A binary fraction between 0 and 1 can be represented as something like 
0.00101110100101, where the first place after the period is the 'halves' place, the next is the 'quarters' place, etc.

I'm concerned about the 'cannot be represented accurately in binary with 32 characters'.  Any number between 0 and 1 should
be representable to within 1 part in 2^32 with such an expansion.  Does the author mean 'cannot be represented exactly'?  
If so, we can't even probe that using doubles, so.... When are we supposed to print 'ERROR.' ???

I'm just going to assume that she wants 'ERROR.' printed if the input was not between 0 and 1.
Also, she only wants the string printed to screen, not saved as a string or returned as a string.  It would be easy to
modify this to do those things, but since it wasn't asked for, I'll opt not to so we can avoid another #include.
*/



void binaryToString(double x)
{
	if ((x < 0) or (x > 1))
	{
		std::cout << "ERROR." << std::endl;
		return;
	}

	std::cout << "0.";

	for (int i = 0; i < 32; i++)
	{
		x *= 2;
		if (x > 1)
		{
			std::cout << "1";
			x -= 1;
		}
		else
			std::cout << "0";
	}
	std::cout << std::endl;
}








int main()
{
	binaryToString(0.72);
    return 0;
}

