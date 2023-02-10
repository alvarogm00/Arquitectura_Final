#include "Component.h"

Component::Component()
{
}

Component::~Component()
{
}

void Component::SetOwner(Entity* _owner)
{
	m_Owner = _owner;
}
