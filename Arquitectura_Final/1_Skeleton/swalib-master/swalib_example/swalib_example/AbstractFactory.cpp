#include "AbstractFactory.h"
#include "WeaponComponent.h"
#include "MovementComponent.h"
#include "RectColliderComponent.h"
#include "RenderComponent.h"
#include "../../common/GameLogic.h"
#include "../../common/Renderer.h"

void AbstractFactory::CreateBalls()
{
}

void AbstractFactory::CreatePlayer()
{
    Entity* player = new Entity(Entity::PLAYER);
		player->SetSize(m_playerSize);
		MovementComponent* movement = new MovementComponent(vec2(SCR_WIDTH/2.f, 20.f), vec2(100.f, 0.f));
		RectColliderComponent* collider = new RectColliderComponent(*player->GetSize());
		RenderComponent* render = new RenderComponent(m_texPlayer, *player->GetSize());
    WeaponComponent* weapon = new WeaponComponent(m_texWeapon, m_weaponVel.y);

		player->SetIsActive(true);
		player->SetPosition(vec2(SCR_WIDTH / 2, 36.f));
		player->AddComponent(movement);
		player->AddComponent(collider);
		player->AddComponent(render);
    player->AddComponent(weapon);
		weapon->SetPosition(*player->GetPosition());
		CGameLogic::instance()->AddEntity(player);
		CRenderer::instance()->SetRenderComponent(render);
}

int AbstractFactory::GetNumBalls()
{
    return numBalls;
}
