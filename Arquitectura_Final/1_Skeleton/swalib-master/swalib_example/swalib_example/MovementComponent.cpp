#include "MovementComponent.h"
#include "../../common/stdafx.h"
#include "../../common/sys.h"

MovementComponent::MovementComponent(vec2 _pos, vec2 _vel)
{
	pos = _pos;
	vel = _vel;
	currentVel = vel;
	newPosMsg = new NewPosMsg();
}

void MovementComponent::Slot()
{
	if (m_Owner->GetType() == Entity::PLAYER)
	{
		if (SYS_KeyPressed(SYS_KEY_RIGHT))
		{
			currentVel = vel;
		}
		else if (SYS_KeyPressed(SYS_KEY_LEFT))
		{
			currentVel = vel * -1.f;
		}
		else
			currentVel = vel * 0.f;
	}
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
	HorLimitWorldCollMsg* horMsg = dynamic_cast<HorLimitWorldCollMsg*>(msg);
	VertLimitWorldCollMsg* verMsg = dynamic_cast<VertLimitWorldCollMsg*>(msg);
	if (horMsg)
	{
		if (m_Owner->GetType() == Entity::BIG_BALL || m_Owner->GetType() == Entity::MEDIUM_BALL || m_Owner->GetType() == Entity::SMALL_BALL)
		{
			vel *= -1.f;
		}
	}
	else if (verMsg) 
	{
		if (m_Owner->GetType() == Entity::BIG_BALL || m_Owner->GetType() == Entity::MEDIUM_BALL || m_Owner->GetType() == Entity::SMALL_BALL)
		{
			vel.y *= -1.f;
		}
	}
	//LimitWorldCollMsg* limitMsg = dynamic_cast<LimitWorldCollMsg*>(msg);

	//if (entMsg || limitMsg)
	//	vel *= -1;
}
