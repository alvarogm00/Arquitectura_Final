#include "Entity.h"
#include "Component.h"

Entity::Entity()
{
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
		(*compIt)->ReceiveMessage(msg);
	}
}
