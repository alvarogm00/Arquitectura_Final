#include "GameLogic.h"
#include "Component.h"
#include "../common/Renderer.h"

CGameLogic* CGameLogic::_instance = nullptr;

CGameLogic* CGameLogic::instance()
{
	if (_instance == nullptr)
	{
		_instance = new CGameLogic();
	}
	return _instance;
}

CGameLogic::CGameLogic() {}

void CGameLogic::InitGameLogic(GLuint* _texbigball, GLuint* _texmediumball, GLuint* _texsmallball)
{
	// Init game state.
	if (_texbigball != 0)
	{
		for (int i = 0; i < NUM_BALLS; i++) {
			Entity* newEntity = new Entity(Entity::BIG_BALL);
			MovementComponent* movComponent = new MovementComponent(vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT)), vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED)));
			CollisionComponent* colComponent = new CircleCollision(16.f);
			RenderComponent* rendComponent = new RenderComponent(*_texbigball, vec2(16.0f * 2.0f, 16.0f * 2.0f), nullptr);

			newEntity->AddComponent(movComponent);
			newEntity->AddComponent(colComponent);
			newEntity->AddComponent(rendComponent);

			m_entities.push_back(newEntity);
		}
	}
	else
	{
	}
}

void CGameLogic::UpdateGameLogic(float _fixedTick)
{
	for (int i = 0; i < NUM_BALLS; i++) {
		if (m_entities[i]->GetIsActive())
		{
			m_entities[i]->SetElapsedTime(_fixedTick);
			m_entities[i]->Slot();
		}
	}
}

void CGameLogic::CloseGameLogic()
{
	m_entities.~vector();
	delete _instance;
}

void CGameLogic::CreateBalls(Entity::EntityType _type, vec2& _pos, GLuint* _texball)
{
	Entity* newEntity = new Entity(_type);
	if(_type == Entity::BIG_BALL)
		MovementComponent* movComponent = new MovementComponent(_pos, m_bigVel);
	else if(_type == Entity::MEDIUM_BALL)
		MovementComponent* movComponent = new MovementComponent(_pos, m_medVel);
	else if(_type == Entity::SMALL_BALL)
		MovementComponent* movComponent = new MovementComponent(_pos, m_smallVel);

	CollisionComponent* colComponent = new CircleCollision(16.f);
	RenderComponent* rendComponent = new RenderComponent(*_texball, vec2(16.0f * 2.0f, 16.0f * 2.0f), nullptr);

	newEntity->AddComponent(movComponent);
	newEntity->AddComponent(colComponent);
	newEntity->AddComponent(rendComponent);

	m_entities.push_back(newEntity);
}

void CGameLogic::SetNumBalls(int _numballs)
{
	NUM_BALLS = _numballs;
}

int CGameLogic::GetNumBalls() const
{
	return NUM_BALLS;
}

std::vector<Entity*> CGameLogic::GetEntitiesArray()
{
	return m_entities;
}

std::vector<Entity*> CGameLogic::GetPlayerEntitiesArray()
{
	return m_playerEntities;
}