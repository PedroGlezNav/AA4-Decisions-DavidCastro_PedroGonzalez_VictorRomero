#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Path.h"
#include "Vector2D.h"
#include "utils.h"
#include "Scene.h"
#include "Decision_Algorithm.h"


class Agent
{
public:
	class SteeringBehavior
	{
	public:
		SteeringBehavior() {};
		virtual ~SteeringBehavior() {};
		virtual void applySteeringForce(Agent *agent, float dtime) {};
	};
private:
	SteeringBehavior *steering_behaviour;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;

	Scene* currentScene;
	//Decision_Algorithm* brain;

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
	Decision_Algorithm* getDecisionAlgorithm();
	void setScene(Scene* scene);
	void setDecisionAlgorithm(Decision_Algorithm* decision_Algorithm);
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
};
