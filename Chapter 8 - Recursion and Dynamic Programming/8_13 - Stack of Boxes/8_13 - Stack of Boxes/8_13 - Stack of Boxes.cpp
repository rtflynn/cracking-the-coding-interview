#include "stdafx.h"
#include <iostream>
#include <vector>



/*
Stack of Boxes:  You have a stack of n boxes, with widths w_i, heights h_i, and depths d_i.  The boxes cannot be rotated
and can only be stacked on top of one another if each box in the stack is strictly larger than the box above it in width, 
height, and depth.  Implement a method to compute the height of the tallest possible stack.  The height of a stack is the 
sum of the heights of each box.
*/

/*
OK, so, first impressions:  Definitely seems like a dynamic programming problem.  But might also be a good graph problem.
Reason being: since each box needs to be strictly larger in all three dimensions than any box above it, we don't get a
total ordering but just a partial ordering.  So we can create a graph whose vertices are the boxes, with an edge from B1 to 
B2 if B1 can sit under B2.  This gives us a DAG (acyclicity is clear), and we can even give this edge a weight which is the
height of B2.  Finally, create a 'source' vertex which has an edge to every other vertex, with edge weights the same as 
already described.  What we want is a maximum weight path in this graph.

With n boxes:  we have to check n^2 relations to find the edges of this graph.  In the worst case, our graph has order of 
n vertices and n^2 edges, and finding a longest path can take O(n^2) time.  [Even if the graph is sparse, we spend O(n^2)
time constructing the graph.]
*/

/*
A graph might also help with non graph-related solutions because we can use a depth-first-search to give a topological
ordering to the boxes, and then use (say) a dynamic programming technique to finish the problem.  

We might be able to get a topological sort without explicitly constructing the graph if we very carefully sort the boxes
by each dimension separately.  As in, first sort by length.  Next, among boxes of the same length, sort by width.  Finally, 
among boxes with a fixed length and width, sort by height.  Then we're guaranteed that if box A can fit below box B, then
A appears before B in our list.  Sounds like quite a bit of processing but all the sorts together take O(nlogn) time.  
Also note that the second and third sorts take something more similar to O(n) time, because we're sorting subsets which are
likely of significantly smaller size than the original set.  That is, the second sort looks more like 
Sum( mlogm )  where  Sum(m) == n.  (And similarly for the third sort).

Assuming we have sorted the boxes in this manner, here's the pseudocode of the algorithm: 

	int currentRecords[numBoxes] {0};
	int bestRecord = 0;

	for (int i=0; i < numBoxes; i++)
	{
		for (int j=0; j < i; j++)	
		{
			if (boxes[i] < boxes[j])		// Box i is large enough for Box j to sit on
			{
				int totalHeight = currentRecords[i] + boxes[j].height;
				if (totalHeight > currentRecords[j])
					currentRecords[j] = totalHeight;	
					// And if we want to, update a back-pointer to construct the best tower of boxes at the end
			}
			if (currentRecords[j] > bestRecord)
				bestRecord = currentRecords[j];
		}
	}

	return bestRecord;			// And again, if we want, return the actual set of boxes realizing this record.
*/

/*
The previous algorithm takes time O(n^2) since we loop through all pairs of boxes and spend constant time in each subcase.
It has space complexity O(n) since we need to store the currentRecords array.
This is probably close to optimal.  It might be possible to get this down a bit but I'm not seeing it quite yet.
One thing that might help would be a smarter data structure which keeps better track of the partial ordering of the boxes,
yet takes less time to construct than a graph.
*/


struct Box
{
	int length, width, height;
	Box(int l = 0, int w = 0, int h = 0) : length(l), width(w), height(h) {}
	void saySomething() const 
	{
		std::cout << "Box with length " << length << ", width " << width << ", height " << height << ".\n"; 
	}
	bool operator<(const Box &other) const
	{
		if (length < other.length)
			return true;
		if (length > other.length)
			return false;				// If we continue past this line then we know length == other.length
		if (width < other.width)
			return true;
		if (width > other.width)
			return false;
		return (height < other.height);
	}

	bool canSitOn(const Box &other) const
	{
		return ((length < other.length) and (width < other.width) and (height < other.height));
	}
};

void sortBoxes(std::vector<Box> &boxVec)
{
	bool keepSorting = true;
	while (keepSorting)
	{
		keepSorting = false;
		for (auto it = boxVec.begin(); it != boxVec.end(); it++)
		{
			if ((it + 1) == boxVec.end())
			{
			}// do nothing
			else if ((*it) < (*(it+1)))
			{
				keepSorting = true;
				Box temp = *it;
				*it = *(it + 1);
				*(it + 1) = temp;
			}
		}
	}
}


void highestStack(const std::vector<Box> &boxVec)
{
	int numBoxes = boxVec.size();
	std::vector<int> currentRecords = std::vector<int>(numBoxes, 0);
	int bestRecord = 0;

	std::vector<int> backPointers = std::vector<int>(numBoxes, numBoxes-1);		// To track the best path
	int bestRecordIndex = numBoxes-1;

	for (int i = numBoxes - 1; i > 0; i--)
	{
		for (int j = i + 1; j < numBoxes; j++)
		{
			if (boxVec[j].canSitOn(boxVec[i]))
			{
				int currentStackHeight = currentRecords[j] + boxVec[i].height;
				if (currentStackHeight > currentRecords[i])
				{
					currentRecords[i] = currentStackHeight;
					backPointers[i] = j;
				}
			}
		}
		if (currentRecords[i] > bestRecord)
		{
			bestRecord = currentRecords[i];
			bestRecordIndex = i;
		}
	}

	std::cout << "The highest stack has height " << bestRecord << ".\n";
	while (bestRecordIndex < numBoxes - 1)
	{
		boxVec[bestRecordIndex].saySomething();
		bestRecordIndex = backPointers[bestRecordIndex];
	}

	std::cout << "\n";
}





int main()
{
	std::vector<Box> someBoxes;

	someBoxes.push_back(Box(1, 2, 3));
	someBoxes.push_back(Box(4, 5, 6));
	someBoxes.push_back(Box(7, 8, 9));
	someBoxes.push_back(Box(5, 4, 3));
	someBoxes.push_back(Box(8, 7, 6));
	someBoxes.push_back(Box(4, 3, 2));
	someBoxes.push_back(Box(7, 7, 7));
	someBoxes.push_back(Box(4, 5, 9));
	someBoxes.push_back(Box(5, 6, 7));



	highestStack(someBoxes);

	

    return 0;
}

