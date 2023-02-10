#pragma once
#include "Component.h"
class MovementComponent : public Component
{
	vec2 vel;	// Velocity.
	vec2 pos;
	float elapsedTime;
	NewPosMsg* newPosMsg;

public:
	MovementComponent(vec2 _pos, vec2 vel);

	void SetVelocity(vec2& _vel);
	vec2 GetVelocity();
	void SetPosition(vec2& _pos);
	vec2* GetPosition();
	void SetElapsedTime(float _elapsedTime);

	virtual void Slot() override;
	virtual void RecieveMessage(Message* msg) override;
};

