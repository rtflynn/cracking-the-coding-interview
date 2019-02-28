// LinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "LinkedList.h"




int main()
{
	LinkedList<int> * myList = new LinkedList<int>();
	myList->appendToHead(30);
	myList->appendToHead(20);
	myList->appendToHead(10);
	myList->appendToTail(40);
	myList->deleteHead();
	myList->deleteHead();
	myList->deleteHead();
	myList->deleteHead();
	myList->deleteHead();
	myList->deleteHead();
	myList->appendToTail(50);

	Node<int> * temp = myList->getHead();
	while (temp != nullptr) {
		std::cout << temp->m_data << std::endl;
		temp = temp->m_next;
	}


	
	
	return 0;
}

