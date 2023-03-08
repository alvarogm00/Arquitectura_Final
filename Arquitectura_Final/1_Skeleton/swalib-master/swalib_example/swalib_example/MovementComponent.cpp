#include "MovementComponent.h"

MovementComponent::MovementComponent(vec2 _pos, vec2 _vel)
{
	pos = _pos;
	vel = _vel;
	newPosMsg = new NewPosMsg();
}

void MovementComponent::Slot()
{
	pos = pos + vel * elapsedTime;
	newPosMsg->newPos = pos;
	m_Owner->ReceiveMessage(newPosMsg);
}

void MovementComponent::SetVelocity(vec2& _vel)
{
	vel = _vel;
}

vec2 MovementComponent::GetVelocity()
{
	return vel;
}

void MovementComponent::SetPosition(vec2& _pos)
{
	pos = _pos;
}

vec2* MovementComponent::GetPosition()
{
	return &pos;
}

void MovementComponent::SetElapsedTime(float _elapsedTime)
{
	elapsedTime = _elapsedTime;
}

void MovementComponent::RecieveMessage(Message* msg)
{
	EntCollisionMsg* entMsg = dynamic_cast<EntCollisionMsg*>(msg);
	if (entMsg)
	{

	}
	//LimitWorldCollMsg* limitMsg = dynamic_cast<LimitWorldCollMsg*>(msg);

	//if (entMsg || limitMsg)
	//	vel *= -1;
}
