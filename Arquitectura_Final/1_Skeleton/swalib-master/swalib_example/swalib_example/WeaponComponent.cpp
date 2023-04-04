#include "WeaponComponent.h"
#include "MovementComponent.h"
#include "CircleCollisionComponent.h"
#include "RenderComponent.h"
#include "../../common/GameLogic.h"
#include "../../common/Renderer.h"
#include "../../common/stdafx.h"
#include "../../common/sys.h"

WeaponComponent::WeaponComponent(GLuint& _projectileTex, float _projectileVel)
{
	m_projectile = new Entity();
	m_projectile->SetSize(vec2(16.f, 16.f));
	MovementComponent* movComponent = new MovementComponent(vec2(0,0), vec2(0, _projectileVel));
	CollisionComponent* colComponent = new CircleCollisionComponent(m_projectile->GetSize()->x / 2);
	RenderComponent* rendComponent = new RenderComponent(_projectileTex, *m_projectile->GetSize());

	m_projectile->SetType(Entity::PROYECTILE);
	m_projectile->AddComponent(movComponent);
	m_projectile->AddComponent(colComponent);
	m_projectile->AddComponent(rendComponent);
	m_projectile->SetIsActive(false);

	CRenderer::instance()->SetRenderComponent(rendComponent);
	CGameLogic::instance()->AddEntity(m_projectile);
}

WeaponComponent::~WeaponComponent()
{
	delete m_projectile;
}

void WeaponComponent::Slot()
{
	if (SYS_KeyPressed(SYS_KEY_UP))
	{
		if (!m_projectile->GetIsActive()) 
		{
			m_projectile->SetPosition(m_position);
			m_projectile->SetIsActive(true);
		}
	}
}

void WeaponComponent::RecieveMessage(Message* _msg)
{
}
