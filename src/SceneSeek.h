#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"
#include "AuxLib.h"

class SceneSeek :
	public Scene
{
public:
	SceneSeek();
	~SceneSeek();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
	Vector2D steering_force;
	
};

