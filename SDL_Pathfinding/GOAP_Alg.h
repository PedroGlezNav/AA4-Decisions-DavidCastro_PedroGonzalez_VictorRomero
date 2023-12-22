#pragma once
#include "GOAPAction.h"

struct AstarNode {
public:
	float f = 0, g = 0, h = 0;

	GOAPWorldState parentWs;
	GOAPWorldState actualWs;

	GOAPAction* action;
};

class GOAP_Alg : public Agent::Decision_Algorithm
{
private:
	std::unordered_map<int, GOAPAction*> actions;
	std::vector<GOAPAction*> plan;
	int idx_currentAction = 0;

	std::vector<GOAPAction*> CalculatePath(GOAPWorldState, GOAPWorldState);
public:

	GOAP_Alg(std::vector<Object*> object);

	virtual void Update(Agent* agent, float dtime) override;
	void AStar(GOAPWorldState start, GOAPWorldState goal);
};