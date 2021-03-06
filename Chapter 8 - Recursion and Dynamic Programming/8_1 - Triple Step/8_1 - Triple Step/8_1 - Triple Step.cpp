// 8_1 - Triple Step.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>



int naiveTripleStep(int n) 
{
	if (n < 0)
		return 0;
	if (n <= 1)
		return 1;
	return naiveTripleStep(n - 1) + naiveTripleStep(n - 2) + naiveTripleStep(n - 3);
}

int * memoizedTripleStep(int n)
{
	int * memo = new int[n];
	memo[0] = 1;
	memo[1] = 1;
	memo[2] = 2;
	for (int i = 3; i < n; i++)
		memo[i] = memo[i - 1] + memo[i - 2] + memo[i - 3];
	return memo;
}

long long inlineTripleStep(int n)
{
	long long prevprev = 0;
	long long prev = 0;
	long long current = 1;
	long long temp;
	for (int i = 0; i < n; i++) {
		temp = prevprev + prev + current;
		prevprev = prev;
		prev = current;
		current = temp;
	}
	return current;
}











int main()
{
	int highestTermToCompute = 350;
	std::cout << inlineTripleStep(highestTermToCompute) << std::endl;

    return 0;
}

