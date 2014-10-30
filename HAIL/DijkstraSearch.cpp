#include "DijkstraSearch.h"
#include "Node.h"

DijkstraSearch::DijkstraSearch(Graph& graph, const ICostFunctor& getG)
	: GraphSearch(graph)
	, GetG(getG)
{

}


Node* DijkstraSearch::GetNextNode()
{
	NodeList::iterator lowestIter;
	float lowestCost = FLT_MAX;

	for (NodeList::iterator iter = mOpenList.begin(); iter != mOpenList.end(); ++iter)
	{
		Node* node = *iter;
		if (node->g < lowestCost && node->walkable)
		{
			lowestIter = iter;
			lowestCost = node->g;
		}
	}
	
	Node* lowestNode = *lowestIter;
	mOpenList.erase(lowestIter);
	return lowestNode;
}

void DijkstraSearch::ExpandNode(Node* node, Node* neighbor)
{
	if(!neighbor->closed)
	{
		const float g = node->g + GetG(node, neighbor);
		if (!neighbor->open)
		{
			neighbor->g = g;
			neighbor->parent = node;
			Push(neighbor);
			neighbor->open = true;
		}
		else if (g < neighbor->g)
		{
			neighbor->g = g;
			neighbor->parent = node;
		}
	}
}


void DijkstraSearch::Push(Node* expanded)
{
	mOpenList.push_back(expanded);
}