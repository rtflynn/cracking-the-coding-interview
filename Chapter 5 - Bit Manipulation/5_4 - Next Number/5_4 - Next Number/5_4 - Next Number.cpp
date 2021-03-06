#include "stdafx.h"
#include <iostream>

/*
Next Number:  Given a positive integer, print the next smallest and next largest number that have the same number of 1
bits in their binary representation.
*/

/*
Note to reader:  This solution is significantly messier than most of the other solutions.  Also, while the main idea
behind the solution ended up being simple, it wasn't so simple to see/prove that it was correct.  

Finally, I was able to implement the prevNumber function using the nextNumber function because of the following observations:

	-	x and y have the same number of binary 1's if and only if ~x and ~y have the same number of binary 1's
	-	x > y if and only if ~x < ~y
	
So, if 'a' is some unsigned integer and we call some smaller unsigned with the same number of binary 1's  'b', then
we have that 'b < a'   and   'b and a have the same number of binary 1s'.

If 'c' is some other unsigned with the same number of binary 1's  and  b < c < a, then ~b > ~c > ~a .  
So if we define b = ~nextNumber(~a), then b = prevNumber(a).
*/


unsigned nextNumber(unsigned x)		// prints the next (larger) number which can be written with the same number of 1's
{	
	unsigned finger = 1;
	bool haveSeenAOne = false;
	while (!haveSeenAOne)
	{		
		haveSeenAOne = (finger & x);
		finger = finger << 1;
	}

	unsigned numOnesSeenSoFar = 1;
	unsigned leastSignificantZero = 0;
	bool haveFoundANontrailingZero = false;
	while (!haveFoundANontrailingZero)
	{
		if (finger > UINT_MAX/2)
		{
			std::cout << "This number has the form 111111....111110000....000, so there is no way to rearrange the 1s "
				<< "to create a larger number.\n";
			return 0;	// or throw exception
		}
		if (!(finger & x))
			haveFoundANontrailingZero = true;
		else
		{
			numOnesSeenSoFar += 1;
			finger = finger << 1;
		}
	}
	leastSignificantZero = finger;

	unsigned mask = ~(finger - 1);			// 11111....11110000000, the last 1 being at the current position

	x = x & mask;
	x += finger;
	finger = 1;

	for (int i = 0; i < numOnesSeenSoFar - 1; i++)
	{
		x += finger;
		finger = finger << 1;
	}

	std::cout << x << std::endl;
	return x;
}



unsigned prevNumber(unsigned x)
{
	unsigned xComplement = ~x;
	unsigned y = nextNumber(xComplement);
	std::cout << ~y << std::endl;
	return ~y;
}


void nextAndPrev(unsigned x)
{
	unsigned prev = prevNumber(x);
	unsigned next = nextNumber(x);

	std::cout << "Our input is " << x << ".  The next larger number with the same number of binary 1's is "
		<< next << " and the next smaller number with the same number of binary 1s is " << prev << ".\n";
}




int main()
{
	nextNumber(88);
	nextNumber(39);
	nextNumber(UINT_MAX - 15);

	nextAndPrev(88);
	nextAndPrev(39);



	return 0;
}

