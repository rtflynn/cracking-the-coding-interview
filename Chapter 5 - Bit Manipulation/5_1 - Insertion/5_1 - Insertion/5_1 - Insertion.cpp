#include "stdafx.h"
#include <iostream>

/*
Insertion:  You are given two 32-bit numbers, N and M, and two bit positions, i and j.  Write a method to
insert M into N such that M starts at bit j and ends at bit i.  You can assume that the bits j through i
have enough space to fit all of M.  That is, if M = 10011, you can assume that there are at least 5 bits
between j and i.  You would not, for example, have j = 3 and i = 2, because M could not fully fit between
bit 3 and bit 2.

EXAMPLE

Input:    N = 10000000000, M = 10011, i = 2, j = 6
Output:   N = 10001001100

Note:  Judging by the example (and the j=3, i=2 talk at the end of the problem), "position 0" refers to
the rightmost position, not the leftmost.
*/

/*
Any solution should run in constant time.  Question is, do we care enough to make it run fast?
I don't actually know how fast/slow the bit operations are --- for example, ANDing a 32-bit integer with
a mask like  00000...000010 - does this take as much time as ANDing two arbitrary 32-bit integers?

From what I've learned building an 8-bit ALU, they really should take the same amount of time (because XOR of
two integers is a single instruction).  But I can imagine that there might be some optimization which allows
checking a boolean flag in an integer in, like, a half-instruction.  Let's just drop the matter entirely...

We could binary search on masks 000...001000...00 (1 in the i position) to find out the size of our integer
which is to be inserted (No guarantee was made that len(M) = j - i + 1, just that len(M) is not larger than
this quantity).  There's also the question of... does   x<<5  take more time, or the same amount of time, as
x<<1.  Again, this seems really unnecessary so let's just work on getting this thing done.  After all, bit 
manipulation is like the most boring part of this whole project.
*/


unsigned int insert(unsigned M, unsigned N, unsigned i, unsigned j)
{
	unsigned bitmask_beginning = (1 << (j + 1)) - 1;			// 000....00111111111
	unsigned bitmask_ending = (1 << (i )) - 1;					// 000....00000000111
	unsigned bitmask = ~(bitmask_beginning - bitmask_ending);	// 000.

	N = N & bitmask;
	M = M << i;
	return N | M;
}



int main()
{
	std::cout << insert(19, 1024, 2, 6) << std::endl;

	return 0;
}

