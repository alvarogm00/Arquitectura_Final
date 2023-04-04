#include "CollisionComponent.h"

CollisionComponent::CollisionComponent()
{
}

CollisionComponent::~CollisionComponent()
{
}

void CollisionComponent::Slot()
{
}

void CollisionComponent::RecieveMessage(Message* _msg)
{
}

vec2* CollisionComponent::GetPosition()
{
	return &m_position;
}

float CollisionComponent::Clamp(float _value, float _minvalue, float _maxValue)
{
	if (_value < _minvalue)
	{
		_value = _minvalue;
	}
	else if (_value > _maxValue)
	{
		_value = _maxValue;
	}
	else
		_value = _value;

	return _value;
}

bool CollisionComponent::checkCircleCircle(const vec2& pos1, float radius1, const vec2& pos2, float radius2)
{
	float distance = vlen2(pos1 - pos2);
	float radiusSum = radius1 + radius2;
	if (distance < radiusSum)
		return true;
	else
		return false;
}

bool CollisionComponent::checkCircleRect(const vec2& circlePos, float circleRadius, const vec2& rectPos, const vec2& rectSize)
{
	float closestX = CollisionComponent::Clamp(circlePos.x, rectPos.x, (rectPos.x + rectSize.x));
	float closestY = CollisionComponent::Clamp(circlePos.y, rectPos.y, (rectPos.y + rectSize.y));

	vec2 closestPos(closestX, closestY);
	float shortestDistance = vlen2(closestPos - circlePos);
	if (shortestDistance < circleRadius)
	{
		return true;
	}
	else
		return false;
}

void CollisionComponent::SetNewPosition(vec2 _newPos)
{
	newPos = _newPos;
}
