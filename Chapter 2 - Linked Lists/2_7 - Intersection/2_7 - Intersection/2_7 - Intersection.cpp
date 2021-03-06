#include "stdafx.h"
#include <iostream>
#include <list>
#include <unordered_set>


// This question is very difficult to parse only because it's very unclear which linked list structure we're working with.
// I mean... if it's a std::list, then are we even able to construct two std::lists which intersect?
// If it's some custom linked list class, then if two lists ever intersect, then they actually share all nodes after the
// intersection as well, no?  So isn't it as simple as comparing the very last node in both lists?  

// I really don't want to come up with a custom linked list class which allows for intersections just for the sake of solving
// this problem, because this problem is not AT ALL difficult.  THe pseudocode is as follows:

// Traverse both lists to their end elements, and obtain the length of both lists. 
// If the last elements are not equal, return nullptr (or a trivial node class if we're returning a node instead of a pointer to a node...)
// If the last elements are equal, start over from the beginning of both lists.  Traverse the longer of the two until the number 
// of nodes not traversed is the same as the length of the other list.  Now traverse both at the same time until we find a node in common.



int main()
{
    return 0;
}

