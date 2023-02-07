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

void CGameLogic::InitGameLogic(GLuint* _texsmallball)
{
	// Init game state.
	for (int i = 0; i < NUM_BALLS; i++) {
		Entity* newEntity = new Entity();
		MovementComponent* movComponent = new MovementComponent(vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT)), vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED)));
		CollisionComponent* colComponent = new CollisionComponent(16.f, i);
		RenderComponent* rendComponent = new RenderComponent(*_texsmallball, vec2(16.0f * 2.0f, 16.0f * 2.0f), nullptr);

		newEntity->AddComponent(movComponent);
		newEntity->AddComponent(colComponent);
		newEntity->AddComponent(rendComponent);

		m_entities.push_back(*newEntity);
		/*tBalls[i].SetPos(vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT)));
		tBalls[i].SetVel(vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED)));
		tBalls[i].SetRadius(16.f);
		tBalls[i].SetSprite(tBalls[i].GetPos(), vec2(tBalls[i].GetRadius() * 2.f, tBalls[i].GetRadius() * 2.f), *_texsmallball);
		tBalls[i].SetIndex(i);
		sprites[i] = tBalls[i].GetSprite();*/

	}
}

void CGameLogic::UpdateGameLogic(float _fixedTick)
{
	for (int i = 0; i < NUM_BALLS; i++) {
		m_entities[i].SetElapsedTime(_fixedTick);
		m_entities[i].Slot();
		// New Pos.
		//tBalls[i].Slot(_fixedTick);
	}
}

void CGameLogic::CloseGameLogic()
{
	m_entities.~vector();
	delete _instance;
}

int CGameLogic::GetNumBalls() const
{
	return NUM_BALLS;
}

std::vector<Entity>* CGameLogic::GetEntitiesArray()
{
	return &m_entities;
}


//SBall* CGameLogic::GetBallsArray()
//{
//	return nullptr;
//	//return tBalls;
//}
//
//CSprite** CGameLogic::GetSpritesArray()
//{
//	return nullptr;
//	//return sprites;
//}



