#pragma once
#include "AbstractFactory.h"
class Lvl2Factory :
    public AbstractFactory
{
public:
  Lvl2Factory(int _numBalls, float _bigVel, float _medVel, float _smallVel, Entity::EntityType _starterType,
    GLuint& _texbigball, GLuint& _texmediumball, GLuint& _texsmallball, GLuint& _texPlayer, vec2 _playerSize, GLuint& _texWeapon, vec2 _weaponVel);
  
  void CreateBalls() override;
};

