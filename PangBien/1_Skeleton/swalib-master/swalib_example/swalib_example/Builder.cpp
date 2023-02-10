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
}

void BuilderLvl2::BuildLevel(AbstractFactory* _absFactory)
{
}
