#include "stdafx.h"
#include <iostream>


/*
First Common Ancestor: Design an algorithm and write code to find the first common ancestor of two nodes
in a binary tree.  Avoid storing additional nodes in a data structure.  NOTE: This is not necessarily a BST.
*/



/*
First idea:  From a given node, continually move to the parent node, keeping track of whether it was a right
or left move.  Record these decisions as bits (Say 0 for left, 1 for right).  Take the resulting sequence of bits
and reverse it.  Now if we have two nodes, their first common ancestor will occur at the last position where
the associated bit sequences agree.

Note this (sort of) breaks the rule of not storing additional nodes in a data structure.  It might be forgiven, 
however, because we're only storing a total of 2*height(T) bits, and binary trees don't get that tall as long
as they're balanced.  i.e. we're using O(log(size(T))) space, which for balanced trees may as well be O(1).
(Like, the biggest balanced tree we can even store in the observable universe would only require a few hundred
bytes for this process).

Anyhow, if we want to not use this O(log(T)) space - say because our binary tree isn't balanced - then we can
try other things.  But the things that come to mind quickly take O(log(T)^2) runtime.

Example:  Set v1 = firstVertex and v2 = secondVertex.  
While (v2 != rootOfTree)
	if (v2 == v1) return v2;
	else check v2 against v1's parent, grandparent, etc [ log(T) steps at most ]
	else v2 = v2.parent;
*/

/*
Another idea:  We can figure out the depth of v1 and v2 by taking parents until we hit the root.  
Say depth(v1) = m    and     depth(v2) = n.  Without loss of generality let's say m > n.
Then starting at v1, take the parent  (m - n)  times.  This is the earliest place along the path from v1
to the root where we have a possibility of finding the first common ancestor of v1 and v2.
Now simply take parents of both vertices we're considering until we find a match.  
This takes O(max(depth(v1), depth(v2))) time and constant space.  And it's simpler than the previous solution.
*/


class Node
{
public:
	Node * m_parent = nullptr;
	Node * m_left = nullptr;
	Node * m_right = nullptr;
	int m_data;
	Node(int data = 0) : m_data(data) {}
};


int depth(Node * v)			// The root has depth 0
{
	if (v == nullptr)
		return -1;
	Node * current = v;
	int currentDepth = 0;

	while (current->m_parent != nullptr)
	{
		current = current->m_parent;
		currentDepth += 1;
	}

	return currentDepth;
}

Node * kthAncestor(Node * v, int k)
{
	if ((v == nullptr) or (k < 0))
		return nullptr;
	Node * temp = v;
	while (k > 0)
	{
		temp = temp->m_parent;
		if (temp == nullptr)
			return nullptr;
		k -= 1;
	}

	return temp;
}

Node * firstCommonAncestor(Node * v1, Node * v2)
{
	if ( (v1 == nullptr) or (v2 == nullptr) )
		return nullptr;
	int depth1 = depth(v1);
	int depth2 = depth(v2);

	Node * temp1 = v1;
	Node * temp2 = v2;

	if (depth2 > depth1)
	{
		temp2 = kthAncestor(temp2, (depth2 - depth1));
	}

	else if (depth1 > depth2)
	{
		temp1 = kthAncestor(temp1, (depth1 - depth2));
	}

	// At this point, temp1 and temp2 are ancestors of v1 and v2 at the same depth.
	// Compare ancestors until we find a match.

	while (temp1 != temp2)
	{
		temp1 = temp1->m_parent;
		temp2 = temp2->m_parent;
	}

	return temp1;
}





int main()
{
    return 0;
}

