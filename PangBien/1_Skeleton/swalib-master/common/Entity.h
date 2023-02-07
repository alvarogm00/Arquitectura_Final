#pragma once
#include <vector>
#include "../swalib_example/swalib_example/Message.h"
//#include "Component.h"

class Component;
class Entity
{
protected:
	std::vector<Component*> m_Components;
	float elapsedTime;

public:
	Entity();
	~Entity();
	void AddComponent(Component* _component);
	void SetElapsedTime(float _elapsedTime);
	float GetElapsedTime();
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
