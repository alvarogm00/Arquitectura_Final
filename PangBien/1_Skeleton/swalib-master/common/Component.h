#pragma once
#include "vector2d.h"
#include "stdafx.h"
#include "CSprite.h"
#include "../swalib_example/swalib_example/Message.h"
//#include "../../common/GameLogic.h"
//#include "../../common/SBall.h"

class Entity;

class Component
{
protected:
	Entity *m_Owner;

public:
	void SetOwner(Entity* _owner);
	Component();
	virtual void Slot() = 0;
	virtual void ReceiveMessage(Message* msg) = 0;
};

class CollisionComponent : public Component
{
protected:
	vec2 pos;	// Position.
	vec2 newPos;
	
	BallCollisionMsg* ballMsg;
	LimitWorldCollMsg* limitMsg; 
	ProjectileCollisionMsg* projMsg;

public:
	CollisionComponent();

	void SetPos(vec2& _newPos);
	vec2* GetPosition();

	static float Clamp(float _value, float _minvalue, float _maxValue);

	virtual bool collides(const CollisionComponent& other) const = 0;
	virtual bool collides(const vec2& circlePos, float circleRadius) const = 0;
	virtual bool collides(const vec2& rectPos, const vec2& rectSize) const = 0;

	virtual void Slot() override;
	virtual void ReceiveMessage(Message* msg) override;

protected:
	static bool checkCircleCircle(const vec2& pos1, float radius1, const vec2& pos2, float radius2);
	static bool checkCircleRect(const vec2& circlePos, float circleRadius, const vec2& rectPos, const vec2& rectSize);
};

class CircleCollision : public CollisionComponent
{
	float radius;

public:
	virtual bool collides(const CollisionComponent& other) const override;
	virtual bool collides(const vec2& circlePos, float circleRadius) const override;
	virtual bool collides(const vec2& rectPos, const vec2& rectSize) const override;
	virtual void Slot() override;

	void SetRadius(float _radius);
	float GetRadius() const;
};

class RectCollision : public CollisionComponent
{
	vec2 size;

public:
	virtual bool collides(const CollisionComponent& other) const override;
	virtual bool collides(const vec2& circlePos, float circleRadius) const override;
	virtual bool collides(const vec2& rectPos, const vec2& rectSize) const override;

	void SetSize(vec2& _size);
	vec2* GetSize();
};

class MovementComponent : public Component
{
	vec2 vel;	// Velocity.
	vec2 pos;
	float elapsedTime;
	NewPosMsg* newPosMsg;

public:
	MovementComponent(vec2 _pos, vec2 vel);

	void SetVelocity(vec2& _vel);
	vec2 GetVelocity();
	void SetPosition(vec2& _pos);
	vec2* GetPosition();
	void SetElapsedTime(float _elapsedTime);

	virtual void Slot() override;
	virtual void ReceiveMessage(Message* msg) override;
};

class RenderComponent : public Component
{
	GLuint gfx;	// OpenGL for id. for visualization purposes. 
	vec2 size;
	vec2 pos;
	CSprite* sprite;

public:
	RenderComponent(GLuint& _gfx, vec2& _size, CSprite* _sprite);

	void SetSize(vec2& _size);
	void SetGfx(GLuint& _gfx);
	void SetPos(vec2& _pos);
	vec2 GetPos();
	void End();

	virtual void Slot() override;
	virtual void ReceiveMessage(Message* msg) override;

};

