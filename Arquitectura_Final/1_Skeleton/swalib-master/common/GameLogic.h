#pragma once
#include "SBall.h"
#include "core.h"
#include "Entity.h"
#include <vector>
#include "../swalib_example/swalib_example/AbstractFactory.h"

class CGameLogic
{
public:
	static CGameLogic* instance();

	void AddFactory(AbstractFactory* _factory);

	void InitGameLogic(AbstractFactory* _factory);
	void SetFactories(AbstractFactory* _factory, AbstractFactory* _factory2);
	void UpdateGameLogic(float _elapsedTime);
	void CloseGameLogic();

	void AddBall(Entity* _ball);
	void AddEntity(Entity* _player);
	void ActivateBalls(Entity::EntityType _type, vec2& _pos);
	void ClearArrays();

	void CheckGameState();
	void BeginLevel(bool _isLevelFinished);

	bool GetIsShutDown();

	std::vector<Entity*> GetPlayerEntitiesArray();
	std::vector<Entity*> GetEntitiesArray();

private:
	int m_maxScore = 0;
	int m_currentScore = 0;
	int m_level = 0;
	bool m_isShutDown = false;
	vec2 m_bigVel, m_medVel, m_smallVel;

	std::vector<Entity*> m_entities;
	std::vector<Entity*> m_playerEntities;
	std::vector<Entity*> m_bigBalls;
	std::vector<Entity*> m_medBalls;
	std::vector<Entity*> m_smallBalls;

	std::vector<AbstractFactory*> m_factories;

    CGameLogic();
	static CGameLogic* _instance;
};