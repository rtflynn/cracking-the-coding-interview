#include "stdafx.h"
#include <iostream>
#include <unordered_map>


/*
Paths with Sum:  You are given a binary tree in which each node contains an integer value (which might be
positive or negative).  Design an algorithm to count the number of paths that sum to a given value.  The
path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from 
parent nodes to child nodes).
*/


/*
First of all, there are O(V*height(T)) such paths, so for a balanced binary tree we're looking at
a likely worst-case O(nlogn) time complexity.  

At first this seems like a dynamic programming problem.  I'm not giving up on that, but I think there's
an easy solution that actually runs in O(nlogn) time.  The problem is that this method also takes
O(nlogn) space.  Starting at the root, walk down each path keeping track of all partial sums at each node, 
say in a list (each node gets a list).  For example, if the root is 8 and the left node is 29, then the root
gets a list consisting of { 8 } and the left node gets the list { 37, 29 }, since the two paths so far are
the one starting at the root and the one starting at the left node.  If the left node's left child is -4, then
this child's list is { 33, 25, -4 }, and so on.  The maximum length of this list is height(T), and each node 
gets one, which explains the O(nlogn) space requirement with this approach.  At the end we count the number of
instances of our given value in all these lists.  The time complexity is also O(nlogn), because at each node
we do an amount of work which is 'constant plus O(length of list)'.  

Back to dynamic programming...  We'd like to break our problem into two subproblems of roughly half the size
of the original, since then we'd get a linear time complexity.  Naively looking at it, we might be tempted
to look at the left and right subtrees - except now we're looking for either paths that sum to k, or paths
that start at the top of their subtree and sum to (k - root).  So the number of problems increases and this
kills the linear time complexity.  Let's see if this can be salvaged or if some nicer approach might work.
(And again, I'm fairly convinced this problem should take nlogn time at best, so there might not be such an
approach.)

*/

/*
Aha:  Well, my intuition was off - it CAN be done in linear time (and logarithmic space).  It was a big mistake
to assume that we have to consider each pair of compatible nodes - let's chalk it up to being a bit tired at
the time.  Anyhow, we can do the following:  

	- The overall structure of the solution is of a depth-first search.  We want to do everything we need to do
	at a Node "n" in constant time when we're there. 
	
	- As we walk down our tree, maintain (i) an integer runningSum which gives the sum of all vertices from
	the root to the current node, and (ii) a hash table of the previous running sums along this path.

	- Make sure to "backwards maintain" these as well - i.e. when our BFS is finally finished with the node "n"
	for good, remove (one copy of) our running sum from the hash table, and change the running sum back to 
	what it was before we visited this node in the first place.  
	
	- Anyhow, the main observation that will give us linear runtime is the following:  If we take two terms 
	in our hash table corresponding to Nodes n1 and n2, and subtract them, we get the PathSum for the path from
	successor(n1) to n2.  (Here successor means the next term after n1 in the path from n1 to n2).

	- Once we've reached a vertex "n" and appropriately updated our hash table and our runningSum, the number
	of paths in our tree ending at "n" and having PathSum equal to K is precisely the number of times 
	"n->m_data - K" appears in the hash table.  This lookup costs constant time, and the rest of the analysis
	is straightforward.  

Finally note that our hash table (as long as we remember to delete entries as we leave nodes for the last time)
will take O(height(T)) space, so for balanced trees we're talking log(n) space and n time complexity.

*/



class Node
{
public:
	Node * m_parent = nullptr;
	Node * m_left = nullptr;
	Node * m_right = nullptr;
	int m_data;

	Node(int data = 0) : m_data(data) {}

	Node * addLeftChild(int data)
	{
		if (m_left != nullptr)
		{
			std::cout << "There's already a left child!\n";
			return m_left;
		}
		Node * newChild = new Node(data);
		m_left = newChild;
		newChild->m_parent = this;
		return newChild;
	}

	Node * addRightChild(int data)
	{
		if (m_right != nullptr)
		{
			std::cout << "There's already a right child!\n";
			return m_right;
		}
		Node * newChild = new Node(data);
		m_right = newChild;
		newChild->m_parent = this;
		return newChild;
	}

};




// One thing:  We're thinking of unordered_map as a multiset, i.e. sumsSoFar(7) = 2 means that our
// multiset contains 7 with multiplicity 2.  With this language, we'll want to initialize our
// multiset to contain 0 with multiplicity 1 before using it as an argument in this function.

void numPathsWithGivenSum(Node * someNode, std::unordered_map<int, int> &sumsSoFar, int runningSum, int target, int &answer)
{
	if (someNode == nullptr)
		return;
	runningSum += someNode->m_data;
	sumsSoFar[runningSum] += 1;
	int numberOfNewGoodPaths = sumsSoFar[runningSum - target];

	answer += numberOfNewGoodPaths;

	numPathsWithGivenSum(someNode->m_left, sumsSoFar, runningSum, target, answer);
	numPathsWithGivenSum(someNode->m_right, sumsSoFar, runningSum, target, answer);

	//sumsSoFar[runningSum] -= 1;		// This took linear space
	if (sumsSoFar[runningSum] == 1)
		sumsSoFar.erase(runningSum);
	else
		sumsSoFar[runningSum] -= 1;		// Instead we take log(n) space with this simple modification.

	runningSum -= someNode->m_data;
}

int numPathsSummingToK(Node * head, int target)
{
	std::unordered_map<int, int> sumsStartingAtRoot;
	sumsStartingAtRoot[0] = 1;
	int answer = 0;

	numPathsWithGivenSum(head, sumsStartingAtRoot, 0, target, answer);
	return answer;
}






Node * createExample()
{
	Node * head = new Node(5);
	Node * left = head->addLeftChild(1);
	Node * leftleft = left->addLeftChild(3);
	Node * leftright = left->addRightChild(-2);
	Node * leftrightleft = leftright->addLeftChild(6);
	Node * leftrightright = leftright->addRightChild(7);
	Node * right = head->addRightChild(-1);
	Node * rightleft = right->addLeftChild(5);
	Node * rightright = right->addRightChild(3);
	Node * rightrightleft = rightright->addLeftChild(-3);
	Node * rightrightright = rightright->addRightChild(2);
	return head;
}



int main()
{
	Node * ourExample = createExample();
	int targetSum = 4;	// This graph has 7 paths summing to 4

	std::cout << numPathsSummingToK(ourExample, targetSum) << std::endl;

    return 0;
}

