#pragma once
#include "GOAPAction.h"

class GOAP_Alg : public Agent::Decision_Algorithm
{
private:
	std::unordered_map<std::string, GOAPAction*> actions;
	std::vector<GOAPAction*> plan;
	int idx_currentAction = 0;
public:
	virtual void Update(Agent* agent, float dtime) override;
	void AStar(GOAPWorldState start, GOAPWorldState goal);
};