#include "RectColliderComponent.h"

void RectColliderComponent::Slot()
{
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
	return other.collides(pos, size);
}

bool RectColliderComponent::collides(const vec2& circlePos, float circleRadius) const
{
	return checkCircleRect(circlePos, circleRadius, pos, size);
}

bool RectColliderComponent::collides(const vec2& rectPos, const vec2& rectSize) const
{
	return false;
}

void RectColliderComponent::RecieveMessage(Message* msg)
{
	BallCollisionMsg* ballMsg = dynamic_cast<BallCollisionMsg*>(msg);
	if (ballMsg)
	{

	}
}
