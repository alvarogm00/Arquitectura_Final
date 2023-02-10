#include "SBall.h"
#include "GameLogic.h"
//
//void SBall::SetPos(vec2& _pos)
//{
//	pos = _pos;
//}
//
//vec2 SBall::GetPos() const
//{
//	return pos;
//}
//
//void SBall::SetVel(vec2& _vel)
//{
//	vel = _vel;
//}
//
//vec2 SBall::GetVel() const
//{
//	return vel;
//}
//
//void SBall::SetRadius(float _radius)
//{
//	radius = _radius;
//}
//
//float SBall::GetRadius() const
//{
//	return radius;
//}
//
//void SBall::SetIndex(int _id)
//{
//	id = _id;
//}
//
//int SBall::GetIndex() const
//{
//	return id;
//}
//
//void SBall::SetSprite(vec2& _pos, vec2& _size, GLuint& _gfx)
//{
//	sprite = new CSprite(_pos, _size, _gfx);
//}
//
//CSprite* SBall::GetSprite() const
//{
//	return sprite;
//}
//
//void SBall::Slot(float _elapsedTime)
//{
//		// New Pos.
//	vec2 newpos = pos + vel * _elapsedTime;
//	sprite->SetPos(newpos);
//
//		// Collision detection.
//	const int numBalls = CGameLogic::instance()->GetNumBalls();
//	SBall* balls = CGameLogic::instance()->GetBallsArray();
//
//		bool collision = false;
//		int colliding_ball = -1;
//		for (int j = 0; j < numBalls; j++) 
//		{
//			if (id != j)
//			{
//				if (pos + vel != balls[j].pos + balls[j].vel) {
//					float limit2 = (radius + balls[j].radius) * (radius + balls[j].radius);
//					if (vlen2(newpos - balls[j].pos) <= limit2) {
//						collision = true;
//						colliding_ball = j;
//						break;
//					}
//				}
//			}
//		}
//
//		if (!collision) {
//			pos = newpos;
//		}
//		else {
//			// Rebound!
//			vel = vel * -1.f;
//			balls[colliding_ball].vel = balls[colliding_ball].vel * -1.f;
//		}
//
//		// Rebound on margins.
//		if ((pos.x > SCR_WIDTH) || (pos.x < 0)) {
//			vel.x *= -1.0;
//		}
//		if ((pos.y > SCR_HEIGHT) || (pos.y < 0)) {
//			vel.y *= -1.0;
//		}
//}
