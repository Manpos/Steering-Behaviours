#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class SceneFlocking : public Scene
{
public:
	SceneFlocking();
	~SceneFlocking();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
	Vector2D steering_force;
	SDL_Rect* bgRect;
	SDL_Texture* bgTex;
	SDL_Rect* srcRect;
	bool loadImage(char* path);
};

#pragma once
