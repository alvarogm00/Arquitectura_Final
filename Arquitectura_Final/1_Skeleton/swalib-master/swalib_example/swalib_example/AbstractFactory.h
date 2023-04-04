#pragma once
#include "../../common/Entity.h"
#include "../../common/stdafx.h"
#include <vector>

class AbstractFactory
{
protected:
	unsigned int numBalls;
	float m_bigVel;
	float m_medVel;
	float m_smallVel;

	GLuint m_texbigball;
	GLuint m_texmediumball;
	GLuint m_texsmallball;
	Entity::EntityType starterType;

	GLuint m_texPlayer;
	vec2 m_playerSize;

	GLuint m_texWeapon;
	vec2 m_weaponVel;
	//std::vector<Entity*> m_entitites;
	//std::vector<Entity*> m_initEntities;
	//std::vector<Entity*> m_sedondaryEntities;
public:
	virtual void CreateBalls() = 0;
	
	void CreatePlayer();
	int GetNumBalls();
};

