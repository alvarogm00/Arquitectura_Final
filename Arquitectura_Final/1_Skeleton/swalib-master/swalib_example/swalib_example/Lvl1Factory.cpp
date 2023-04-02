#include "Lvl1Factory.h"
#include "MovementComponent.h"
#include "CircleCollisionComponent.h"
#include "RenderComponent.h"
#include "../../common/Renderer.h"
#include "../../common/GameLogic.h"

Lvl1Factory::Lvl1Factory(int _numBalls, float _bigVel, float _medVel, float _smallVel, Entity::EntityType _starterType, 
	GLuint& _texbigball, GLuint& _texmediumball, GLuint& _texsmallball, GLuint& _texPlayer, vec2 _playerSize)
{
	numBalls = _numBalls;
	m_bigVel = _bigVel;
	m_medVel = _medVel;
	m_smallVel = _smallVel;
	starterType = _starterType;
	m_texbigball = _texbigball;
	m_texmediumball = _texmediumball;
	m_texsmallball = _texsmallball;
	m_texPlayer = _texPlayer;
	m_playerSize = _playerSize;
}

void Lvl1Factory::CreateBalls()
{
	for (size_t i = 0; i < numBalls; i++)
	{
		Entity* newEntity = new Entity(starterType);
		MovementComponent* movComponent = new MovementComponent(vec2(0, 0), vec2(m_medVel, -m_medVel));
		CollisionComponent* colComponent = new CircleCollisionComponent(8.f);
		RenderComponent* rendComponent = new RenderComponent(m_texmediumball, vec2(8.0f * 2.0f, 8.0f * 2.0f));

		newEntity->SetType(Entity::MEDIUM_BALL);
		newEntity->AddComponent(movComponent);
		newEntity->AddComponent(colComponent);
		newEntity->AddComponent(rendComponent);

		CGameLogic::instance()->AddBall(newEntity);
		CRenderer::instance()->SetRenderComponent(rendComponent);
	}

	for (size_t i = 0; i < numBalls * 2; i++)
	{
		Entity* newEntity = new Entity();
		MovementComponent* movComponent = new MovementComponent(vec2(0, 0), vec2(m_smallVel, -m_smallVel));
		CollisionComponent* colComponent = new CircleCollisionComponent(4.f);
		RenderComponent* rendComponent = new RenderComponent(m_texsmallball, vec2(4.f * 2.0f, 4.f * 2.0f));

		newEntity->SetType(Entity::SMALL_BALL);
		newEntity->AddComponent(movComponent);
		newEntity->AddComponent(colComponent);
		newEntity->AddComponent(rendComponent);
		newEntity->SetIsActive(false);

		CGameLogic::instance()->AddBall(newEntity);
		CRenderer::instance()->SetRenderComponent(rendComponent);
	}
}
