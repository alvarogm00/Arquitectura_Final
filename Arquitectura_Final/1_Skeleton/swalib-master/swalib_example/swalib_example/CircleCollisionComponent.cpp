#include "CircleCollisionComponent.h"
#include "../../common/GameLogic.h"
#include "MovementComponent.h"

CircleCollisionComponent::CircleCollisionComponent(float _radius)
{
    radius = _radius;
}

void CircleCollisionComponent::Slot()
{
	bool collision = false;
	std::vector<Entity*> entities = CGameLogic::instance()->GetEntitiesArray();
	vec2 vel = m_Owner->FindComponent<MovementComponent>()->GetVelocity();

	for (size_t i = 0; i < entities.size(); i++)
	{
		if(entities[i] != this->m_Owner && entities[i]->GetIsActive())
			collision = entities[i]->FindComponent<CollisionComponent>()->collides(*this);

		if (collision)
		{
			if (entities[i]->GetType() == Entity::PROYECTILE)
			{
				RecieveMessage(projMsg);
				entities[i]->ReceiveMessage(ballMsg);
			}
			else if (entities[i]->GetType() == Entity::PLAYER)
			{
				if(m_Owner->GetType() == Entity::BIG_BALL || m_Owner->GetType() == Entity::MEDIUM_BALL || m_Owner->GetType() == Entity::SMALL_BALL)
					entities[i]->ReceiveMessage(ballMsg);
			}
			else
				collision = false;
		}
	}

	// Rebound on margins.
	if ((newPos.x > SCR_WIDTH) || (newPos.x < 0)) {
		//vel *= -1.0;
		m_Owner->ReceiveMessage(horLimitMsg);
	}
	else if ((newPos.y > SCR_HEIGHT) || (newPos.y < 0)) {
		//vel *= -1.0;
		m_Owner->ReceiveMessage(vertLimitMsg);
	}
	else if (!collision) {
		m_Owner->SetPosition(newPos);
	}
}

void CircleCollisionComponent::RecieveMessage(Message* _msg)
{
	ProjectileCollisionMsg* projMsg = dynamic_cast<ProjectileCollisionMsg*>(_msg);
	VertLimitWorldCollMsg* vertMsg = dynamic_cast<VertLimitWorldCollMsg*>(_msg);
	BallCollisionMsg* ballMsg = dynamic_cast<BallCollisionMsg*>(_msg);
	NewPosMsg* newPosMsg = dynamic_cast<NewPosMsg*>(_msg);

	if (newPosMsg)
	{
		SetNewPosition(newPosMsg->newPos);
	}
	else if (projMsg)
	{
		if (m_Owner->GetType() == Entity::BIG_BALL)
		{
			CGameLogic::instance()->ActivateBalls(Entity::MEDIUM_BALL, *m_Owner->GetPosition());
			m_Owner->SetIsActive(false);
		}
		else if (m_Owner->GetType() == Entity::MEDIUM_BALL)
		{
			CGameLogic::instance()->ActivateBalls(Entity::SMALL_BALL, *m_Owner->GetPosition());
			m_Owner->SetIsActive(false);
		}
		else if (m_Owner->GetType() == Entity::SMALL_BALL)
		{
			m_Owner->SetIsActive(false);
			CGameLogic::instance()->CheckGameState();
		}
	}
	else if (vertMsg)
	{
		if (m_Owner->GetType() == Entity::PROYECTILE)
		{
			m_Owner->SetIsActive(false);
		}
	}
	else if (ballMsg)
	{
		if (m_Owner->GetType() == Entity::PROYECTILE)
		{
			m_Owner->SetIsActive(false);
		}
	}
}

bool CircleCollisionComponent::collides(const CollisionComponent& other) const
{
    return other.collides(m_position, radius);
}

bool CircleCollisionComponent::collides(vec2& circlePos, float circleRadius) const
{
    return checkCircleCircle(m_position, radius, circlePos, circleRadius);
}

bool CircleCollisionComponent::collides(const vec2& rectPos, const vec2& rectSize) const
{
    return checkCircleRect(m_position, radius, rectPos, rectSize);
}

void CircleCollisionComponent::SetRadius(float _radius)
{
	radius = _radius;
}

float CircleCollisionComponent::GetRadius()
{
	return radius;
}

