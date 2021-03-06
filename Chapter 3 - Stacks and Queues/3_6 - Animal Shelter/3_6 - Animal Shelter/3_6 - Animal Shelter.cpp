#include "stdafx.h"
#include <iostream>
#include <string>

// An animal shelter, which holds only cats and dogs, operates on a strictly "first in, first out" basis.
// People must adopt either the "oldest" (based on arrival time) of all animals at the shelter, or they can
// select whether they would prefer a dog or cat (and will receive the oldest animal of that type). 
// They cannot select which specific animal they would like.  Create the data structures to maintain this 
// system and implement operations such as enqueue, dequeueAny, dequeueDog, dequeueCat.
// We may use the built-in LinkedList data structure.



// I've had some complicated ideas here, including a Queue sort of structure made out of Nodes which have
// pointers not only to the previous and next nodes, but also to the previous and next Cat nodes and to the
// previous and next Dog nodes.  The one here (I think) is simpler and has the benefit that all the requested
// operations run in O(1) time.

// Finally, just to keep things readable, I've made lots of member variables public to avoid needing getters and setters.



class Counter
{
public:
	static Counter & getInstance()
	{
		static Counter ourInstance;
		return ourInstance;
	}
	Counter(const Counter &) = delete;
	void operator=(const Counter &) = delete;
	void increment() { ++count; }
	int getCount() { return count; }

private:
	Counter() {}
	int count = 0;

	/* To use:

	Counter * myCounter;   
	myCounter->getInstance.getCount();		// returns the current count
	myCounter->getInstance.increment();		// increments the current count
	Counter * anotherCounter;				// Actually it's not another counter. It shares its value with myCounter
											// because we've created this class with the singleton pattern.
	*/
};


class Cat
{
public:
	std::string m_name;
	int m_lives = 9;
public:
	Cat(std::string name = "Catty") : m_name(name) {}
};

class Dog
{
public:
	std::string m_name;
	int m_dogYears = 7;
public:
	Dog(std::string name = "Doggo") : m_name(name) {}

};



template<class T>
class Node 
{
public:
	Node * m_prev = nullptr;
	Node * m_next = nullptr;
	int m_placeInLine;
	T m_data;

public:
	Node(T data) : m_data(data)
	{
		Counter * ourCounter;
		m_placeInLine = ourCounter->getInstance().getCount();
		ourCounter->getInstance().increment();
	}	
};

template<class T>
class AnimalQueue
{
public:
	Node<T> * m_first = nullptr;
	Node<T> * m_last = nullptr;

public:
	AnimalQueue() {}

	bool isEmpty() { return (m_first == nullptr); }
	void push(T someData)
	{
		Node<T> * newNode = new Node<T>(someData);

		if (m_first == nullptr)
		{			
			m_first = newNode;
			m_last = newNode;
			std::cout << "Pushing first item with ID number " << m_last->m_placeInLine << "\n";
			return;
		}

		newNode->m_prev = m_last;
		m_last->m_next = newNode;
		m_last = newNode;

		std::cout << "Pushing item which has ID number " << m_last->m_placeInLine << "\n";
	}

	T popFront()
	{
		if (m_first == nullptr)
			throw "Queue is empty, so can't pop!\n";
		if (m_first == m_last)
		{
			std::cout << "popping first item, which has ID number "<< m_first->m_placeInLine <<"\n";
			T answer = m_first->m_data;
			delete m_first;
			m_first = nullptr;
			m_last = nullptr;
			return answer;
		}

		Node<T> * temp = m_first;
		std::cout << "Popping item with ID number " << temp->m_placeInLine << "\n";
		T answer = temp->m_data;
		m_first = m_first->m_next;
		m_first->m_prev = nullptr;
		delete temp;
		
		return answer;
	}

	T peekFront()
	{
		if (m_first == nullptr)
			throw "Queue is empty, so can't peek!\n";
		return m_first->m_data;
	}
};


class CatDogQueue
{
private:
	AnimalQueue<Cat> m_catQueue;
	AnimalQueue<Dog> m_dogQueue;

public:
	CatDogQueue() {}

	void enqueueCat(Cat someCat)
	{
		m_catQueue.push(someCat);
	}

	void enqueueDog(Dog someDog)
	{
		m_dogQueue.push(someDog);
	}

	Cat dequeueCat()
	{
		if (m_catQueue.isEmpty())
			throw "Can't dequeueCat --- no cats left!!!\n";
		return m_catQueue.popFront();
	}

	Dog dequeueDog()
	{
		if (m_dogQueue.isEmpty())
			throw "Can't dequeueDog --- no dogs left!!!\n";
		return m_dogQueue.popFront();
	}
	
	// I wanted to keep it relatively simple.  In reality we'd have some sort of Animal class which can be returned
	// by dequeueAny.  But in reality some other things would be different as well, so let's just leave it as is
	// for now.

	void dequeueAny()		
	{
		if (m_dogQueue.isEmpty())
		{
			Cat answer = m_catQueue.popFront();
			std::cout << "Congratulations on your new cat, " << answer.m_name << ".\n";
			// Really we'd just return this Animal.
			return;
		}

		if (m_catQueue.isEmpty())
		{
			Dog answer = m_dogQueue.popFront();
			std::cout << "Congratulations on your new dog, " << answer.m_name << ".\n";
			return;
		}

		int firstDogID = m_dogQueue.m_first->m_placeInLine;
		int firstCatID = m_catQueue.m_first->m_placeInLine;

		if (firstDogID < firstCatID)
		{			
			Dog answer = m_dogQueue.popFront();
			std::cout << "Congratulations on your new dog, " << answer.m_name << ".\n";
			return;			
		}
		else
		{
			Cat answer = m_catQueue.popFront();
			std::cout << "Congratulations on your new cat, " << answer.m_name << ".\n";
			// Really we'd just return this Animal.
			return;
		}
	}

};






int main()
{
	CatDogQueue myQueue = CatDogQueue();
	myQueue.enqueueCat(Cat("Mittens"));
	myQueue.enqueueDog(Dog("Wilbur"));
	myQueue.enqueueCat(Cat("Pickles"));
	myQueue.enqueueDog(Dog("Roofus"));
	myQueue.enqueueDog(Dog("Goldie"));
	myQueue.enqueueCat(Cat("Charlie"));

	Cat firstAdopted = myQueue.dequeueCat();
	std::cout << "Looks like " << firstAdopted.m_name << " got adopted!\n";
	myQueue.dequeueAny();












    return 0;
}

