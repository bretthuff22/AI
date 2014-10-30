#ifndef INCLUDED_AI_BREADTHFIRSTSEARCH_H
#define INCLUDED_AI_BREADTHFIRSTSEARCH_H

#include "GraphSearch.h"

class BreadthFirstSearch : public GraphSearch
{
public:
	BreadthFirstSearch(Graph& graph);

private:
	
	Node* GetNextNode();
	virtual void ExpandNode(Node* node, Node* neighbor);
	virtual void Push(Node* expanded);
};

#endif