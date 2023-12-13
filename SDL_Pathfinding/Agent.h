#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Path.h"
#include "Vector2D.h"

#include "utils.h"
#include "Scene.h"
#include "Defines.h"

#include "BFS_Alg.h"
#include "Djikstra_Alg.h"
#include "Greedy_Alg.h"
#include "AStar_Alg.h"

class Agent
{
public:
	class Graph;

	class Decision_Algorithm
	{
	public:
		virtual void Update(Agent* agent, float dtime) {};
	};

	class SteeringBehavior
	{
	public:
		SteeringBehavior() {};
		virtual ~SteeringBehavior() {};
		virtual void applySteeringForce(Agent *agent,  float dtime) {};
	};

private:
	SteeringBehavior *steering_behaviour;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;

	Nav_Algorithm* nav_Algorithm;

	Scene* currentScene;
	Decision_Algorithm* brain;

	bool hasGun;

	Path path;
	int currentTargetIndex;

	float mass;
	float orientation;
	float max_force;
	float max_velocity;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;

public:
	Agent();
	~Agent();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	Scene* getScene();
	void setScene(Scene* scene);
	void setDecisionAlgorithm(Decision_Algorithm* decision_Algorithm);
	void setNavigationAlgorithm(Nav_Algorithm* nav_Algorithm);
	Nav_Algorithm* getNavigationAlgorithm();
	void setBehavior(SteeringBehavior *behavior);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void addPathPoint(Vector2D point);
	void setCurrentTargetIndex(int idx);
	void setPathCircleColor(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a);
	int getCurrentTargetIndex();
	int getPathSize();
	Vector2D getPathPoint(int idx);
	void clearPath();
	void update(float dtime, SDL_Event *event);
	void draw();
	bool loadSpriteTexture(char* filename, int num_frames=1);
	bool getHasGun();
	void setHasGun(bool newHasGun);
};
