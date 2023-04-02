#pragma once
#include "Component.h"
#include "../../common/stdafx.h"
class WeaponComponent : public Component
{
public:
  WeaponComponent(GLuint& _projectileTex, float _projectileVel);
  ~WeaponComponent();
    virtual void Slot() override;
    virtual void RecieveMessage(Message* _msg) override;

    Entity* m_projectile = nullptr;
};

