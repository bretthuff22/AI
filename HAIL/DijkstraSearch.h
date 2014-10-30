#ifndef INCLUDED_AI_DIJKSTRASEARCH_H
#define INCLUDED_AI_DIJKSTRASEARCH_H

#include "GraphSearch.h"

class DijkstraSearch : public GraphSearch
{
public:
	DijkstraSearch(Graph& graph, const ICostFunctor& getG);

private:
	
	Node* GetNextNode();
	virtual void ExpandNode(Node* node, Node* neighbor);
	virtual void Push(Node* expanded);

	const ICostFunctor& GetG;
};

#endif