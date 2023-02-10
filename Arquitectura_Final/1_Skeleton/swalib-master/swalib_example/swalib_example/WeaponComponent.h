#pragma once
#include "Component.h"
class WeaponComponent : public Component
{
    virtual void Slot() override;
    virtual void RecieveMessage(Message* _msg) override;
};

