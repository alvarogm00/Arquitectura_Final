#pragma once
#include "AbstractFactory.h"
class Lvl1Factory : public AbstractFactory
{
public:
	Lvl1Factory(int _numBalls, float m_bigVel, float m_medVel, float m_smallVel, Entity::EntityType _starterType, GLuint& m_texbigball, GLuint& m_texmediumball, GLuint& m_texsmallball,
		GLuint& _texPlayer, vec2 _playerSize);
	void CreateBalls() override;
};

