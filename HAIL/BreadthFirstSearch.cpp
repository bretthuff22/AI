#include "BreadthFirstSearch.h"
#include "Node.h"

BreadthFirstSearch::BreadthFirstSearch(Graph& graph)
	: GraphSearch(graph)
{

}


Node* BreadthFirstSearch::GetNextNode()
{
	Node* node = mOpenList.front();
	mOpenList.pop_front();
	while (!node->walkable)
	{
		node = mOpenList.front();
		mOpenList.pop_front();
	}
	return node;
}

void BreadthFirstSearch::ExpandNode(Node* node, Node* neighbor)
{
	if(!neighbor->open && !neighbor->closed)
	{
		neighbor->parent = node;
		Push(neighbor);
		neighbor->open = true;
	}
}


void BreadthFirstSearch::Push(Node* expanded)
{
	mOpenList.push_back(expanded);
}