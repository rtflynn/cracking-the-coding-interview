#include "stdafx.h"
#include <iostream>
#include <unordered_set>		// Requires user-defined hash for user-defined classes
#include <set>					// Only requires comparison operator.  Use this as a placeholder for simplicity
#include <string>

/*
Robot in a Grid:  Imagine a robot sitting on the upper left corner of a grid with r rows and c columns.  The robot can only
move in two directions, right and down, but certain cells are "off limits" such that the robot cannot step on them.  Design
an algorithm to find a path for the robot from the top left to the bottom right.
*/


/*
One idea:  Think of the grid as a graph whose vertices are the grid cells and whose directed edges connect a grid cell
to the cell to the right and the cell below.  Use a depth-first search; we will eventually reach the bottom right cell 
if it's possible to do so.  Use back-pointers to record the path taken to get there.

We can do without back-pointers if we want, by directly constructing an output string like 'RRRDDRDDRRRDR', R and D 
corresponding to Right and Down respectively, and recursively adding a letter to the end of the string when we initiate
a recursive call, and deleting the last letter of the string when backing out of a recursive call.  As long as we
reserve a string length of 'r + c', we should be able to do this for constant cost each time.

Also note, there may be shorter algorithms for this, but there are not (!) shorter paths.  Every path from top-left
to bottom-right has the same number of moves.


After trying something, I noticed a little optimization: We don't need two hash sets, one for forbiddenCells, and another
for visitedCells.  Rather, we can just have forbiddenCells, and after we've visited a cell, add it to forbiddenCells, because
we don't want to visit previously visited cells anyway.

One last note:  Ideally we'd use std::unordered_set, but to do that we'd need to write our own hash function.
Instead I'm using std::set because it only requires defining a comparison operator.  If we wanted to optimize this, 
we'd clearly figure out a good hash function to use, and use it.
*/



class Position
{
private:
	int x;
	int y;
public:
	Position(int Posx = 0, int Posy = 0) : x(Posx), y(Posy){}
	bool operator==(const Position &other)
	{
		return ((x == other.x) and (y == other.y));
	}
	bool operator<(const Position &other) const
	{
		if (x < other.x)
			return true;
		if (x == other.x)
			if (y < other.y)
				return true;
		return false;
	}
	Position right()
	{
		return Position(x + 1, y);
	}
	Position down()
	{
		return Position(x, y + 1);
	}
};


void setUpBoundary(int columns, int rows, std::set<Position> &forbiddenCells)
{
	for (int x = 0; x <= columns; x++)
		forbiddenCells.insert(Position(x, rows));
	for (int y = 0; y < rows; y++)
		forbiddenCells.insert(Position(columns, y));
}







bool findPath(Position current, Position end, std::string &pathSoFar, std::set<Position> &forbiddenCells)
{
	if (forbiddenCells.count(current))
	{
		if (pathSoFar.length() >= 1)
		{
			pathSoFar.pop_back();
			return false;
		}
		else
			return false;
	}
	if (current == end)	
		return true;	

	forbiddenCells.insert(current);
	if (findPath(current.right(), end, pathSoFar.append("R"), forbiddenCells))
		return true;

	if (findPath(current.down(), end, pathSoFar.append("D"), forbiddenCells))
		return true;

	return false;
}



int main()
{
	int rows = 4;
	int columns = 8;
	Position start = Position(0, 0);
	Position finish = Position(7, 3);
	std::string pathSoFar = "";

	std::set<Position> forbiddenCells;
	setUpBoundary(columns, rows, forbiddenCells);
	forbiddenCells.insert(Position(3, 0));
	forbiddenCells.insert(Position(7, 2));
	//forbiddenCells.insert(Position(6, 3));					// Uncomment this line to get a setup with no valid path


	if (findPath(start, finish, pathSoFar, forbiddenCells))
		std::cout << pathSoFar << std::endl;
	else
		std::cout << "No path exists.\n";

    return 0;
}

