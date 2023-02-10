#pragma once
#include "../../common/Entity.h"
#include "../../common/stdafx.h"
#include <vector>

class AbstractFactory
{
protected:
	unsigned int numBalls;

	GLuint* _texbigball;
	GLuint* _texmediumball;
	GLuint* _texsmallball;

	//std::vector<Entity*> m_entitites;
	//std::vector<Entity*> m_initEntities;
	//std::vector<Entity*> m_sedondaryEntities;
public:
	virtual void CreateBalls() = 0;
	virtual void CreatePlayer();
};

