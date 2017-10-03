#include "SceneAvoidance.h"

using namespace std;

SceneAvoidance::SceneAvoidance() 
{
	Agent *agent = new Agent;

}

SceneAvoidance::~SceneAvoidance() 
{

}

void SceneAvoidance::update(float dtime, SDL_Event *event)
{

}

void SceneAvoidance::draw() {

}

const char* SceneAvoidance::getTitle()
{
	return "SDL Steering Behaviors :: Avoidance Demo";
}