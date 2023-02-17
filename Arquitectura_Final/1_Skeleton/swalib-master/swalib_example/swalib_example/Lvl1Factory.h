#pragma once
#include "AbstractFactory.h"
class Lvl1Factory : public AbstractFactory
{
public:
	Lvl1Factory(int _numBalls, Entity::EntityType _starterType);

	virtual void CreateBalls() override;
};

