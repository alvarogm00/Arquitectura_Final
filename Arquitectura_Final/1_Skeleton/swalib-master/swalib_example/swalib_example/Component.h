#pragma once
#include "../../common/Entity.h"
#include "Message.h"

class Component
{
protected: 
	Entity* m_Owner;

public: 
	Component();
	virtual ~Component();

	void SetOwner(Entity* _owner);

	virtual void Slot() = 0;
	virtual void RecieveMessage(Message* _msg) = 0;
};

