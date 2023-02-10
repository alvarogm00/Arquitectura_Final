#include "CircleCollisionComponent.h"
#include "../../common/GameLogic.h"

CircleCollisionComponent::CircleCollisionComponent(float _radius)
{
    radius = _radius;
}

void CircleCollisionComponent::Slot()
{
	bool collision = false;
	std::vector<Entity*> entities = CGameLogic::instance()->GetPlayerEntitiesArray();
	vec2 vel = *m_Owner->FindComponent<MovementComponent>()->GetVelocity();

	for (size_t i = 0; i < entities.size(); i++)
	{
		collision = entities[i]->FindComponent<CollisionComponent>()->collides(*this);

		if (collision)
		{
			if (entities[i]->GetType() == Entity::PROYECTILE)
			{
				RecieveMessage(projMsg);
			}
			else if (entities[i]->GetType() == Entity::PLAYER)
			{
				entities[i]->ReceiveMessage(ballMsg);
			}
		}
	}

	if (!collision) {
		pos = newPos;
	}
	else {
		// Rebound!
		vel = vel * -1.0f;
		//if (otherEntity.GetType() == Entity::BIG_BALL)
		//	m_Owner->ReceiveMessage(projMsg);
		//else if (otherEntity.GetType() == Entity::PLAYER)
		//	otherEntity.ReceiveMessage(ballMsg);
	}

	// Rebound on margins.
	if ((pos.x > SCR_WIDTH) || (pos.x < 0)) {
		//vel *= -1.0;
		m_Owner->ReceiveMessage(horLimitMsg);
	}
	if ((pos.y > SCR_HEIGHT) || (pos.y < 0)) {
		//vel *= -1.0;
		m_Owner->ReceiveMessage(vertLimitMsg);
	}
}

void CircleCollisionComponent::RecieveMessage(Message* _msg)
{
	ProjectileCollisionMsg* projMsg = dynamic_cast<ProjectileCollisionMsg*>(_msg);
	VertLimitWorldCollMsg* vertMsg = dynamic_cast<VertLimitWorldCollMsg*>(_msg);

	if (projMsg)
	{
		if (m_Owner->GetType() == Entity::BIG_BALL)
		{
			CGameLogic::instance()->CreateBalls(Entity::MEDIUM_BALL, *m_Owner->FindComponent<CollisionComponent>()->GetPosition());
			m_Owner->SetIsActive(false);
		}
		else if (m_Owner->GetType() == Entity::MEDIUM_BALL)
		{
			CGameLogic::instance()->CreateBalls(Entity::SMALL_BALL, *m_Owner->FindComponent<CollisionComponent>()->GetPosition());
			m_Owner->SetIsActive(false);
		}
		else if (m_Owner->GetType() == Entity::SMALL_BALL)
		{
			m_Owner->SetIsActive(false);
		}
	}
	else if (vertMsg)
	{
		if (m_Owner->GetType() == Entity::PROYECTILE)
		{
			m_Owner->SetIsActive(false);
		}
	}
}

bool CircleCollisionComponent::collides(const CollisionComponent& other) const
{
    return other.collides(pos, radius);
}

bool CircleCollisionComponent::collides(vec2& circlePos, float circleRadius) const
{
    return checkCircleCircle(pos, radius, circlePos, circleRadius);
}

bool CircleCollisionComponent::collides(const vec2& rectPos, const vec2& rectSize) const
{
    return checkCircleRect(pos, radius, rectPos, rectSize);
}

void CircleCollisionComponent::SetRadius(float _radius)
{
	radius = _radius;
}

float CircleCollisionComponent::GetRadius()
{
	return radius;
}
