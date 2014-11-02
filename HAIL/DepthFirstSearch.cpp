#include "DepthFirstSearch.h"
#include "Node.h"

DepthFirstSearch::DepthFirstSearch(Graph& graph)
	: GraphSearch(graph)
{

}

Node* DepthFirstSearch::GetNextNode()
{
	Node* node = mOpenList.front();
	mOpenList.pop_front();
	
	return node;
}

void DepthFirstSearch::ExpandNode(Node* node, Node* neighbor)
{
	if(!neighbor->open && !neighbor->closed)
	{
		neighbor->parent = node;
		Push(neighbor);
		neighbor->open = true;
	}
}

void DepthFirstSearch::Push(Node* expanded)
{
	mOpenList.push_front(expanded);
}