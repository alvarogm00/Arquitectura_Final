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
	vec2   pos;	// Position.
	vec2 newPos;
	float  radius;	// Radius.
	int id;
	ProjectileCollisionMsg* projMsg;
	BallCollisionMsg* ballMsg;
	LimitWorldCollMsg* limitMsg; 

public:
	CollisionComponent(float _radius, int _id);

	void SetIndex(int _id);
	int GetIndex() const;
	void SetRadius(float _radius);
	float GetRadius() const;
	void SetPos(vec2& _newPos);
	vec2* GetPosition();

	virtual void Slot() override;
	virtual void ReceiveMessage(Message* msg) override;
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

