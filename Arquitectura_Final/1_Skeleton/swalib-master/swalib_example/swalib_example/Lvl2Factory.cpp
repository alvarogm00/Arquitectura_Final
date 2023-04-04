#include "Lvl2Factory.h"
#include "MovementComponent.h"
#include "CircleCollisionComponent.h"
#include "RenderComponent.h"
#include "../../common/GameLogic.h"
#include "../../common/Renderer.h"

Lvl2Factory::Lvl2Factory(int _numBalls, float _bigVel, float _medVel, float _smallVel, Entity::EntityType _starterType,
	GLuint& _texbigball, GLuint& _texmediumball, GLuint& _texsmallball, GLuint& _texPlayer, vec2 _playerSize, GLuint& _texWeapon, vec2 _weaponVel)
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
	m_texWeapon = _texWeapon;
	m_weaponVel = _weaponVel;
}

void Lvl2Factory::CreateBalls()
{
	vec2 position(10.f, SCR_HEIGHT / 3);

	for (size_t i = 0; i < numBalls; i++)
	{
		position.x += 120.f;

		Entity* newEntity = new Entity(starterType);
		newEntity->SetSize(vec2(64.f, 64.f));
		MovementComponent* movComponent = new MovementComponent(vec2(0, 0), vec2(m_bigVel, -m_bigVel));
		CollisionComponent* colComponent = new CircleCollisionComponent(newEntity->GetSize()->x / 2);
		RenderComponent* rendComponent = new RenderComponent(m_texbigball, *newEntity->GetSize());

		movComponent->SetMaxHeight((SCR_HEIGHT / 3));
		newEntity->AddComponent(movComponent);
		newEntity->AddComponent(colComponent);
		newEntity->AddComponent(rendComponent);
		newEntity->SetPosition(position);
		newEntity->SetIsActive(true);

		CGameLogic::instance()->AddBall(newEntity);
		CRenderer::instance()->SetRenderComponent(rendComponent);
	}

	for (size_t i = 0; i < numBalls * 2; i++)
	{
		Entity* newEntity = new Entity();
		newEntity->SetSize(vec2(32.f, 32.f));
		MovementComponent* movComponent = new MovementComponent(vec2(0, 0), vec2(m_medVel, -m_medVel));
		CollisionComponent* colComponent = new CircleCollisionComponent(newEntity->GetSize()->x / 2);
		RenderComponent* rendComponent = new RenderComponent(m_texmediumball, *newEntity->GetSize());

		movComponent->SetMaxHeight(SCR_HEIGHT / 2);

		newEntity->SetType(Entity::MEDIUM_BALL);
		newEntity->AddComponent(movComponent);
		newEntity->AddComponent(colComponent);
		newEntity->AddComponent(rendComponent);
		newEntity->SetPosition(position);
		newEntity->SetIsActive(false);

		CGameLogic::instance()->AddBall(newEntity);
		CRenderer::instance()->SetRenderComponent(rendComponent);
	}

	for (size_t i = 0; i < numBalls * 4; i++)
	{
		Entity* newEntity = new Entity(Entity::SMALL_BALL);
		newEntity->SetSize(vec2(16.f, 16.f));
		MovementComponent* movComponent = new MovementComponent(vec2(0, 0), vec2(m_smallVel, -m_smallVel));
		CollisionComponent* colComponent = new CircleCollisionComponent(newEntity->GetSize()->x / 2);
		RenderComponent* rendComponent = new RenderComponent(m_texsmallball, *newEntity->GetSize());

		movComponent->SetMaxHeight(SCR_HEIGHT / 3 * 2);

		newEntity->AddComponent(movComponent);
		newEntity->AddComponent(colComponent);
		newEntity->AddComponent(rendComponent);
		newEntity->SetIsActive(false);

		CGameLogic::instance()->AddBall(newEntity);
		CRenderer::instance()->SetRenderComponent(rendComponent);
	}
}

