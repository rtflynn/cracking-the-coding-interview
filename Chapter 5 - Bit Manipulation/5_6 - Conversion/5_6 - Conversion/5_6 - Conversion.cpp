#include "stdafx.h"
#include <iostream>

/*
Conversion:  Write a function to determine the number of bits you would need to flip to convert integer A to B.

EXAMPLE:
Input:		29 (i.e. 11101), 15 (i.e. 01111)
Output:		2
*/


/*
A bit needs to be flipped if and only if A and B differ in that bit - i.e. if and only if the XOR of the corresponding
bits is 1.  So build A xor B, and count the number of 1s.
*/


int conversion(unsigned A, unsigned B)
{
	unsigned differenceBits = A ^ B;
	int answer = 0;
	while (differenceBits != 0)
	{
		if (differenceBits & 1)		
			answer += 1;		
		differenceBits = differenceBits >> 1;
	}
	return answer;
}


int main()
{
	std::cout << conversion(5, 7) << std::endl;					 // Answer is 1
	std::cout << conversion(1 + 4 + 16, 2 + 8) << std::endl;	 // Answer is 5
	std::cout << conversion(UINT_MAX, 0) << std::endl;			 // Answer is 32



    return 0;
}

