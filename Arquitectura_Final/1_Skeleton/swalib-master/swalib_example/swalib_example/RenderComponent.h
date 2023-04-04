#pragma once
#include "Component.h"
#include "../../common/CSprite.h"

class RenderComponent : public Component
{
	GLuint gfx;	// OpenGL for id. for visualization purposes. 
	vec2 size;
	//vec2 pos;
	CSprite* sprite;

public:
	RenderComponent();
	RenderComponent(GLuint& _gfx, vec2& _size/*, CSprite* _sprite*/);
	~RenderComponent();

	void SetSize(vec2& _size);
	vec2 GetSize();
	void SetGfx(GLuint& _gfx);
	//void SetPos(vec2& _pos);
	vec2 GetPos();
	void End();

	virtual void Slot() override;
	virtual void Draw();
	virtual void RecieveMessage(Message* msg) override;
};

