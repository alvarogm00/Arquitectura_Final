#include "Builder.h"

void Builder::SetLevel(Level* _level)
{
	m_level = _level;
}

Level* Builder::GetLevel()
{
	return m_level;
}

void BuilderLvl1::BuildLevel(AbstractFactory* _absFactory)
{
	m_level = new Level();
	_absFactory->CreateBalls();
	_absFactory->CreatePlayer();
}

void BuilderLvl2::BuildLevel(AbstractFactory* _absFactory)
{
	m_level = new Level();
	_absFactory->CreateBalls();
	_absFactory->CreatePlayer();
}
