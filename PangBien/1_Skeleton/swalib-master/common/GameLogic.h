#pragma once
#include "SBall.h"
#include "core.h"
#include "Entity.h"
#include <vector>

class CGameLogic
{
public:
	static CGameLogic* instance();
	void InitGameLogic(GLuint* _texsmallball);
	void UpdateGameLogic(float _elapsedTime);
	void CloseGameLogic();
	void CreateBalls(Entity::EntityType, vec2& _pos);
	int GetNumBalls() const;
	std::vector<Entity>* GetEntitiesArray();
	std::vector<Entity>* GetPlayerEntitiesArray();

private:
	int m_lifes;
	const static unsigned int NUM_BALLS = 10;	// Max. num balls.
	const float MAX_BALL_SPEED = 80;
	std::vector<Entity> m_entities;
	std::vector<Entity> m_playerEntities;

    CGameLogic();
	static CGameLogic* _instance;
};