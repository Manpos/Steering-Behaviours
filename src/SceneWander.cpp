#include "SceneWander.h"
#include "AuxLib.h"

using namespace std;

SceneWander::SceneWander()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640,360));
	agent->setTarget(Vector2D(640, 360));
	agent->setMass(0.035);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	wanderMaxChange = 50;
	wanderCircleOffset = 70;
	wanderCircleRadius = 80;
	wanderAngle = 0.0f;
	wanderCircleCenter = {};
	wanderDisplacementVector = {};
}

SceneWander::~SceneWander()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneWander::update(float dtime, SDL_Event *event)
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
	Vector2D velocity = agents[0]->getVelocity();	 

	float angle = agents[0]->getOrientation();
	float angleToUpdate = (float)(atan2(velocity.y, velocity.x) * RAD2DEG);
	float angleDelta = angleToUpdate - angle;
	if (angleDelta > 180.0f) { agents[0]->setOrientation(angle + 360.f); }
	else if (angleDelta < -180.f) { agents[0]->setOrientation(angle - 360.f); }
	angle = AuxLib::lerp(angle, angleToUpdate, 0.1f);
	//agents[0]->setOrientation(angle);
	Vector2D steering_force = agents[0]->Behavior()->Wander(agents[0], angle, &agents[0]->wanderAngle, wanderMaxChange,
		wanderCircleOffset, wanderCircleRadius, dtime);
	agents[0]->update(steering_force, dtime, event);
}

void SceneWander::draw()
{
	agents[0]->draw();
}

const char* SceneWander::getTitle()
{
	return "SDL Steering Behaviors :: Wander Demo";
}