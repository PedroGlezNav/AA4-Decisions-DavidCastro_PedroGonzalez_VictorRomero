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

float GOAPAction_GoToObject::GetCost(Agent* agent)
{
	std::vector<Vector2D> nullVector;

	std::vector<Vector2D> pathWeDontCare = agent->getNavigationAlgorithm()->CalculatePathNodes(
											agent->getScene()->getMaze()->pix2cell(agent->getPosition()),
											object->position,
											agent->getScene()->getGraph(),
											nullVector);

	return agent->getNavigationAlgorithm()->GetCost();
}

std::vector<Vector2D> GOAPAction_GoToObject::GetPath(Agent* agent)
{
	return agent->getNavigationAlgorithm()->CalculatePathNodes(
		agent->getScene()->getMaze()->pix2cell(agent->getPosition()), 
		object->position, 
		agent->getScene()->getGraph(), 
		std::vector<Vector2D>());
}
