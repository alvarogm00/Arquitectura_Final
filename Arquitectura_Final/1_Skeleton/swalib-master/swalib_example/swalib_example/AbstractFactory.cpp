#include "AbstractFactory.h"
#include "WeaponComponent.h"
#include "MovementComponent.h"
#include "CircleCollisionComponent.h"
#include "RenderComponent.h"

void AbstractFactory::CreateBalls()
{
	for (size_t i = 0; i < numBalls; i++)
	{
		Entity* newEntity = new Entity(starterType);
		MovementComponent* movComponent = new MovementComponent(vec2(0, 0), vec2(0, 0));
		CollisionComponent* colComponent = new CircleCollisionComponent(0.f);
		RenderComponent* rendComponent = new RenderComponent();
		CSprite* spriteComponent = new CSprite(vec2(0, 0), vec2(0, 0), 0);

		if (starterType == Entity::BIG_BALL)
		{
			movComponent->SetVelocity(vec2(m_bigVel, -m_bigVel));
			static_cast<CircleCollisionComponent*>(colComponent)->SetRadius(16.f);
			rendComponent->SetGfx(*m_texbigball);
			rendComponent->SetSize(vec2(16.0f * 2.0f, 16.0f * 2.0f));
			spriteComponent->SetGfx(m_texbigball);
		}
		else if (starterType == Entity::MEDIUM_BALL)
		{
			movComponent->SetVelocity(vec2(m_medVel, -m_medVel));
			static_cast<CircleCollisionComponent*>(colComponent)->SetRadius(16.f);
			rendComponent->SetGfx(*m_texmediumball);
			rendComponent->SetSize(vec2(16.0f * 2.0f, 16.0f * 2.0f));

		}
		else if (starterType == Entity::SMALL_BALL)
		{
			movComponent->SetVelocity(vec2(m_smallVel, -m_smallVel));
			static_cast<CircleCollisionComponent*>(colComponent)->SetRadius(16.f);
			rendComponent->SetGfx(*m_texsmallball);
			rendComponent->SetSize(vec2(16.0f * 2.0f, 16.0f * 2.0f));
		}

		newEntity->AddComponent(movComponent);
		newEntity->AddComponent(colComponent);
		newEntity->AddComponent(rendComponent);
		
		//m_entities.push_back(newEntity);
	}

	for (size_t i = 0; i < numBalls * 2; i++)
	{
		Entity* newEntity = new Entity();
		MovementComponent* movComponent = new MovementComponent(vec2(0, 0), vec2(0, 0));
		CollisionComponent* colComponent = new CircleCollisionComponent(0.f);
		RenderComponent* rendComponent = new RenderComponent();

		if (starterType == Entity::BIG_BALL)
		{
			newEntity->SetType(Entity::MEDIUM_BALL);
			movComponent->SetVelocity(vec2(m_medVel, -m_medVel));
			static_cast<CircleCollisionComponent*>(colComponent)->SetRadius(16.f);
			rendComponent->SetGfx(*m_texmediumball);
			rendComponent->SetSize(vec2(16.0f * 2.0f, 16.0f * 2.0f));
		}
		else if (starterType == Entity::MEDIUM_BALL)
		{
			newEntity->SetType(Entity::SMALL_BALL);
			movComponent->SetVelocity(vec2(m_smallVel, -m_smallVel));
			static_cast<CircleCollisionComponent*>(colComponent)->SetRadius(16.f);
			rendComponent->SetGfx(*m_texsmallball);
			rendComponent->SetSize(vec2(16.0f * 2.0f, 16.0f * 2.0f));
		}

		newEntity->AddComponent(movComponent);
		newEntity->AddComponent(colComponent);
		newEntity->AddComponent(rendComponent);
		newEntity->SetIsActive(false);
	}

	for (size_t i = 0; i < numBalls * 4; i++)
	{
		Entity* newEntity = new Entity(Entity::SMALL_BALL);
		MovementComponent* movComponent = new MovementComponent(vec2(0, 0), vec2(m_smallVel, -m_smallVel));
		CollisionComponent* colComponent = new CircleCollisionComponent(16.f);
		RenderComponent* rendComponent = new RenderComponent(*m_texsmallball, vec2(16.0f * 2.0f, 16.0f * 2.0f), nullptr);

		newEntity->AddComponent(movComponent);
		newEntity->AddComponent(colComponent);
		newEntity->AddComponent(rendComponent);
		newEntity->SetIsActive(false);
	}
}

void AbstractFactory::CreatePlayer()
{
    Entity* player = new Entity(Entity::PLAYER);
    WeaponComponent* weapon = new WeaponComponent();

    player->AddComponent(weapon);
}

int AbstractFactory::GetNumBalls()
{
    return numBalls;
}
