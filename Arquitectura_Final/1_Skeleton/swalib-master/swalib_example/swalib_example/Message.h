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

class VertLimitWorldCollMsg : public CollisionMsg
{

};

class HorLimitWorldCollMsg : public CollisionMsg
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