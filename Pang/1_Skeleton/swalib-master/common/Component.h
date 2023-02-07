#pragma once
#include "vector2d.h"
#include "stdafx.h"
#include "CSprite.h"
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
};

class CollisionComponent : public Component
{
	vec2   pos;	// Position.
	vec2 newPos;
	float  radius;	// Radius.
	int id;

public:
	CollisionComponent(float _radius, int _id);

	void SetIndex(int _id);
	int GetIndex() const;
	void SetRadius(float _radius);
	float GetRadius() const;
	void SetNewPos(vec2& _newPos);
	vec2* GetPosition();
	void Slot() override;
};

class MovementComponent : public Component
{
	vec2 vel;	// Velocity.
	vec2 pos;
	float elapsedTime;
public:
	MovementComponent(vec2 _pos, vec2 vel);

	void Slot() override;
	void SetVelocity(vec2& _vel);
	vec2 GetVelocity();
	void SetPosition(vec2& _pos);
	vec2* GetPosition();
	void SetElapsedTime(float _elapsedTime);
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
	void Slot() override;
	void End();
};

