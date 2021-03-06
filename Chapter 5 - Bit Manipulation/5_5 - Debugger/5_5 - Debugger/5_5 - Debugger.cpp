#include "stdafx.h"
#include <iostream>

/*
Debugger:  Explain what the following code does:  ((n & (n-1)) == 0)
*/


/*
I'm surprised this one's in here.  It's trivial.  The only way n and (n-1) bitwise-and to 0 is if they have
no 1's in common.  The only way for this to occur is if every 1 in (n-1) becomes a 0 after adding 1, and the only
way this can happen is if (n-1) consisted of a bunch of trailing 1's with everything else 0's.  That is, 
((n & (n-1)) == 0)  is true  if and only if n is a power of 2.

(To be a bit more precise here:  if n is unsigned then what I just said is true.  But another possibility is n is an integer,
in which case 0 and -1 also bitwise-and to 0, so for integers the answer is that n is a power of 2 or n is 0)

*/




int main()
{
    return 0;
}

