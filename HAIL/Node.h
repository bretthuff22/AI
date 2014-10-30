#ifndef INCLUDED_AI_NODE_H
#define INCLUDED_AI_NODE_H

#include <SGE.h>
using namespace SGE;

#include<list>

enum Direction
{
	North,
	East,
	South,
	West,
	NorthEast,
	NorthWest,
	SouthEast,
	SouthWest,
	Count
};

struct Node
{
	Node* neighbors[Direction::Count];
	Node* parent;
	float g;
	float h;
	bool open;
	bool closed;
	bool walkable;

	SVector2 position;
};

typedef std::list<Node*> NodeList;

#endif //INCLUDED_AI_NODE_H