#include "stdafx.h"
#include <iostream>
#include <string>

/*
Check Subtree:  T1 and T2 are two very large binary trees, with T1 much bigger than T2.  Create an algorithm
to determine if T2 is a subtree of T1.

A tree T2 is a subtree of T1 if there exists a node n in T1 such that the subtree of n is identical to T2.
That is, if you cut off the tree at node n, the two trees would be identical.
*/


/*
Note, it wasn't made entirely clear if we care about the tree and subtree being identical as trees or as
binary trees.  What I mean is, are we looking at graph isomorphism, or ordered (left/right) graph isomorphism?
Let's assume ordered - i.e. we want our isomorphism to be a graph isomorphism and preserve inequalities
of key values.
*/


/*
My first thought was a brute-force solution.  First write a function areIdentical(Node * T1, Node * T2) 
which returns true if and only if the trees rooted at T1 and T2 are identical.  This runs in time 
O(the smaller tree's number of vertices), since once we've explored the smaller tree completely, if the
other tree still has vertices then we know they're not identical.

Then run this for all nodes of the large tree.  The result runs in O(V1 * V2), V1 and V2 being the number
of vertices in T1, T2, respectively.  

I was on the solution page reading about CTCI's solution to problem 4.9, and unfortunately (!!!) I glimpsed
at a very important part of the solution to this problem:  It can be attacked with some sort of traversal.
I would have liked to figure this out on my own, but oh well.  Now to think it through...
*/

/*
Aha, not bad at all.  In-Order traversal doesn't work because, for example, the in-order traversal of a 
binary search tree depends only on the keys and not at all on the structure of the tree.  

Pre-order traversal turns out to work, *as long as* we keep track of which nodes are leaves.  This is easy:
Use a character to denote null nodes and include it in the preorder traversal output.  I used "N".

Also note that (for example) a tree with nodes root = 2, left = 1  has preorder traversal  N12N, which is
the same as we would have gotten with a tree with root = 12 and nothing else.  So, also use a character to
delineate all nodes.  I used "V".

Going from tree to string takes time linear or quadratic in the size of the tree, depending on whether we
reserve enough space for the string beforehand.   (Or it's always linear??? I'm not sure how C++ implements
its strings.  If they auto resize with some fixed geometric factor like 1.5, then it's linear.)  We could
change how our trees are implemented to keep track of total size, if we wanted to be sure that this step
takes linear time.

Anyhow, checking whether one string contains another can take up to O(L1 * L2) where L1 and L2 are the lengths
of the strings.  However, this runtime is quite unlikely to actually be achieved, and simply won't be achieved
if, for example, our trees' nodes have distinct m_data.

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



std::string preOrderTraversal(Node * root)
{
	if (root == nullptr)
		return "N";		// N for nullptr

	std::string currentChar = "V";		// V for value
	currentChar.append(std::to_string(root->m_data));

	std::string leftString = preOrderTraversal(root->m_left);
	std::string rightString = preOrderTraversal(root->m_right);

	std::string answer = leftString;
	answer.append(rightString);
	answer.append(currentChar);
	return answer;
}


bool containsSubtree(Node * tree, Node * subtreeCandidate)
{
	std::string treeInOrder = preOrderTraversal(tree);
	std::string subtreeCandidateInOrder = preOrderTraversal(subtreeCandidate);

	return (treeInOrder.find(subtreeCandidateInOrder) != std::string::npos);

}





Node * createExample()
{
	// It would have been quicker to create a few tree creation tools first.  Oh well.

	Node * root = new Node(12);
	Node * left = new Node(7);
	Node * leftleft = new Node(2);
	Node * leftright = new Node(9);
	Node * right = new Node(25);
	Node * rightleft = new Node(17);
	Node * rightleftleft = new Node(15);
	Node * rightleftright = new Node(19);
	Node * rightleftrightleft = new Node(18);
	Node * rightright = new Node(40);

	root->m_left = left;
	root->m_right = right;
	left->m_left = leftleft;
	left->m_right = leftright;
	right->m_left = rightleft;
	right->m_right = rightright;
	rightleft->m_left = rightleftleft;
	rightleft->m_right = rightleftright;
	rightleftright->m_left = rightleftrightleft;

	left->m_parent = root;
	right->m_parent = root;
	leftleft->m_parent = left;
	leftright->m_parent = left;
	rightright->m_parent = right;
	rightleft->m_parent = right;
	rightleftleft->m_parent = rightleft;
	rightleftright->m_parent = rightleft;
	rightleftrightleft->m_parent = rightleftright;

	return root;
}





int main()
{
	Node * example = createExample();
	std::string exampleInOrder = preOrderTraversal(example);

	Node * subtree = example->m_right->m_left;
	std::string subtreeInOrder = preOrderTraversal(subtree);

	Node * notSubtree = new Node(999);
	Node * anotherNotSubtree = new Node(7);
	
	std::cout << exampleInOrder << "\n";
	std::cout << subtreeInOrder << "\n";

	std::cout << preOrderTraversal(anotherNotSubtree) << "\n";
	if (containsSubtree(example, subtree))
		std::cout << "First test passed.\n";

	if (!containsSubtree(example, notSubtree))			// The Node's value isn't even contained in 'example'
		std::cout << "Second test passed.\n";

	if (!containsSubtree(example, anotherNotSubtree))	// 'example' does contain a node with value 7.
		std::cout << "Third test passed.\n";
	
    return 0;
}

