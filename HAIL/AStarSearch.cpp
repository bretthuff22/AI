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
	NodeList::iterator lowestIter = mOpenList.begin();
	float lowestCost = FLT_MAX;

	for (NodeList::iterator iter = mOpenList.begin(); iter != mOpenList.end(); ++iter)
	{
		Node* node = *iter;

		float cost = node->g + node->h;
		if (cost < lowestCost)
		{
			lowestIter = iter;
			lowestCost = cost;
		}
	}
	
	Node* lowestNode = nullptr;
	if (*lowestIter != nullptr)
	{
		lowestNode = *lowestIter;
		mOpenList.erase(lowestIter);
	}
	
	return lowestNode;
}

void AStarSearch::ExpandNode(Node* node, Node* neighbor)
{
	if(!neighbor->closed)
	{
		const float g = node->g + GetG(node, neighbor);
		const float h = GetH(neighbor, mEndNode);
		if (!neighbor->open)
		{
			neighbor->g = g;
			neighbor->h = h; 
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


void AStarSearch::Push(Node* expanded)
{
	mOpenList.push_back(expanded);
}