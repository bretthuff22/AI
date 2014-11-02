#ifndef INCLUDED_AI_GRAPHSEARCH_H
#define INCLUDED_AI_GRAPHSEARCH_H

#include "Node.h"

class Graph;

struct ICostFunctor
{
	virtual float operator()(Node* a, Node* b) const = 0;
};

class GraphSearch
{
public:
	GraphSearch(Graph& graph);

	void Run(unsigned int startX, unsigned int startY, unsigned int endX, unsigned int endY);

	bool IsFound() { return mFound;}

	Node* GetPath();
	NodeList GetClosedList()	{ return mClosedList; }

private:
	virtual Node* GetNextNode() = 0;
	virtual void ExpandNode(Node* node, Node* neighbor) = 0;
	virtual void Push(Node* expanded) = 0;

protected:

	NodeList mOpenList;
	NodeList mClosedList;
	Node* mStartNode;
	Node* mEndNode;

	Graph& mGraph;

	bool mFound;
};

#endif //INCLUDED_AI_GRAPHSEARCH_H