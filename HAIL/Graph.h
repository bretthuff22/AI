#ifndef INCLUDED_AI_GRAPH_H
#define INCLUDED_AI_GRAPH_H

#include "Node.h"

class Graph
{
public:
	Graph();
	~Graph();
	Graph(const Graph& rhs);
	Graph& operator=(const Graph& rhs);

	void Create(unsigned int width, unsigned int height);
	void Destroy();

	void ResetNodes();

	Node* GetNode(unsigned int x, unsigned int y);
private:

	Node* mNodes;
	unsigned int mWidth;
	unsigned int mHeight;
};

#endif //INCLUDED_AI_GRAPH_H