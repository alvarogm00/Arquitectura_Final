#pragma once
#include "vector2d.h"
#include "stdafx.h"

class CSprite
{
	vec2   pos;	// Position.
	vec2   size;	// Velocity.
	GLuint gfx;

public:
	CSprite(vec2 _pos, vec2 _size, GLuint _gfx);

	vec2 GetPos() const;
	void SetPos(vec2 _pos);
	vec2 GetSize() const;
	void SetSize(vec2& _size);
	GLuint GetGfx();
	void SetGfx(GLuint& _gfx);

	void Draw();
};

