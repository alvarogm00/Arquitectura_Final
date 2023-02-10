#pragma once
#include "CollisionComponent.h"
class CircleCollisionComponent : public CollisionComponent
{
protected:
    float radius;

public:
    CircleCollisionComponent(float _radius);
    virtual void Slot() override;
    virtual void RecieveMessage(Message* _msg) override;

    virtual bool collides(const CollisionComponent& other) const override;
    virtual bool collides(vec2& circlePos, float circleRadius) const override;
    virtual bool collides(const vec2& rectPos, const vec2& rectSize) const override;

    void SetRadius(float _radius);
    float GetRadius();
};

