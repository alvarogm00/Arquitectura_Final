#pragma once
#include "../../common/vector2d.h"

class Message
{
protected:
	virtual ~Message();
};

class CollisionMsg : public Message
{
public:
	vec2 pos; 
	vec2 vel;
};

class EntCollisionMsg : public CollisionMsg
{

};

class LimitWorldCollMsg : public CollisionMsg
{

};

class NewPosMsg : public Message
{
public:
	vec2 newPos;
};

class ProjectileCollisionMsg : public Message
{

};

class BallCollisionMsg : public Message
{

};