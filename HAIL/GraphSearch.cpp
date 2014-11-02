#include "GraphSearch.h"
#include "Graph.h"

GraphSearch::GraphSearch(Graph& graph)
	: mGraph(graph)
	, mFound(false)
	, mStartNode(nullptr)
	, mEndNode(nullptr)
{

}

void GraphSearch::Run(unsigned int startX, unsigned int startY, unsigned int endX, unsigned int endY)
{
	mStartNode = mGraph.GetNode(startX, startY);
	mEndNode = mGraph.GetNode(endX, endY);

	if (mStartNode == nullptr || mEndNode == nullptr)
	{
		return;
	}

	// Reset graph nodes
	mGraph.ResetNodes();

	// Add start node to the open list
	mOpenList.push_back(mStartNode);
	mStartNode->open = true;

	// Start searching
	bool done = false;
	while (!done && !mOpenList.empty())
	{
		Node* node = GetNextNode();

		if (node == mEndNode)
		{
			done = true;
			mFound = true;
		}
		else
		{
			for (unsigned int n = 0; n < Direction::Count; ++n)
			{
				Node* neighbor = node->neighbors[n];
				if (neighbor!= nullptr && neighbor->walkable)
				{
					ExpandNode(node, neighbor);
				}
			}
		}

		mClosedList.push_back(node);
		node->closed = true;
	}
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