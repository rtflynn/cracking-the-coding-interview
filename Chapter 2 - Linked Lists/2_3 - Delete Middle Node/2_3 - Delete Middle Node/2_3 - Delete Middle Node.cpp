#include "stdafx.h"
#include <iostream>
#include "linkedList.h"


///// WHOOPS!  I misread the problem --- we don't even have access to the head node.  
/*



void removeFromList(Node * headOfList, Node * nodeToRemove)
{
	Node * current = headOfList;
	while (current->next != nodeToRemove)
	{
		current = current->next;
	}

	if (current->next == nodeToRemove)
	{
		current->next = nodeToRemove->next;
		delete nodeToRemove;
	}


}







int main()
{
	Node * head = new Node(5);
	head->appendToTail(6);
	head->appendToTail(7);
	head->appendToTail(8);
	head->appendToTail(9);
	head->saySomething();

	Node * nodeToRemove = head->next->next;
	nodeToRemove->saySomething();


	removeFromList(head, nodeToRemove);
	head->saySomething();


	
	return 0;
}

*/


void removeNode(Node * nodeToRemove)
{
	Node * nextNode = nodeToRemove->next;
	nodeToRemove->m_data = nextNode->m_data;
	nodeToRemove->next = nextNode->next;
	delete nextNode;
}






int main()
{
	Node * head = new Node(5);
	head->appendToTail(6);
	head->appendToTail(7);
	head->appendToTail(8);
	head->appendToTail(9);

	Node * nodeToRemove = head->next->next;

	removeNode(nodeToRemove);
	head->saySomething();




	return 0;
}