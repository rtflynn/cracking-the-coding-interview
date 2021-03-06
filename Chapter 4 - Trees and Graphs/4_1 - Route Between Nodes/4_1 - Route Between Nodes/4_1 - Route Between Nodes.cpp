#include "stdafx.h"
#include <iostream>
#include "LinkedList.h"
#include <unordered_set>

// Given a directed graph, design an algorithm to find out whether there is a route between two nodes.


/*
Note on solution:  Man, what a mess this is.  To keep this from becoming a large project, I've implemented (barely)
some of the required data structures, with very unsatisfactory (i) implementations, and (ii) interfaces.
There's also the code-gore in the BFS algorithm where we track some vertices by pointer and others by ID.

For future problems either implement these objects much better, or use an external library.
*/




class Vertex
{
public:
	LinkedList<Vertex*> m_neighbors;
	int m_ID;
	Vertex(int ID = 0) : m_ID(ID) {}

	void addNeighbor(Vertex * v) { m_neighbors.pushTail(v); }



	void saySomething()
	{
		Node<Vertex*> * current = m_neighbors.getHead();
		while (current != nullptr)
		{
			int currentID = current->m_data->m_ID;
			std::cout << "There is an edge between vertex " << m_ID << " and vertex " << currentID << ".\n";
			current = current->m_next;
		}
	}
};


class Graph
{
public:
	LinkedList<Vertex*> m_verts;
	Graph() {}

public:
	void addVertex(int ID = 0)
	{
		Vertex * v = new Vertex(ID); 
		m_verts.pushTail(v);
	}

	void addEdge(int id1, int id2)	// Very flimsy stuff!  Needs serious rethinking.
	{
		Vertex * v1 = m_verts.getItem(id1);
		Vertex * v2 = m_verts.getItem(id2);
		v1->addNeighbor(v2);

		std::cout << "Adding an edge from vertex " << id1 << " to vertex " << id2 << ".\n";
	}

	void saySomething()
	{
		Node<Vertex*> *current = m_verts.getHead();
		while (current != nullptr)
		{
			current->m_data->saySomething();
			current = current->m_next;
		}
	}
};


class VertexQueue
{
private:
	LinkedList<Vertex*> m_list;


public:
	VertexQueue() {}

	void push(Vertex* v) { m_list.pushTail(v); }	// New vertices to the back of the line
	Vertex* pop()									// And we pop from the front of the line
	{
		if (m_list.getHead() == nullptr)
			return nullptr;
		Vertex * answer = m_list.getHead()->m_data; 
		m_list.deleteHead();
		return answer;
	}

	bool isEmpty() { return m_list.getHead() == nullptr; }
};


bool pathBetweenVerts(Graph ourGraph, int id1, int id2)
{
	VertexQueue vertsToVisit;
	std::unordered_set<int> visitedVertexIDs;	// This code is all terrible!

	vertsToVisit.push(ourGraph.m_verts.getItem(id1));
	visitedVertexIDs.insert(id1);

	while (!vertsToVisit.isEmpty())				// Visit each vertex in our queue
	{ 
		Vertex* currentVertex = vertsToVisit.pop();
//		std::cout << "Current Vertex is " << currentVertex->m_ID << ".\n";

		Node<Vertex*> * m_neighbor = currentVertex->m_neighbors.getHead();
		while (m_neighbor != nullptr)			// Add new adjacent vertices to our queue
		{
//			std::cout << "Considering the neighbor " << m_neighbor->m_data->m_ID << ".\n";
			if (visitedVertexIDs.count(m_neighbor->m_data->m_ID) == 0)
			{
//				std::cout << "Pushing vertex " << m_neighbor->m_data->m_ID << " into our queue.\n";
				vertsToVisit.push(m_neighbor->m_data);
				visitedVertexIDs.insert(m_neighbor->m_data->m_ID);
			}

//			else
//				std::cout << "The vertex " << m_neighbor->m_data->m_ID << " appears "
//				<< visitedVertexIDs.count(m_neighbor->m_data->m_ID) << " times in our visited set.\n";

			m_neighbor = m_neighbor->m_next;
		}	
	}

	return (visitedVertexIDs.count(id2));

}







int main()
{
	Graph ourGraph = Graph();
	for (int i = 0; i < 5; i++)
		ourGraph.addVertex(i);
	ourGraph.addEdge(0, 1);
	ourGraph.addEdge(0, 2);
	ourGraph.addEdge(0, 4);
	ourGraph.addEdge(1, 3);
	ourGraph.addEdge(2, 3);
	ourGraph.addEdge(4, 3);
	///// Easy to draw and find all paths


	ourGraph.saySomething();


	
	for (int start = 0; start < 5; start++)
		for (int end = 0; end < 5; end++)		
			if (start != end)
			{
				std::cout << "Is there a path from " << start << " to " << end << "?   "
					<< (pathBetweenVerts(ourGraph, start, end) ? "Yes" : "No") << "\n";
			}
		
	return 0;
}