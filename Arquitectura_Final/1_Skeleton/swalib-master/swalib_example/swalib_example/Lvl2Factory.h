#pragma once
#include "AbstractFactory.h"
class Lvl2Factory :
    public AbstractFactory
{
    Lvl2Factory(int _numBalls, float m_bigVel, float m_medVel, float m_smallVel, Entity::EntityType _starterType, 
        GLuint& _texbigball, GLuint& _texmediumball, GLuint& _texsmallball);
    void CreateBalls() override;
};

