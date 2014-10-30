#include "AStarSearch.h"
#include "Node.h"

AStarSearch::AStarSearch(Graph& graph, const ICostFunctor& getG, const ICostFunctor& getH)
	: GraphSearch(graph)
	, GetG(getG)
	, GetH(getH)
{

}


Node* AStarSearch::GetNextNode()
{
	NodeList::iterator lowestIter;
	float lowestCost = FLT_MAX;

	for (NodeList::iterator iter = mOpenList.begin(); iter != mOpenList.end(); ++iter)
	{
		Node* node = *iter;
		float cost = node->g + node->h;
		if (cost < lowestCost && node->walkable)
		{
			lowestIter = iter;
			lowestCost = cost;
		}
	}
	
	Node* lowestNode = *lowestIter;
	mOpenList.erase(lowestIter);
	return lowestNode;
}

void AStarSearch::ExpandNode(Node* node, Node* neighbor)
{
	if(!neighbor->closed)
	{
		const float g = node->g + GetG(node, neighbor);
		const float h = GetH(node, neighbor);
		if (!neighbor->open)
		{
			neighbor->g = g;
			neighbor->h = h; 
			neighbor->parent = node;
			Push(neighbor);
			neighbor->open = true;
		}
		else if (g + h < neighbor->g + neighbor->h)
		{
			neighbor->g = g;
			neighbor->h = h;
			neighbor->parent = node;
		}
	}
}


void AStarSearch::Push(Node* expanded)
{
	mOpenList.push_back(expanded);
}