#pragma once
#include <vector>
#include "../swalib_example/swalib_example/Message.h"
//#include "Component.h"

class Component;
class Entity
{
protected:
	vec2 m_pos; 
	vec2 m_size;

	std::vector<Component*> m_Components;
	float elapsedTime;
	bool isActive;

public:
	enum EntityType { BIG_BALL, MEDIUM_BALL, SMALL_BALL, PLAYER, PROYECTILE };
	EntityType type;

	Entity(EntityType _type);
	~Entity();

	void AddComponent(Component* _component);

	void SetElapsedTime(float _elapsedTime);
	float GetElapsedTime();

	void SetPosition(vec2& _pos);
	vec2* GetPosition();

	void SetSize(vec2& _size);
	vec2* GetSize();

	void SetType(EntityType _type);
	EntityType GetType();

	void SetIsActive(bool _isActive);
	bool GetIsActive();

	void Slot();
	void ReceiveMessage(Message* msg);

	template <class T>
	T* FindComponent();
};

template<class T>
inline T* Entity::FindComponent()
{
	for (auto compIt = m_Components.begin(); compIt != m_Components.end(); ++compIt)
	{
		T* comp = dynamic_cast<T*>(*compIt);
		if (comp)
			return comp;
	}
	return NULL;
}
