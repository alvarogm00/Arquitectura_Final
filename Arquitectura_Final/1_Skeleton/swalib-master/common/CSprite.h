#pragma once
#include "vector2d.h"
#include "stdafx.h"

class RenderComponent;

class CSprite
{
	vec2   pos;	// Position.
	vec2   size;	// Velocity.
	GLuint gfx;
	RenderComponent* m_Owner;

public:
	CSprite(vec2 _pos, vec2 _size, GLuint _gfx);
	~CSprite();

	void SetOwner(RenderComponent* _Owner);
	vec2 GetPos() const;
	void SetPos(vec2 _pos);
	vec2 GetSize() const;
	void SetSize(vec2& _size);
	GLuint GetGfx();
	void SetGfx(GLuint& _gfx);

	void Draw();
	void End();
};

