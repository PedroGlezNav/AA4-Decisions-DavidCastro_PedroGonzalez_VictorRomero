#pragma once
#include "Agent.h"

class GOAPWorldState {
public:
	std::pair<int,bool> value;


	inline bool operator==(const GOAPWorldState& rhs) const
	{
		return (value.first == rhs.value.first && value.second == rhs.value.second);
	}
};

class GOAPAction {
public:
	GOAPWorldState preconditions;
	GOAPWorldState effects;
	int cost = 0;

	virtual void GetCost(Agent* agent) = 0;
};

class GOAPAction_GoToObject : public GOAPAction {
public:
	Object* object;

	GOAPAction_GoToObject(Object*);

	// Heredado v�a GOAPAction
	void GetCost(Agent* agent) override; //Llamar al agent a calcular path y pillar el coste (igual hay que cambiar cosas)
	void GetPath();

};

