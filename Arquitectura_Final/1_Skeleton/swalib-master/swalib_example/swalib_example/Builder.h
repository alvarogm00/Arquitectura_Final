#pragma once
#include "AbstractFactory.h"
#include "Level.h"

class Builder
{
protected:
	Level* m_level;
public:
	virtual void BuildLevel(AbstractFactory* _absFactory) = 0;
	void SetLevel(Level* _level);
	Level* GetLevel();
};

class BuilderLvl1 : public Builder
{
public:
	virtual void BuildLevel(AbstractFactory* _absFactory) override;
};

class BuilderLvl2 : public Builder
{
public:
	virtual void BuildLevel(AbstractFactory* _absFactory) override;
};
