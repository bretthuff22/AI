#ifndef INCLUDED_AI_DEPTHFIRSTSEARCH_H
#define INCLUDED_AI_DEPTHFIRSTSEARCH_H

#include "GraphSearch.h"

class DepthFirstSearch : public GraphSearch
{
public:
	DepthFirstSearch(Graph& graph);

private:
	Node* GetNextNode();
	virtual void ExpandNode(Node* node, Node* neighbor);
	virtual void Push(Node* expanded);
};

#endif