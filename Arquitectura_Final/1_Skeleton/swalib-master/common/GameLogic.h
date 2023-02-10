#pragma once
#include "SBall.h"
#include "core.h"
#include "Entity.h"
#include <vector>

class CGameLogic
{
public:
	static CGameLogic* instance();
	void InitGameLogic(GLuint* _texbigball, GLuint* _texmediumball, GLuint* _texsmallball);
	void UpdateGameLogic(float _elapsedTime);
	void CloseGameLogic();
	void CreateBalls(Entity::EntityType _type, vec2& _pos, GLuint* _texball);
	void RestartLevel();
	void SetNumBalls(int _numballs);
	int GetNumBalls() const;
	std::vector<Entity*> GetEntitiesArray();
	std::vector<Entity*> GetPlayerEntitiesArray();

private:
	int m_lifes;
	static unsigned int NUM_BALLS;	// Max. num balls.
	const float MAX_BALL_SPEED = 80;

	vec2 m_bigVel, m_medVel, m_smallVel;

	std::vector<Entity*> m_entities;
	std::vector<Entity*> m_playerEntities;

    CGameLogic();
	static CGameLogic* _instance;
};