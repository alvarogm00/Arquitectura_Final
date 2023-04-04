#include "RenderComponent.h"
#include "../../common/Renderer.h"

RenderComponent::RenderComponent()
{
	gfx = 0;
	m_position = vec2(0, 0);
	SetSize(vec2(0,0));
}

RenderComponent::RenderComponent(GLuint& _gfx, vec2& _size/*, CSprite* _sprite*/)
{
	gfx = _gfx;
	size = _size;
	m_position = vec2(0, 0);
	//sprite = new CSprite(vec2(0, 0), vec2(0, 0), 0);
	//sprite->SetOwner(this);
	//sprite->SetGfx(gfx);
	//sprite->SetPos(m_position);
	//sprite->SetSize(size);
	//CRenderer::instance()->SetSprite(0, sprite);
}

RenderComponent::~RenderComponent()
{
	End();
}

void RenderComponent::SetSize(vec2& _size)
{
	size = _size;
	//sprite->SetSize(_size);
}

vec2 RenderComponent::GetSize()
{
	return size;
}

void RenderComponent::SetGfx(GLuint& _gfx)
{
	gfx = _gfx;
	//sprite->SetGfx(_gfx);
}

vec2 RenderComponent::GetPos()
{
	m_position = *m_Owner->GetPosition();
	return m_position;
}

void RenderComponent::RecieveMessage(Message* msg)
{
	//NewPosMsg* npMsg = dynamic_cast<NewPosMsg*>(msg);
	//if (npMsg)
	//	SetPos(npMsg->newPos);
}

void RenderComponent::Slot()
{
	
}

void RenderComponent::Draw()
{
	if (m_Owner->GetIsActive())
		CORE_RenderCenteredSprite(GetPos(), size, gfx);
}

void RenderComponent::End()
{
	CORE_UnloadPNG(gfx);
}

