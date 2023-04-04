#include "GameLogic.h"
#include "../swalib_example/swalib_example/Component.h"
#include "../swalib_example/swalib_example/MovementComponent.h"
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

void CGameLogic::AddFactory(AbstractFactory* _factory)
{
	m_factories.push_back(_factory);
}

CGameLogic::CGameLogic() {}

void CGameLogic::InitGameLogic(AbstractFactory* _factory)
{
	// Init game state.
	_factory->CreatePlayer();
	_factory->CreateBalls();

	m_maxScore = m_smallBalls.size();
}

void CGameLogic::SetFactories(AbstractFactory* _factory, AbstractFactory* _factory2)
{
	m_factories[0] = _factory;
	m_factories[1] = _factory2;
}

void CGameLogic::UpdateGameLogic(float _fixedTick)
{
	for (int i = 0; i < m_entities.size(); i++) {
		if (m_entities[i]->GetIsActive())
		{
			m_entities[i]->SetElapsedTime(_fixedTick);
			m_entities[i]->Slot();
		}
	}
}

void CGameLogic::CloseGameLogic()
{
	ClearArrays();
	m_factories.clear();
	//delete _instance;
}

void CGameLogic::AddBall(Entity* _ball)
{
	m_entities.push_back(_ball);

	if (_ball->GetType() == Entity::BIG_BALL)
		m_bigBalls.push_back(_ball);
	else if (_ball->GetType() == Entity::MEDIUM_BALL)
		m_medBalls.push_back(_ball);
	else if (_ball->GetType() == Entity::SMALL_BALL)
		m_smallBalls.push_back(_ball);
}

void CGameLogic::AddEntity(Entity* _player)
{
	m_entities.push_back(_player);
	m_playerEntities.push_back(_player);
}

void CGameLogic::ActivateBalls(Entity::EntityType _type, vec2& _pos)
{
	if (_type == Entity::MEDIUM_BALL)
	{
		if (!m_medBalls.empty())
		{
			m_medBalls.back()->SetPosition(_pos);
			m_medBalls.back()->SetIsActive(true);
			m_medBalls.pop_back();

			vec2 newVel = m_medBalls.back()->FindComponent<MovementComponent>()->GetVelocity();
			newVel *= vec2(-1.0, 1.0);
			m_medBalls.back()->FindComponent<MovementComponent>()->SetVelocity(newVel);
			m_medBalls.back()->SetPosition(_pos);
			m_medBalls.back()->SetIsActive(true);
			m_medBalls.pop_back();
		}
	}
	else if (_type == Entity::SMALL_BALL)
	{
		if (!m_smallBalls.empty())
		{
			m_smallBalls.back()->SetPosition(_pos);
			m_smallBalls.back()->SetIsActive(true);
			m_smallBalls.pop_back();

			vec2 newVel = m_smallBalls.back()->FindComponent<MovementComponent>()->GetVelocity();
			newVel *= vec2(-1.0, 1.0);
			m_smallBalls.back()->FindComponent<MovementComponent>()->SetVelocity(newVel);
			m_smallBalls.back()->SetPosition(_pos);
			m_smallBalls.back()->SetIsActive(true);
			m_smallBalls.pop_back();

		}
	}
}

void CGameLogic::ClearArrays()
{
	m_entities.clear();
	m_bigBalls.clear();
	m_medBalls.clear();
	m_smallBalls.clear();
}

void CGameLogic::CheckGameState()
{
	++m_currentScore;
	if (m_currentScore == m_maxScore)
		BeginLevel(true);
}

void CGameLogic::BeginLevel(bool _isLevelFinished)
{
	if (_isLevelFinished)
		++m_level;

	ClearArrays();
	CRenderer::instance()->Clear();

	if (m_factories.size() > m_level)
		InitGameLogic(m_factories[m_level]);
	else
		m_isShutDown = true;
}

bool CGameLogic::GetIsShutDown()
{
	return m_isShutDown;
}

std::vector<Entity*> CGameLogic::GetPlayerEntitiesArray()
{
	return m_playerEntities;
}

std::vector<Entity*> CGameLogic::GetEntitiesArray()
{
	return m_entities;
}
