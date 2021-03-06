#include "stdafx.h"
#include <iostream>
#include <cassert>


/*
Coins:  Given an infinite number of Quarters, Dimes, Nickels, and Pennies, write code to calculate the total number of 
ways of making n cents.
*/

/*
Idea:  This at first seems like a good problem for memoization.  Consider first the number of quarters used; if we use 
q Quarters then we have to make  n - 25q  cents our of pennies, nickels, and dimes only.  Next consider the number of
dimes used, and continue down.  So we end up needing to know the values of 4 functions.  One benefit is, once we have
built up a memo table of previous values of these functions, it becomes quick to calculate and memoize new values.

However, I think there may be a significantly quicker algorithm.  Let's name the functions QDNP(n)  (which stands for
Quarters Dimes Nickels and Pennies), DNP(n), NP(n), and P(n).  For starters, P(n) is constant equal to 1.
But this means that NP(n) is essentially linear with slope 1/5, and this means that DNP(n) is essentially quadratic, etc.

So, we can hopefully find a polynomial which gives the answer exactly, and thus reduce the problem to O(1) space and time
complexity.


UPDATE:  So, I managed to find the polynomials for P(n) [trivially == 1], NP(n), and DNP(n).  The polynomial for
QDNP(n) will be cubic and will have terms involving (n/25), (n/10), (n/5).  It's difficult to figure out what these
terms are.  One idea:  Assume the answer is cubic in these terms with some coefficients, and use known values of QDNP
to get a system of equations our coeffs must satisfy.  If done correctly we can generalize to arbitrary number of coins
with arbitrary positive integer value - i.e. we can make a machine that outputs these polynomials.  

But for now I'm going to leave the solution as is since it already solves the problem.
*/


int DNP(int n);
int QDNP(int n) // Quarters, Dimes, Nickels, Pennies.  
{
	int sum = 0;
	for (int i = 0; 25 * i <= n; i++)
		sum += DNP(n - 25 * i);
	return sum;				
}

int NP(int n);
int DNP(int n)	// Dimes, Nickels, Pennies
{
	int sum = 0;
	for (int i = 0; 10*i <= n; i++)
		sum += NP(n - 10 * i);
	return sum;
}

int NP(int n)	// Nickels, Pennies
{
	int sum = 0;
	for (int i = 0;  5*i <= n; i++)
		sum += 1;
	return sum;
}							

int quickDNP(int n)
{
	int maxNumDimes = (n / 10) + 1;
	return maxNumDimes * ((n / 5) + 1) - (maxNumDimes - 1)*maxNumDimes;
}

int quickNP(int n)							// Gives the same answer as NP(n).
{
	return (n / 5) + 1;
}

int P(int n)	// Pennies
{
	return 1;
}

int sortaQuickQDNP(int n)				// Runs in linear rather than constant time :/  
{
	int sum = 0;
	for (int i = 0; 25 * i <= n; i++)
		sum += quickDNP(n - 25*i);
	return sum;
}

int main()
{
	// Finite differences to figure out what DNP(k) is

	for (int k = 1; k < 100; k++)
		std::cout << "k = " << k << ": " << QDNP(k) << '\n';


	return 0;
}

