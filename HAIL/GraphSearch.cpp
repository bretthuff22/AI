#include "GraphSearch.h"
#include "Graph.h"

GraphSearch::GraphSearch(Graph& graph)
	: mGraph(graph)
	, mFound(false)
{

}

void GraphSearch::Run(unsigned int startX, unsigned int startY, unsigned int endX, unsigned int endY)
{
	Node* startNode = mGraph.GetNode(startX, startY);
	Node* endNode = mGraph.GetNode(endX, endY);

	if (startNode == nullptr || endNode == nullptr)
	{
		return;
	}

	// Reset graph nodes
	mGraph.ResetNodes();

	// Add start node to the open list
	mOpenList.push_back(startNode);
	startNode->open = true;

	// Start searching
	bool done = false;
	while (!done && !mOpenList.empty())
	{
		Node* node = GetNextNode();
		if (node == endNode)
		{
			done = true;
			mFound = true;
		}
		else
		{
			for (unsigned int n = 0; n < Direction::Count; ++n)
			{
				Node* neighbor = node->neighbors[n];
				if (neighbor!= nullptr)
				{
					ExpandNode(node, neighbor);
				}
			}
		}

		mClosedList.push_back(node);
		node->closed = true;
	}

	bool boobs = true;
}

Node* GraphSearch::GetPath()
{
	Node* path = nullptr;
	if (mFound == true)
	{
		path =  mClosedList.back();
	}

	return path;
}

//Node* GraphSearch::GetNextNode()
//{
//
//}