#include "SceneFlocking.h"
#include <random>

using namespace std;

#define MAX_AGENTS 50
#define NEIGHBORHOOD_RAD 50
#define SEPARATION_FORCE 20
#define COHESION_FORCE 7
#define ALIGNMENT_FORCE 5
SceneFlocking::SceneFlocking()
{
	std::mt19937 randGen(26247845489576);
	std::uniform_real_distribution<double> dis(0, 1);

	Agent *agent;
	for (int i = 0; i < MAX_AGENTS; i++)
	{
		agent = new Agent;
		agent->setPosition(Vector2D(dis(randGen)*300, dis(randGen)*300));
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
		Vector2D steering_force = a->Behavior()->Seek(a, a->getTarget(), dtime);
		a->update(steering_force, dtime, event);

		steering_force = a->Behavior()->Flock(agents, a, NEIGHBORHOOD_RAD, SEPARATION_FORCE, COHESION_FORCE, ALIGNMENT_FORCE, dtime);
		a->update(steering_force, dtime, event);

		steering_force = a->Behavior()->PerimeterAvoidance(a, 768, 1280, 0, dtime);
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