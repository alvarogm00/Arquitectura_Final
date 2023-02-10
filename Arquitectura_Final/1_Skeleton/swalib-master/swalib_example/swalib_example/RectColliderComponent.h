#pragma once
#include "CollisionComponent.h"
class RectColliderComponent : public CollisionComponent
{
	vec2 size;

public:
	virtual void Slot() override;
	virtual void RecieveMessage(Message* msg) override;

	virtual bool collides(const CollisionComponent& other) const override;
	virtual bool collides(const vec2& circlePos, float circleRadius) const override;
	virtual bool collides(const vec2& rectPos, const vec2& rectSize) const override;

	void SetSize(vec2& _size);
	vec2* GetSize();
};

