#include "stdafx.h"
#include <iostream>

/*
Flip Bit to Win:  You have an integer and you can flip exactly one bit from a 0 to a 1.  Write code to find the 
length of the longest sequence of 1's you could create.

EXAMPLE:
Input:		1775   (or:  11011101111)
Output:		8
*/

/*
Bit operations in C++ work better with unsigned integers than with integers.  So let's keep it simple and use unsigned.

Main idea:  Start (say) at the rightmost bit and walk to the left one bit at a time.  Maintain an integer which keeps track
of how many 1's we've seen in a row.  Actually.... my code below is pretty self-documenting.  BUT there's one major flaw
in it right now:  I have a ton of side-variables.  I mean, we're looking at a 32 bit number and I'm using 8 variables in 
this problem.  One thing that makes it sting a little bit less is that my solution generalizes to integers of any fixed
length.
*/



/*
Did I read it wrong?  Maybe the integer is of variable length.  In which case, find the length real quick and use that
to dictate how long we loop for (and to dictate the trivial case of all 1's).  With this, our algorithm takes O(1) space
and O(length(x)) time.
*/


int winningFlipBit(unsigned x)
{
	if (x == UINT_MAX -1)
		return 31;

	unsigned finger = 1;
	int currentStreak = 0;
	int previousStreak = 0;
	int mostRecentGap = 0;
	int currentScore = 0;		
	int bestScore = 0;
	int bestIndex = 0;
	

	for (int i = 0; i < 32; i++)
	{
		if (x & finger)
		{
			currentStreak += 1;
		}

		else
		{
			currentScore = previousStreak + currentStreak + 1;	// We should optimize the +1 out.
			if (currentScore > bestScore)
			{
				bestScore = currentScore;
				bestIndex = mostRecentGap;
			}
			previousStreak = currentStreak;
			currentStreak = 0;
			mostRecentGap = i;
		}
		finger = finger << 1;
	}
	return bestScore;
}


int main()
{
	std::cout << winningFlipBit(9) << std::endl;


    return 0;
}

