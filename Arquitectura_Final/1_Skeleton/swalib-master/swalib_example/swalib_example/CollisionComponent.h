#pragma once
#include "Component.h"
class CollisionComponent : public Component
{
protected:
	vec2 pos;	// Position.
	vec2 newPos;

	BallCollisionMsg* ballMsg;
	VertLimitWorldCollMsg* vertLimitMsg;
	HorLimitWorldCollMsg* horLimitMsg;
	ProjectileCollisionMsg* projMsg;

public:
	CollisionComponent();
	virtual ~CollisionComponent();

    virtual void Slot() override;
    virtual void RecieveMessage(Message* _msg) override;

	void SetPos(vec2& _newPos);
	vec2* GetPosition();

	static float Clamp(float _value, float _minvalue, float _maxValue);

	virtual bool collides(const CollisionComponent& other) const = 0;
	virtual bool collides(vec2& circlePos, float circleRadius) const = 0;
	virtual bool collides(const vec2& rectPos, const vec2& rectSize) const = 0;

protected:
	static bool checkCircleCircle(const vec2& pos1, float radius1, const vec2& pos2, float radius2);
	static bool checkCircleRect(const vec2& circlePos, float circleRadius, const vec2& rectPos, const vec2& rectSize);
};

