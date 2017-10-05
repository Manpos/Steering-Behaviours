#include "SceneAvoidance.h"

using namespace std;

SceneAvoidance::SceneAvoidance() 
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640,360));
	agent->setTarget(Vector2D(640, 360));
	agent->setMass(0.035);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
}

SceneAvoidance::~SceneAvoidance() 
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneAvoidance::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[0]->setTarget(target);
		}
		break;
	default:
		break;
	}

	Vector2D steering_force = agents[0]->Behavior()->PerimeterAvoidance(agents[0], 768, 1280, 200, dtime);

	agents[0]->update(steering_force, dtime, event);
}

void SceneAvoidance::draw() {
	agents[0]->draw();
}

const char* SceneAvoidance::getTitle()
{
	return "SDL Steering Behaviors :: Avoidance Demo";
}