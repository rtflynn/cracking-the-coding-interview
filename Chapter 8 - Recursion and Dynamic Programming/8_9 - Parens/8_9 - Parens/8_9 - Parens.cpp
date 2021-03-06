#include "stdafx.h"
#include <iostream>
#include <string>

/*
Parens:  Implement an algorithm to print all valid (e.g. properly opened and closed) combinations of n pairs of parentheses.

EXAMPLE:
	Input: 3
	Output:  ((())), (()()), (())(), ()(()), ()()()
*/

/*
Note that the number of parenthesizations (?) is exponential, because using ()() and (()), we can come up with 
2^N combinations of 2N pairs of parentheses.  So the number is exponential with base at least sqrt(2).

Now that I've finished the problem:  Totally sick - I got them to print in the same order as the example :D
Note the order in the example is basically 'alphabetical order', if we think of "(" as coming before ")".
[Or, easier to see perhaps, if we replace all "(" with "L" and all ")" with "R", we're talking actual alphabetical order]

So it's pretty clear why this occurred - we build our parenthesizations alphabetically in our recursion.
*/


void foo(int leftParensUsed, int rightParensUsed, int totalPairsParens, int currentLength, std::string currentString)
{
	if (currentLength == 2 * totalPairsParens)
	{
		std::cout << currentString << std::endl;
		// counter += 1;		// If we want to count the number of parenthesizations
		return;
	}

	if (leftParensUsed < totalPairsParens)		// We've used, say, 4 of our allowed 7 'left' parentheses
	{
		currentString.append("(");
		foo(leftParensUsed + 1, rightParensUsed, totalPairsParens, currentLength + 1, currentString);
		currentString.pop_back();
	}

	if (rightParensUsed < leftParensUsed)		// We've used more left parens than right, so we're allowed to add another right
	{
		currentString.append(")");
		foo(leftParensUsed, rightParensUsed + 1, totalPairsParens, currentLength + 1, currentString);
		currentString.pop_back();
	}	
}

void printAllParenthesizations(int n)
{
	std::string parenString = "";
	foo(0, 0, n, 0, parenString);
}


int main()
{
	std::cout << "3 pairs of parentheses:\n";
	printAllParenthesizations(3);
	std::cout << "5 pairs of parentheses:\n";
	printAllParenthesizations(5);
    return 0;
}