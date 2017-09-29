#include "SteeringBehavior.h"
#include "AuxLib.h"


SteeringBehavior::SteeringBehavior()
{
}


SteeringBehavior::~SteeringBehavior()
{
}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Vector2D target, float dtime)
{
	Vector2D steering = target - agent->position;
	steering.Normalize();
	return steering * agent->max_velocity;
}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Agent *target, float dtime)
{
	return KinematicSeek(agent, target->position, dtime);
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Vector2D target, float dtime)
{
	Vector2D steering = agent->position - target;
	steering.Normalize();
	return steering * agent->max_velocity;
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Agent *target, float dtime)
{
	return KinematicFlee(agent, target->position, dtime);
}

/* Add here your own Steering Behavior functions definitions */

Vector2D SteeringBehavior::Seek(Agent *agent, Vector2D target, float dtime)
{
	Vector2D desiredVelocity = target - agent->getPosition();
	desiredVelocity.Normalize();
	desiredVelocity *= agent->getMaxVelocity();
	Vector2D steeringForce = desiredVelocity - agent->getVelocity();
	steeringForce /= agent->getMaxVelocity();
	steeringForce *= agent->getMaxForce();
	return steeringForce;
}

Vector2D SteeringBehavior::Seek(Agent *agent, Agent *target, float dtime)
{
	return Seek(agent, target->position, dtime);
}

Vector2D SteeringBehavior::Flee(Agent *agent, Vector2D target, float dtime)
{
	Vector2D desiredVelocity = agent->getPosition() - target;
	desiredVelocity.Normalize();
	desiredVelocity *= agent->getMaxVelocity();
	Vector2D steeringForce = desiredVelocity - agent->getVelocity();
	steeringForce /= agent->getMaxVelocity();
	steeringForce *= agent->getMaxForce();
	return steeringForce;
}

Vector2D SteeringBehavior::Flee(Agent *agent, Agent *target, float dtime)
{
	return Flee(agent, target->position, dtime);
}

Vector2D SteeringBehavior::Arrive(Agent *agent, Vector2D target, float slowRadius, float dtime) 
{
	float distanceToTarget = (target - agent->getPosition()).Length();

	Vector2D steeringForce;
	float factor = distanceToTarget / slowRadius;

	if (distanceToTarget > slowRadius) {
		return Seek(agent, target, dtime);
	}

	else if (factor == 0) {
		return steeringForce;
	}
	
	else {

		Vector2D desiredVelocity = target - agent->getPosition();
		desiredVelocity.Normalize();
		desiredVelocity *= agent->getMaxVelocity() * factor;

		steeringForce = desiredVelocity - agent->getVelocity();
		steeringForce /= agent->getMaxVelocity() * factor;
		steeringForce *= agent->getMaxForce();
		return steeringForce;
	}

}

Vector2D SteeringBehavior::Arrive(Agent *agent, Agent *target, float slowRadius, float dtime) 
{
	return Arrive(agent, target->getPosition(), slowRadius, dtime);
}

Vector2D SteeringBehavior::Pursue(Agent *agent, Agent *target, float dtime)
{
	float distanceToTarget = (target->getPosition() - agent->getPosition()).Length();
	float T = distanceToTarget / target->getVelocity().Length();
	Vector2D predictedTarget = target->getPosition() + target->getVelocity()*T;
	return Seek(agent, predictedTarget, dtime);
}

Vector2D SteeringBehavior::Evade(Agent *agent, Agent *target, float dtime)
{
	float distanceToTarget = (target->getPosition() - agent->getPosition()).Length();
	float T = distanceToTarget / target->getVelocity().Length();
	Vector2D predictedTarget = target->getPosition() + target->getVelocity()*T;
	return Flee(agent, predictedTarget, dtime);
}

Vector2D SteeringBehavior::Wander(Agent *agent, float angle, float *wanderAngle, int wanderMaxChange, int wanderCircleOffset, int wanderCircleRadius, float dtime) 
{
	*wanderAngle += AuxLib::RandomBinomial() * wanderMaxChange;
	float targetAngle = angle + *wanderAngle;
	Vector2D circleCenter = agent->getPosition() + agent->getVelocity().Normalize() * wanderCircleOffset;
	Vector2D targetPosition;
	targetPosition.x = circleCenter.x + wanderCircleRadius * cos(targetAngle);
	targetPosition.y = circleCenter.y + wanderCircleRadius * sin(targetAngle);
	wanderAngle = wanderAngle + rand() * wanderMaxChange;

	return Seek(agent, targetPosition, dtime);
}

Vector2D SteeringBehavior::Flock(std::vector<Agent*> agents, Agent* agent, float neighborhoodRadius, float separationForceWeight, float cohesionForceWeight, float alignmentForceWeight)
{
	int neighborCount = 0;

	//Separation
	Vector2D separationDirection;
	Vector2D separationVector = {};

	for each (Agent* a in agents)
	{
		if (Vector2D::Distance(a->position, agent->position) < neighborhoodRadius)
		{
			separationVector += (agent->position - a->position);
			neighborCount++;
		}
	}

	separationVector /= neighborCount;
	separationDirection = Vector2D::Normalize(separationVector);


	//Cohesion
	neighborCount = 0;
	Vector2D cohesionDirection;
	Vector2D averagePosition = {};

	for each (Agent* a in agents)
	{
		if (Vector2D::Distance(a->position, agent->position) < neighborhoodRadius)
		{
			averagePosition += a->position;
			neighborCount++;
		}
	}

	averagePosition /= neighborCount;
	averagePosition -= agent->position;
	cohesionDirection = Vector2D::Normalize(averagePosition);

	//Alignment
	neighborCount = 0;
	Vector2D alignmentDirection;
	Vector2D averageVelocity = {};

	for each (Agent* a in agents)
	{
		if (Vector2D::Distance(a->position, agent->position) < neighborhoodRadius)
		{
			averageVelocity += a->velocity;
			neighborCount++;
		}
	}

	averageVelocity /= neighborCount;
	alignmentDirection = Vector2D::Normalize(averageVelocity);
	
	
	return Vector2D((separationDirection * separationForceWeight) +
					(cohesionDirection * cohesionForceWeight) +
					(alignmentDirection * alignmentForceWeight));
}