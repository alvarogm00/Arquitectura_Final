#include "Lvl1Factory.h"
#include "MovementComponent.h"
#include "CircleCollisionComponent.h"
#include "RenderComponent.h"

void Lvl1Factory::CreateBalls()
{
	for (size_t i = 0; i < numBalls; i++)
	{
		Entity* newEntity = new Entity(starterType);
		MovementComponent* movComponent = new MovementComponent(vec2(0, 0), vec2(0, 0));
		if(starterType == Entity::BIG_BALL)
			movComponent = new MovementComponent(_pos, m_bigVel);
		else if(starterType == Entity::MEDIUM_BALL)
			movComponent = new MovementComponent(_pos, m_medVel);
		else if(starterType == Entity::SMALL_BALL)
			movComponent = new MovementComponent(_pos, m_smallVel);

		CollisionComponent* colComponent = new CircleCollisionComponent(16.f);
		RenderComponent* rendComponent = new RenderComponent(*_texball, vec2(16.0f * 2.0f, 16.0f * 2.0f), nullptr);

		newEntity->AddComponent(movComponent);
		newEntity->AddComponent(colComponent);
		newEntity->AddComponent(rendComponent);

		//m_entities.push_back(newEntity);
	}
}

Lvl1Factory::Lvl1Factory(int _numBalls, Entity::EntityType _starterType)
{
	numBalls = _numBalls;
	starterType = _starterType;
}
