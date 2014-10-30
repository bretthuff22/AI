#ifndef INCLUDED_AI_ASTARSEARCH_H
#define INCLUDED_AI_ASTARSEARCH_H

#include "GraphSearch.h"

class AStarSearch : public GraphSearch
{
public:
	AStarSearch(Graph& graph, const ICostFunctor& getG, const ICostFunctor& getH);

private:
	
	Node* GetNextNode();
	virtual void ExpandNode(Node* node, Node* neighbor);
	virtual void Push(Node* expanded);

	const ICostFunctor& GetG;
	const ICostFunctor& GetH;
};

#endif