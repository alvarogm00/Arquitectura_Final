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
	int GetNumBalls() const;
	std::vector<Entity>* GetEntitiesArray();
	//SBall* GetBallsArray();
	//CSprite** GetSpritesArray();

private:
	const static unsigned int NUM_BALLS = 10;	// Max. num balls.
	const float MAX_BALL_SPEED = 80;
	std::vector<Entity> m_entities;
	//SBall tBalls[NUM_BALLS];
	//CSprite* sprites[NUM_BALLS];

    CGameLogic();
	static CGameLogic* _instance;
};