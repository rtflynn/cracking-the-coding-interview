#include "stdafx.h"
#include <iostream>
#include <vector>



/*
Power Set:  Write a function to return all subsets of a set.
*/


/*
First, what is meant by 'return all subsets'?  C++ only allows us to return one object - so do they want us to
create a set containing all the subsets of X, and return that set?  Or do they just want us to (say) print all
the subsets?  Let's take the prompt literally and return an object which contains all the subsets of X.

As for expected complexity:  If X is a set with n elements, then there are 2^n subsets and their average length is n/2,
so we're talking about O(n*2^n) space to store them, and clearly at least this much time to compute them.
*/

/*
OK, now that I'm finished and I've read the solution in CTCI, boy do I feel dumb for not seeing the 'bitmask approach'.
That is, for sets of size n, there are 2^n bitmasks  (e.g. 1100010010011001), each of which uniquely determines a subset.
These are just integers between 0 and 2^n - 1.  So we can loop through integers, and for each integer i we can build
a subset by including/not including elements corresponding to 1's/0's in our integer.

It's definitely more elegant, but I'm not positive that it's any better.
*/


// Let's say we're working with sets of integers to keep things simple.

std::vector<std::vector<int>> insertInAllSubsets(std::vector<std::vector<int>> ourSubset, int someInt)
{
	for (auto it = ourSubset.begin(); it != ourSubset.end(); it++)
	{
		(*it).push_back(someInt);
	}

	return ourSubset;
	// Since we didn't pass it in by address, this makes and returns a copy.
}



std::vector<std::vector<int>> powerSet(std::vector<int> originalSet)
{
	if (originalSet.size() == 1)
	{
		std::vector<std::vector<int>> answer;
		answer.push_back(originalSet);
		answer.push_back(std::vector<int>());
		return answer;
	}

	int lastElt = originalSet.back();
	originalSet.pop_back();

	std::vector<std::vector<int>> subsetsOfInitialSegment = powerSet(originalSet);
	std::vector<std::vector<int>> subsetsContainingLastElt = insertInAllSubsets(subsetsOfInitialSegment, lastElt);
	subsetsOfInitialSegment.insert(subsetsOfInitialSegment.end(), subsetsContainingLastElt.begin(), subsetsContainingLastElt.end());


	return subsetsOfInitialSegment;
}




int main()
{
	std::vector<int> ourInts{ 1, 3, 5, 7, 9 };

	std::vector<std::vector<int>> allSubsets = powerSet(ourInts);

	for (auto it = allSubsets.begin(); it != allSubsets.end(); it++)
	{
		for (auto derp = (*it).begin(); derp != (*it).end(); derp++)
			std::cout << *derp << " ";
		std::cout << std::endl;
	}

    return 0;
}

