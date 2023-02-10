#include "AbstractFactory.h"
#include "WeaponComponent.h"

void AbstractFactory::CreatePlayer()
{
    Entity* player = new Entity(Entity::PLAYER);
    WeaponComponent* weapon = new WeaponComponent();

    player->AddComponent(weapon);
}

int AbstractFactory::GetNumBalls()
{
    return numBalls;
}
