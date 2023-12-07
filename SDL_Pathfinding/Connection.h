#pragma once
#include "Node.h"

class Connection
{
private:
	float cost;
	Node* fromNode;
	Node* toNode;

public:
	Connection(float _cost, Node* _fromNode, Node* _toNode) : cost(_cost), fromNode(_fromNode), toNode(_toNode) {}

	float GetCost() {
		return cost;
	}

	Node* GetFromNode() {
		return fromNode;
	}

	Node* GetToNode() {
		return toNode;
	}
};