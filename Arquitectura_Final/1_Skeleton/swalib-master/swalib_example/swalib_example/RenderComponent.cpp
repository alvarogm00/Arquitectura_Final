#include "RenderComponent.h"
#include "../../common/Renderer.h"

RenderComponent::RenderComponent()
{
	gfx = 0;
	pos = vec2(0, 0);
	SetSize(vec2(0,0));
}

RenderComponent::RenderComponent(GLuint& _gfx, vec2& _size/*, CSprite* _sprite*/)
{
	gfx = _gfx;
	pos = vec2(0, 0);
	SetSize(_size);
	sprite = new CSprite(vec2(0, 0), vec2(0, 0), 0);
	sprite->SetGfx(gfx);
	sprite->SetPos(pos);
	sprite->SetSize(size);
	//CRenderer::instance()->SetSprite(0, sprite);
}

void RenderComponent::SetSize(vec2& _size)
{
	size = _size;
}

void RenderComponent::SetGfx(GLuint& _gfx)
{
	gfx = _gfx;
}

void RenderComponent::SetPos(vec2& _pos)
{
	pos = _pos;
	sprite->SetPos(pos);
}

vec2 RenderComponent::GetPos()
{
	pos = *m_Owner->GetPosition();
	return pos;
}

void RenderComponent::RecieveMessage(Message* msg)
{
	NewPosMsg* npMsg = dynamic_cast<NewPosMsg*>(msg);
	if (npMsg)
		SetPos(npMsg->newPos);
}

void RenderComponent::Slot()
{
	if(m_Owner->GetIsActive())
		CORE_RenderCenteredSprite(GetPos(),size, gfx);
}

void RenderComponent::End()
{
	CORE_UnloadPNG(gfx);
}

