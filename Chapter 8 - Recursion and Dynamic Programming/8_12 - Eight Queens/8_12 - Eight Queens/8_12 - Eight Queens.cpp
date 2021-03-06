#include "stdafx.h"
#include <iostream>
#include <string>

/*
Eight Queens:  Write an algorithm to print all ways of arranging eight queens on an 8x8 chess board so that none of them
share the same row, column, or diagonal.  In this case, "diagonal" means all diagonals, not just the two that bisect the
board.
*/

/*
I decided to do this one more generally because it has a nice setup for an object-oriented approach.  I want to generalize
to chessboards (8x8 for now) with various pieces, not just Queens.  So we have a base ChessPiece class which the other 
pieces derive from.  I wrote it all up and got it working for the Queen problem.  Then I wrote a Rook class, which took
honestly about 15 seconds, and after 15 more seconds had a working solution to the corresponding 'Rook' problem.

We'd have to change the logic a little to solve (say) the Bishop problem, because in our current approach we don't allow
two pieces in one column (which makes sense for Queens and Rooks).  This isn't tough to rectify - for example, we could
order the squares on our chessboard in any way we like, and instead of iterating over columns, we could just iterate
over individual squares.  

Easy things to add with the current class structure:  
	- Arbitrary length/width boards
	- Support for all chess pieces
	- Support for fictional chess pieces
	- Returning a number instead of printing out all the possibilities
	- Similar problems which allow multiple types of pieces on the same board

There's a cute way to do this last one (which is not a serious solution, but a little entertaining), which I've carried out
with the last two functions soo() and roo().
*/




class ChessPiece
{
public:
	int x;
	int y;
	std::string m_name;

	ChessPiece(int posx = 0, int posy = 0, std::string name = "") : x(posx), y(posy), m_name(name) {}
	void saySomething() 
	{
		std::cout << m_name << "(" << x << "," << y << ")  ";
	}

	virtual bool collidesWith(ChessPiece &other) 
	{	
		return true; 
	}
};


class Node
{
public:
	ChessPiece *m_ChessPiece;			// It's important that this is a pointer and not an object since we want to take
	Node * m_next = nullptr;			// advantage of polymorphism.
	Node * m_prev = nullptr;
	Node(ChessPiece *x) : m_ChessPiece(x) {}
};

class LinkedList
{
public:
	Node * m_head = nullptr;
	Node * m_tail = nullptr;
	LinkedList() {}
	void appendToTail(ChessPiece *x)
	{
		Node * newNode = new Node(x);

		if (m_head == nullptr)
		{			
			m_head = newNode;
			m_tail = newNode;
			return;
		}

		else
		{
			m_tail->m_next = newNode;
			newNode->m_prev = m_tail;
			m_tail = newNode;
		}
	}

	void popFromTail()
	{
		if (m_tail == nullptr)
			return;
		else if (m_head == m_tail)		// neither is nullptr.  Our list has one Node in it.
		{
			delete m_head;
			m_head = nullptr;
			m_tail = nullptr;			
		}
		else
		{
			Node * temp = m_tail;
			m_tail = m_tail->m_prev;
			m_tail->m_next = nullptr;
			delete temp;
		}
	}


	void saySomething()
	{
		Node * temp = m_head;
		while (temp != nullptr)
		{
			temp->m_ChessPiece->saySomething();
			temp = temp->m_next;
		}
		std::cout << std::endl;
	}
	
	bool canExtendWith(ChessPiece &other)
	{
		Node * temp = m_head;
		while (temp != nullptr)
		{
			// Need to check both ways - the new piece may be able to eat a previous or vice versa.
			if (temp->m_ChessPiece->collidesWith(other))
				return false;
			if (other.collidesWith(*(temp->m_ChessPiece)))
				return false;
			temp = temp->m_next;
		}
		return true;
	}
};

class Rook : public ChessPiece
{
public:
	Rook(int posx = 0, int posy = 0) : ChessPiece(posx, posy, "Rook") {}

	bool collidesWith(ChessPiece &other) override
	{
		if ((x == other.x) or (y == other.y))
			return true;
		return false;
	}

};


class Queen : public ChessPiece
{
public:
	Queen(int posx = 0, int posy = 0) : ChessPiece(posx, posy, "Queen"){}	
	/*
	If we want to generalize the problem, we may want to put some bound-checking logic so that (x,y) is a valid board
	position.
	*/

	bool collidesWith(ChessPiece &other) override
	{
		if (x == other.x)			
			return true;
		if (y == other.y)
			return true;
		if ((x + y) == (other.x + other.y))
			return true;
		if ((x - y) == (other.x - other.y))
			return true;
	
		return false;
	}	
};

// If we want to allow for bishops and other pieces, replace the currentColumn variable with a currentSquare variable,
// and iterate through those.  It's easy to get a row and column out of an integer between 0 and 63 using long division.
void foo(LinkedList &currentPieces, int currentColumn)		
{
	if (currentColumn == 8)
	{
		currentPieces.saySomething();
		return;
	}

	for (int row = 0; row < 8; row++)
	{
		Queen * newPiece = new Queen(currentColumn, row);
		if (currentPieces.canExtendWith(*newPiece))
		{
			currentPieces.appendToTail(newPiece);
			foo(currentPieces, currentColumn + 1);
			currentPieces.popFromTail();
		}
	}
}

void goo(LinkedList &currentPieces, int currentColumn)
{
	if (currentColumn == 8)
	{
		currentPieces.saySomething();
		return;
	}

	for (int row = 0; row < 8; row++)
	{
		Rook * newPiece = new Rook(currentColumn, row);
		if (currentPieces.canExtendWith(*newPiece))
		{
			currentPieces.appendToTail(newPiece);
			goo(currentPieces, currentColumn + 1);
			currentPieces.popFromTail();
		}
	}
}


void roo(LinkedList &currentPieces, int currentColumn);

void soo(LinkedList &currentPieces, int currentColumn)
{
	if (currentColumn == 8)
	{
		currentPieces.saySomething();
		return;
	}

	for (int row = 0; row < 8; row++)
	{
		Queen * newPiece = new Queen(currentColumn, row);
		if (currentPieces.canExtendWith(*newPiece))
		{
			currentPieces.appendToTail(newPiece);
			roo(currentPieces, currentColumn + 1);
			currentPieces.popFromTail();
		}
	}
}

void roo(LinkedList &currentPieces, int currentColumn)
{
	if (currentColumn == 8)
	{
		currentPieces.saySomething();
		return;
	}

	for (int row = 0; row < 8; row++)
	{
		Rook * newPiece = new Rook(currentColumn, row);
		if (currentPieces.canExtendWith(*newPiece))
		{
			currentPieces.appendToTail(newPiece);
			soo(currentPieces, currentColumn + 1);
			currentPieces.popFromTail();
		}
	}
}



int main()
{
	LinkedList ourList = LinkedList();
	foo(ourList, 0);					// 8 Queens problem		
	
//	goo(ourList, 0);					// 8 Rooks problem.  There are 8! valid arrangements.
	
	soo(ourList, 0);					// Alternating Rooks and Queens

	roo(ourList, 0);					// Alternating Queens and Rooks


	return 0;
}

