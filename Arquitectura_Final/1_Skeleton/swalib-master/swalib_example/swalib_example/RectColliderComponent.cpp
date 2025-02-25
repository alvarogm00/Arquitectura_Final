#include "RectColliderComponent.h"
#include "../../common/GameLogic.h"

RectColliderComponent::RectColliderComponent(vec2& _size)
{
	size = _size;
}

void RectColliderComponent::Slot()
{
	if ((newPos.x < SCR_WIDTH) && (newPos.x > 0)) {
		m_Owner->SetPosition(newPos);
	}
}

void RectColliderComponent::SetSize(vec2& _size)
{
	size = _size;
}

vec2* RectColliderComponent::GetSize()
{
	return &size;
}

bool RectColliderComponent::collides(const CollisionComponent& other) const
{
	return other.collides(m_position, size);
}

bool RectColliderComponent::collides(vec2& circlePos, float circleRadius) const
{
	return checkCircleRect(circlePos, circleRadius, m_position, size);
}

bool RectColliderComponent::collides(const vec2& rectPos, const vec2& rectSize) const
{
	return false;
}

void RectColliderComponent::RecieveMessage(Message* msg)
{
	BallCollisionMsg* ballMsg = dynamic_cast<BallCollisionMsg*>(msg);
	NewPosMsg* newPosMsg = dynamic_cast<NewPosMsg*>(msg);
	if (newPosMsg)
	{
		SetNewPosition(newPosMsg->newPos);
	}
	else if (ballMsg)
	{
		CGameLogic::instance()->BeginLevel(false);
	}
}
