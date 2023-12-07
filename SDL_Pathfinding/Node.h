#pragma once
#include "Vector2D.h"
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#include "Defines.h"

class Node {
private:
	float heuristic;
	Vector2D position;

public:
	Node(float _heuristic, Vector2D _position) : heuristic(_heuristic), position(_position) {}

	~Node() {}

	void SetHeuristic(float _heuristic) {
		heuristic = _heuristic;
	}

	void SetPosition(Vector2D _position) {
		position = _position;
	}

	float GetHeuristic() {
		return heuristic;
	}

	Vector2D GetPosition() {
		return position;
	}
};