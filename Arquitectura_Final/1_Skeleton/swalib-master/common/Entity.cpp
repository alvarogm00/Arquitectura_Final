#include "Entity.h"
#include "../swalib_example/swalib_example/Component.h"
#include "../swalib_example/swalib_example/MovementComponent.h"
#include "GameLogic.h"

Entity::Entity(EntityType _type)
{
	m_pos = vec2(0, 0);
	m_size = vec2(0, 0);

	type = _type;
}

Entity::~Entity()
{
	m_Components.clear();
}

void Entity::AddComponent(Component* _component)
{	
	_component->SetOwner(this);
	m_Components.push_back(_component);
}

void Entity::SetElapsedTime(float _elapsedTime)
{
	elapsedTime = _elapsedTime;
	FindComponent<MovementComponent>()->SetElapsedTime(_elapsedTime);
}

float Entity::GetElapsedTime()
{
	return elapsedTime;
}

void Entity::SetPosition(vec2& _pos)
{
	m_pos = _pos;
}

vec2* Entity::GetPosition()
{
	return &m_pos;
}

void Entity::SetSize(vec2& _size)
{
	m_size = _size;
}

vec2* Entity::GetSize()
{
	return &m_size;
}

void Entity::SetType(EntityType _type)
{
	type = _type;
}

Entity::EntityType Entity::GetType()
{
	return type;
}

void Entity::SetIsActive(bool _isActive)
{
	isActive = _isActive;
}

bool Entity::GetIsActive()
{
	return isActive;
}

void Entity::Slot()
{
	for (size_t i = 0; i < m_Components.size(); i++)
	{
		m_Components[i]->Slot();
	}
}

void Entity::ReceiveMessage(Message* msg)
{
	for (auto compIt = m_Components.begin(); compIt != m_Components.end(); ++compIt)
	{
		(*compIt)->RecieveMessage(msg);
	}
}
