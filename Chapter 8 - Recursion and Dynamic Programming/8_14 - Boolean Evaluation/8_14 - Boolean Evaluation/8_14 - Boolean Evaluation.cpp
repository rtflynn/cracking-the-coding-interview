#include "stdafx.h"
#include <iostream>

/*
Boolean Evaluation:  Given a boolean expression consisting of the symbols 0 (false), 1 (true), & (AND), | (OR), and ^ (XOR), 
and a desired boolean result value myResult, implement a function to count the number of ways of parenthesizing the expression
such that it evaluates to myResult.  The expression should be fully parenthesized but not extraneously.

Example:
	countEval("l^0|0|1", false) -> 2
	countEval("0&0&0&1^1|0", true) -> 10
*/

/*
Main Idea:  Look for the "last" operation to be done, and evaluate the number of ways for the expressions to its left and
right to be parenthesized to come out to proper boolean values to make the whole thing come out how we want.

Ex:  "1&1&0&1|0^1|1&0", false:
	Well, if the last operation is (say) the third AND, then the left and right expressions are "1&1&0" and "1|0^1|1&0", 
	and we want to find the number of ways of making the left/right expressions  TF, FT, and FF.  If there are 4 ways of 
	making the left expression True and 3 ways of making the right expression False, then that's a total of 12 ways of
	making the entire thing False from just TF.  Add up contributions from all possibilities.  Also note that in each
	parenthesization, there will always be a 'last' operation because of the wording of the problem, i.e. that each
	expression is fully parenthesized but not overly so.

	We can memoize on the begin/end indices of the expression we're looking at if we want to.  This brings the runtime
	down to O(n^2) instead of the more naive approach's O(2^n).
*/


int catalan(int n)
{
	if (n == 0)
		return 1;
	int answer = 0;
	for (int i = 0; i < n; i++)
		answer += catalan(i)*catalan(n - i - 1);
	return answer;
}


// Assume our input has been cleaned up by some earlier function if necessary, so that all the odd-index characters
// are logical operations and all the even-index characters are booleans, 0 or 1.

// Example input for following function:
// myExpression = "1&1|0|1^0", myBool = false, beginIndex = 0, endIndex = 9, so that myExpression[endIndex] is out of bounds.

int numWaysToParen(const char * myExpression, const bool myBool, const int beginIndex, const int endIndex)
{	
	// If we memoize, then checking the memo table goes here.  Only store (say) function calls where myBool == true,
	// and subtract from catalan((endIndex - beginIndex - 1)/2) if myBool == false.

	// Additionally, update our memo table before returning any value anywhere else in this function.

	if (endIndex == beginIndex + 1)	
		return (int(myExpression[beginIndex]) - 48 == int(myBool));

	if (myBool == false)
		return catalan((endIndex - beginIndex - 1) / 2) - numWaysToParen(myExpression, !myBool, beginIndex, endIndex);
	
	int answer = 0;

	for (int i = beginIndex + 1; i < endIndex; i += 2)
	{
		int leftFalse = numWaysToParen(myExpression, false, beginIndex, i);
		int leftTrue = numWaysToParen(myExpression, true, beginIndex, i);
		int rightFalse = numWaysToParen(myExpression, false, i + 1, endIndex);
		int rightTrue = numWaysToParen(myExpression, true, i + 1, endIndex);

		if (myExpression[i] == '&')		
			answer += leftTrue * rightTrue;
		else if (myExpression[i] == '|')
			answer += leftTrue * rightTrue + leftFalse * rightTrue + leftTrue * rightFalse;
		else if (myExpression[i] == '^')		
			answer += leftTrue * rightFalse + leftFalse * rightTrue;
	}

	return answer;
}







int main()
{
	char myExpression[] = "1&1&1&1&1&1&1&1&1";
	std::cout << numWaysToParen(myExpression, true, 0, 17) << std::endl;
	std::cout << numWaysToParen(myExpression, false, 0, 17) << std::endl;

	//countEval("l^0|0|1", false) -> 2
	//countEval("0&0&0&1^1|0", true) -> 10
	std::cout << numWaysToParen("1^0|0|1", false, 0, 7) << std::endl;
	std::cout << numWaysToParen("0&0&0&1^1|0", true, 0, 11) << std::endl;


    return 0;
}

