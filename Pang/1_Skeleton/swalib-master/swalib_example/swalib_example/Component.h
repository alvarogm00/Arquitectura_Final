#pragma once
#include "../../common/vector2d.h"
#include "../../common/GameLogic.h"
#include "../../common/SBall.h"
#include "../

class Component
{
protected:
	Entity *m_Owner;

public:
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
public:
	MovementComponent(vec2 _pos, vec2 vel);

	void Slot() override;
	void SetVelocity(vec2& _vel);
	vec2* GetVelocity();
	void SetPosition(vec2& _pos);
	vec2* GetPosition();
};

class RenderComponent : public Component
{
	GLuint gfx;	// OpenGL for id. for visualization purposes. 
	vec2 size;
public:
	RenderComponent(GLuint& _gfx);

	void SetSize(vec2& _size);
	void SetGfx(GLuint& _gfx);
	void Slot() override;
	void End();
};

