#include "CSprite.h"
#include "core.h";

CSprite::CSprite(vec2 _pos, vec2 _size, GLuint _gfx)
{
	SetPos(_pos);
	SetSize(_size);
}

vec2 CSprite::GetPos() const
{
	return pos;
}

void CSprite::SetPos(vec2 _pos)
{
	pos = _pos;
}

vec2 CSprite::GetSize() const
{
	return size;
}

void CSprite::SetSize(vec2& _size)
{
	size = _size;
}

GLuint CSprite::GetGfx()
{
	return gfx;
}

void CSprite::SetGfx(GLuint& _gfx)
{
	gfx = _gfx;
}

void CSprite::Draw()
{
	CORE_RenderCenteredSprite(GetPos(), GetSize(), GetGfx());
}
