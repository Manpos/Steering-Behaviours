#include "SceneFlocking.h"

using namespace std;

SceneFlocking::SceneFlocking()
{
	Agent *agent;
	for (int i = 0; i < MAX_AGENTS; i++)
	{
		agent = new Agent;
		agent->setPosition(Vector2D(600, 50));
		agent->setTarget(Vector2D(900, 650));
		agent->loadSpriteTexture("../res/zombie1.png", 8);
		agents.push_back(agent);
	}
}

SceneFlocking::~SceneFlocking()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneFlocking::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));

			for each (Agent* a in agents)
			{
				a->setTarget(target);
			}
		}
		break;
	default:
		break;
	}

	for each (Agent* a in agents)
	{
		Vector2D steering_force = a->Behavior()->Flock(agents, a);
		a->update(steering_force, dtime, event);
	}
}

void SceneFlocking::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->draw();
	}
}

const char* SceneFlocking::getTitle()
{
	return "SDL Steering Behaviors :: Flocking Demo";
}