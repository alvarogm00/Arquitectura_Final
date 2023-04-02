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
	_factory->CreateBalls();
	_factory->CreatePlayer();
}

void CGameLogic::SetFactories(AbstractFactory* _factory, AbstractFactory* _factory2)
{
	m_absFactory1 = _factory;
	m_absFactory2 = _factory2;
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
	m_entities.~vector();
	//delete _instance;
}

void CGameLogic::AddBall(Entity* _ball)
{
	m_entities.push_back(_ball);

	if (_ball->BIG_BALL)
		m_bigBalls.push_back(_ball);
	else if (_ball->MEDIUM_BALL)
		m_medBalls.push_back(_ball);
	else if (_ball->SMALL_BALL)
		m_smallBalls.push_back(_ball);
}

void CGameLogic::AddEntity(Entity* _player)
{
	m_entities.push_back(_player);
}

void CGameLogic::ActivateBalls(Entity::EntityType _type, vec2& _pos)
{
	if (_type == Entity::MEDIUM_BALL)
	{
		m_medBalls.back()->SetIsActive(true);
		m_medBalls.pop_back();

		vec2 newVel = m_medBalls.back()->FindComponent<MovementComponent>()->GetVelocity();
		newVel *= vec2(-1.0, 1.0);
		m_medBalls.back()->FindComponent<MovementComponent>()->SetVelocity(newVel);
		m_medBalls.back()->SetIsActive(true);
		m_medBalls.pop_back();
	}
	else if (_type == Entity::SMALL_BALL)
	{
		m_smallBalls.back()->SetIsActive(true);
		m_smallBalls.pop_back();

		vec2 newVel = m_smallBalls.back()->FindComponent<MovementComponent>()->GetVelocity();
		newVel *= vec2(-1.0, 1.0);
		m_smallBalls.back()->FindComponent<MovementComponent>()->SetVelocity(newVel);
		m_smallBalls.back()->SetIsActive(true);
		m_smallBalls.pop_back();
	}
}

void CGameLogic::ClearArrays()
{
	for (size_t i = 0; i < m_entities.size(); i++)
	{
		delete m_entities[i];
	};

	m_entities.clear();
	m_bigBalls.clear();
	m_medBalls.clear();
	m_smallBalls.clear();
}

void CGameLogic::CheckGameState()
{
	if (m_smallBalls.empty())
	{
		if (m_level == 0)
		{
			ClearArrays();
			InitGameLogic(m_absFactory2);
		}
		//siguiente nivel o acabar el juego
	}
}

void CGameLogic::BeginLevel(bool _isLevelFinished)
{
	if (_isLevelFinished)
		++m_level;

	ClearArrays();
	InitGameLogic(m_factories[m_level]);
}

void CGameLogic::SetNumBalls(int _numballs)
{
	NUM_BALLS = _numballs;
}
//
//int CGameLogic::GetNumBalls() const
//{
//	return NUM_BALLS;
//}

std::vector<Entity*> CGameLogic::GetEntitiesArray()
{
	return m_entities;
}

std::vector<Entity*> CGameLogic::GetPlayerEntitiesArray()
{
	return m_playerEntities;
}