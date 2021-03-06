#include "stdafx.h"
#include <iostream>

/*
Random Node:  You are implementing a binary search tree class from scratch, which, in addition to insert, 
find, and delete, has a method getRandomNode() which returns a random node from the tree.  All nodes should be 
equally likely to be chosen.  Design and implement an algorithm for getRandomNode, and explain how you would
implement the rest of the methods.
*/

/*
Well, "find" is trivial, and insert/delete reeeeeally depend on whether I want to keep the tree balanced.
Let's say we do --- then we've got plenty of options.  I can probably work out how AVL trees work without
much trouble, so that'd be my approach.

As for the getRandomNode function:  Have each node keep a count of how many nodes are in its left and right
subtrees.  Let's just say that the current node has 45 left children and 186 right children.  This means that 
the tree has a total of 45 + 186 + 1 = 232 nodes.  Roll a dice with 232 sides, and if the result is <=45, 
go left.  If it's between 46 and 231, go right.  If it's 232, select the current node.

This is one approach, and it has the advantage of being quite simple.  It's also easy to maintain each Node's
left/right children variables, as long as we make sure each AVL tree operation maintains them.

Finally, we can avoid rolling dice over and over and over by rolling our dice once, and keeping the result
in mind as we traverse the tree.  If we rolled something <= 45, then just step left and keep the number 45.
If we rolled something 46 <= r <= 231, then subtract 45 and use the resulting number in the right subtree.  Etc.
*/




int main()
{
	/* 
	This will be one of the few problems I don't write a solution for.  It's quite a bit to write an AVL tree
	just for this problem - I'll do it later if there's free time, as it's always good practice if there's 
	nothing better to be doing.

	On second thought, it may be worth it to write this out with a very very simple BST.  
	*/


    return 0;
}

