#include "GOAPAction.h"

GOAPAction_GoToObject::GOAPAction_GoToObject(Object* _object)
{
	object = _object;

	GOAPWorldState pre;

	pre.value = std::pair<int, bool>(object->roomType, true);

	preconditions = pre;

	GOAPWorldState eff;

	eff.value = std::pair<int, bool>(object->index, true);

	effects = eff;
}

void GOAPAction_GoToObject::GetCost(Agent* agent)
{
}

void GOAPAction_GoToObject::GetPath()
{
}
