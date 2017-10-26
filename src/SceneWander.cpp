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

	float angle = agents[0]->getOrientation();

	steering_force = agents[0]->Behavior()->Wander(agents[0], angle, &agents[0]->wanderAngle, wanderMaxChange,
		wanderCircleOffset, wanderCircleRadius, dtime);
	agents[0]->update(steering_force, dtime, event);
}

void SceneWander::draw()
{
	agents[0]->draw();
	if (agents[0]->getDrawSprite() == false) {
		agents[0]->steeringForceArrow->Draw(agents[0]->getPosition(), agents[0]->getPosition() + steering_force);
		agents[0]->velocityArrow->Draw(agents[0]->getPosition(), (agents[0]->getPosition() + agents[0]->getVelocity()));
		draw_circle(TheApp::Instance()->getRenderer(), (int)agents[0]->getWanderTarget().x, (int)agents[0]->getWanderTarget().y, 15, 0, 0, 255, 255);
		Vector2D offsetPosition = agents[0]->getPosition() + agents[0]->getVelocity().Normalize() * wanderCircleOffset;
		draw_circle(TheApp::Instance()->getRenderer(), offsetPosition.x, offsetPosition.y, wanderCircleRadius, 0, 0, 255, 255);
	}

}

const char* SceneWander::getTitle()
{
	return "SDL Steering Behaviors :: Wander Demo";
}