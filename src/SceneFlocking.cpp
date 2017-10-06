#include "SceneFlocking.h"
#include <random>

using namespace std;

#define MAX_AGENTS 100
#define NEIGHBORHOOD_RAD 50
#define SEPARATION_FORCE 20
#define COHESION_FORCE 7
#define ALIGNMENT_FORCE 5
SceneFlocking::SceneFlocking()
{
	std::mt19937 randGen(26247845489576);
	std::uniform_real_distribution<double> dis(0, 1);

	srcRect = new SDL_Rect;
	bgRect = new SDL_Rect;
	loadImage("../res/bg.jpg");

	bgRect->x = 0;
	bgRect->y = 0;
	bgRect->w = SDL_SimpleApp::Instance()->getWinSize().x;
	bgRect->h = SDL_SimpleApp::Instance()->getWinSize().y;

	Agent *agent;
	for (int i = 0; i < MAX_AGENTS; i++)
	{
		agent = new Agent;
		agent->setPosition(Vector2D(dis(randGen)*300, dis(randGen)*300));
		agent->setTarget(Vector2D(900, 650));
		agent->loadSpriteTexture("../res/firefly.png");
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
		steering_force = a->Behavior()->Seek(a, a->getTarget(), dtime);
		a->update(steering_force, dtime, event);

		steering_force = a->Behavior()->Flock(agents, a, NEIGHBORHOOD_RAD, SEPARATION_FORCE, COHESION_FORCE, ALIGNMENT_FORCE, dtime);
		a->update(steering_force, dtime, event);

		steering_force = a->Behavior()->PerimeterAvoidance(a, 768, 1280, 0, dtime);
		a->update(steering_force, dtime, event);
	}
}

void SceneFlocking::draw()
{


	SDL_RenderCopy(SDL_SimpleApp::Instance()->getRenderer(), bgTex, srcRect, bgRect);
	
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->draw();
	}

	if (agents[0]->getDrawSprite() == false) 
	{
		for (int i = 0; i < MAX_AGENTS; i++)
		{
			agents[i]->steeringForceArrow->Draw(agents[i]->getPosition(), agents[i]->getPosition() + steering_force);
			agents[i]->velocityArrow->Draw(agents[i]->getPosition(), (agents[i]->getPosition() + agents[i]->getVelocity()));
		}
	}
}

bool SceneFlocking::loadImage(char *path) {

	SDL_Surface *image = IMG_Load(path);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}

	bgTex = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	srcRect->x = 0;
	srcRect->y = 0;
	srcRect->w = image->w;
	srcRect->h = image->h;

	if (image) SDL_FreeSurface(image);

	return true;
}

const char* SceneFlocking::getTitle()
{
	return "SDL Steering Behaviors :: Flocking Demo";
}