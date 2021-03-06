#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
#include <queue>


/*
Build Order: You are given a list of projects and a list of dependencies (which is a list of pairs of projects,
where the second project is dependent upon the first project).  All of a project's dependencies must be built
before the project is.  Find a build order that will allow the projects to be built.  If there is no valid
build order, return an error.

Example:
Input:   
		projects: a, b, c, d, e, f
		dependencies: (a, d), (f, b), (b, d), (f, a), (d, c)

Output:
		f, e, a, b, d, c
*/

/*
Ideas before getting started:  We can sort our dependency list according to its second coordinate, as well
as our project list, and through this quickly figure out the first project which has no prerequisite projects,
if any exist at all.  The sorting will take O(nlog(n)) time where n is the length of the longer of the two lists.

Then scan to find the first project which has no prerequisites.  Add this project to an output queue, and
delete it from the projects list.  Also delete all dependencies where this project is the first coordinate.
Continue in this manner until the projects list is empty, or we can't go further.

Let m, n be the lengths of the projects, dependencies lists respectively.
	nlog(n) + mlog(m) to sort both lists. 
	log(n) to find a dependency with a given second coordinate, or to conclude there isn't one (binary search)
		and this is done m times, for a total of O(mlog(n))
	Constant time to delete the project from the projects list.  Once for each project, so O(n).
	Potentially m time to delete all relevant dependencies, for a total of O(m*n).

	So, this thing runs quadratically.  We can definitely do better.
	For one thing, if we want O(m*n), we can do it much easier without all this sorting business.
	We could have probably kept this O(klog(k)), where k = max(m,n), if we'd been slightly smarter about
	deleting dependencies.  
*/

/*
Second idea:  Store Projects in some lookup-table according to the number of dependencies they appear in the
second coordinate of.  If a Project doesn't appearas the second coordinate of any Dependencies, then we can 
delete all Dependencies for which our Project is the first coordinate, and update all the corresponding Project 
lookup-table values.  This still takes a long time, so I'm not going to spell out the algorithm any more than this.
*/

/*
Final idea:  First, this problem is very naturally a graph problem.  Create a graph where the vertices are the
Projects and the directed edges are the Dependencies.  

Note that if this graph has a cycle, then there's no valid Project order.
Conversely, if the graph doesn't have a cycle, I want to say that there is a valid Project order.

To see this:  Let P be a path of maximum length in our graph (which we're assuming has no cycles).
Let v0 be the starting vertex of this path.  Then v0 can't have any incoming edges, since if it did, 
we could find a longer path P'.  Therefore we can peel off v0, and continue in this manner since removing
an edge from an acyclic graph leaves it acyclic.

Therefore the question is: Given a graph, find a cycle (to prove there's no valid Project order), 
or show that it has no cycle (in which case we still have to find a valid Project order).
*/

/*
Well, I like this last idea, but I'm having some trouble getting the run time down past klog(k).
I think I recall something like 'topological sort' (maybe it had a different name), where we basically
"complete our poset to a total ordering".  And I think I recall that this could be done quickly ---
it was (?) an artifact of breadth-first-search.   OKAY well there's enough question marks and 'maybe's here
that it should be worthwhile to review the topic.  Off we go.
*/

/*
Well, that's reassuring.  All the topological sort algorithms I've found do basically the first idea that 
came to mind.  

First:  Find all vertices with in-degree 0.  For now select one of them.
Next:   Delete this vertex and all outgoing edges from the graph.  
Finally:  Repeat until the graph is empty or we can't go any more.

To keep this efficient, we can maintain for each vertex its current in-degree.
When we delete an edge, decrease the in-degree of its terminus.
When the in-degree of a vertex falls to 0, add it to the queue of "in-degree 0" vertices.

Each vertex is visited as many times as edges incident to it, which leads to O(V+E) time complexity.
*/


class Vertex
{
public:		
	std::list<Vertex*> m_neighbors;
	int m_inDegree = 0;
	std::string m_name;

public:
	Vertex(std::string name) : m_name(name) {}
	
	void addNeighbor(Vertex *v)
	{
		m_neighbors.push_back(v);
		v->m_inDegree += 1;
	}

	void saySomething()
	{
		std::cout << "I'm a vertex with name " << m_name << " and inDegree " << m_inDegree << ".\n";
		std::cout << "My neighbors are: ";
		for (auto it = m_neighbors.begin(); it != m_neighbors.end(); it++)
			std::cout << (**it).m_name << " ";
		std::cout << std::endl;
	}
};


class Graph
{
public:
	std::list<Vertex*> m_vertices;

	Graph() {}

	void addVertex(Vertex * v) { m_vertices.push_back(v); }
	void saySomething()
	{
		for (auto it = m_vertices.begin(); it != m_vertices.end(); it++)
			(**it).saySomething();
	}
};

Graph exampleGraph()
{
	Graph ourGraph = Graph();
	Vertex * a = new Vertex("a");
	Vertex * b = new Vertex("b");
	Vertex * c = new Vertex("c");
	Vertex * d = new Vertex("d");
	Vertex * e = new Vertex("e");
	Vertex * f = new Vertex("f");

	ourGraph.addVertex(a);
	ourGraph.addVertex(b);
	ourGraph.addVertex(c);
	ourGraph.addVertex(d);
	ourGraph.addVertex(e);
	ourGraph.addVertex(f);

	a->addNeighbor(d);
	b->addNeighbor(d);
	d->addNeighbor(c);
	f->addNeighbor(a);
	f->addNeighbor(b);

	return ourGraph;
}


void printValidOrder(Graph ourGraph)
{
	std::queue<Vertex *> verticesWithInDegreeZero;

	for (auto it = ourGraph.m_vertices.begin(); it != ourGraph.m_vertices.end(); it++)
	{
		if ((**it).m_inDegree == 0)
		{
			verticesWithInDegreeZero.push(*it);
		//	ourGraph.m_vertices.erase(it);
		}
	}		

	while (!verticesWithInDegreeZero.empty())
	{		
		Vertex * current = verticesWithInDegreeZero.front();
		verticesWithInDegreeZero.pop();
		for (auto it = current->m_neighbors.begin(); it != current->m_neighbors.end(); it++)
		{
//			std::cout << "Removing the edge from " << current->m_name << " to "
//				<< (*it)->m_name << ".\n";
			(*it)->m_inDegree -= 1;
			if ((*it)->m_inDegree == 0)
				verticesWithInDegreeZero.push((*it));
		}

		std::cout << current->m_name << " ";
	}

	std::cout << std::endl;

	for (auto it = ourGraph.m_vertices.begin(); it != ourGraph.m_vertices.end(); it++)
	{
		if ((*it)->m_inDegree > 0)
			std::cout << "There's no valid Project ordering.\n";
	}

}



int main()
{
	Graph ourGraph = exampleGraph();
	//ourGraph.saySomething();			Looks like my classes are working so far.

	printValidOrder(ourGraph);






    return 0;
}

