#include "Graph.h"
	


Graph::Graph()
	: mNodes(nullptr)
	, mWidth(0)
	, mHeight(0)
{

}
	
Graph::~Graph()
{
	Destroy();
}

Graph::Graph(const Graph& rhs)
{
	for (unsigned int i = 0; i < Direction::Count; ++i)
	{
		mNodes->neighbors[i] = rhs.mNodes->neighbors[i];
	}
	mNodes->position = rhs.mNodes->position;
	mHeight = rhs.mHeight;
	mWidth = rhs.mWidth;
}
	
Graph& Graph::operator=(const Graph& rhs)
{
	for (unsigned int i = 0; i < Direction::Count; ++i)
	{
		mNodes->neighbors[i] = rhs.mNodes->neighbors[i];
	}
	mNodes->position = rhs.mNodes->position;
	mHeight = rhs.mHeight;
	mWidth = rhs.mWidth;

	return *this;
}

	
void Graph::Create(unsigned unsigned int width, unsigned int height)
{
	Destroy();

	// Allocate new nodes
	mNodes = new Node[width * height];
	mWidth = width;
	mHeight = height;

	// Connect node neighbors
	for (unsigned int y = 0; y < height; ++y)
	{
		for (unsigned int x = 0; x < width; ++x)
		{
			Node* node = GetNode(x,y);
			node->open = false;
			node->closed = false;
			node->neighbors[North]		= GetNode(x, y-1);
			node->neighbors[East]		= GetNode(x+1, y);
			node->neighbors[South]		= GetNode(x, y+1);
			node->neighbors[West]		= GetNode(x-1, y);
			node->neighbors[NorthEast]	= GetNode(x+1, y-1);
			node->neighbors[NorthWest]	= GetNode(x-1, y-1);
			node->neighbors[SouthEast]	= GetNode(x+1, y+1);
			node->neighbors[SouthWest]	= GetNode(x-1, y+1);		
		}
	}
}

void Graph::ResetNodes()
{
	const int numNodes = mWidth * mHeight;
	for (unsigned int i = 0; i < numNodes; ++i)
	{
		Node& node = mNodes[i];
		node.parent = nullptr;
		node.g = 0.0f;
		node.h = 0.0f;
		node.open = false;
		node.closed = false;
	}
}
	
void Graph::Destroy()
{
	delete[] mNodes;
	mNodes = nullptr;
	mWidth = 0;
	mHeight = 0;
}

Node* Graph::GetNode(unsigned int x, unsigned int y)
{
	Node* node = nullptr;
	if ( x < mWidth && y < mHeight)
	{
		const unsigned int index = y*mWidth + x;
		node =  &mNodes[index];
	}

	return node;
}