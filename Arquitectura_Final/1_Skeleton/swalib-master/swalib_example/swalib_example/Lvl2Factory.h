#pragma once
#include "AbstractFactory.h"
class Lvl2Factory :
    public AbstractFactory
{
    Lvl2Factory(int _numBalls, float m_bigVel, float m_medVel, float m_smallVel, Entity::EntityType _starterType, GLuint* m_texbigball, GLuint* m_texmediumball, GLuint* m_texsmallball);
    void CreateBalls() override;
};

