#include "MovementComponent.h"
#include "../../common/stdafx.h"
#include "../../common/sys.h"

MovementComponent::MovementComponent(vec2 _pos, vec2 _vel)
{
	m_position = _pos;
	vel = _vel;
	currentVel = _vel;
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

	else if (m_Owner->GetType() == Entity::SMALL_BALL || m_Owner->GetType() == Entity::MEDIUM_BALL || m_Owner->GetType() == Entity::BIG_BALL)
	{
		if ((m_position + currentVel * elapsedTime).y > maxHeight)
		{
			currentVel.y *= -1;
		}
	}
	m_position = m_position + currentVel * elapsedTime;
	newPosMsg->newPos = m_position;
	m_Owner->ReceiveMessage(newPosMsg);
}

void MovementComponent::SetVelocity(vec2& _vel)
{
	vel = _vel;
	currentVel = _vel;
}

vec2 MovementComponent::GetVelocity()
{
	return currentVel;
}


vec2* MovementComponent::GetPosition()
{
	return &m_position;
}

void MovementComponent::SetElapsedTime(float _elapsedTime)
{
	elapsedTime = _elapsedTime;
}

void MovementComponent::SetMaxHeight(float _maxHeight)
{
	maxHeight = _maxHeight;
}

void MovementComponent::RecieveMessage(Message* msg)
{
	HorLimitWorldCollMsg* horMsg = dynamic_cast<HorLimitWorldCollMsg*>(msg);
	VertLimitWorldCollMsg* verMsg = dynamic_cast<VertLimitWorldCollMsg*>(msg);
	if (horMsg)
	{
		if (m_Owner->GetType() == Entity::BIG_BALL || m_Owner->GetType() == Entity::MEDIUM_BALL || m_Owner->GetType() == Entity::SMALL_BALL)
		{
			currentVel *= -1.f;
		}
	}
	else if (verMsg) 
	{
		if (m_Owner->GetType() == Entity::BIG_BALL || m_Owner->GetType() == Entity::MEDIUM_BALL || m_Owner->GetType() == Entity::SMALL_BALL)
		{
			currentVel.y *= -1.f;
		}
	}
	//LimitWorldCollMsg* limitMsg = dynamic_cast<LimitWorldCollMsg*>(msg);

	//if (entMsg || limitMsg)
	//	vel *= -1;
}
