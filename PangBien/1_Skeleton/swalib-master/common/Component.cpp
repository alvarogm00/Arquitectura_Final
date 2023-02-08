#include "Component.h"
#include "GameLogic.h"
#include "Entity.h"
#include "Renderer.h"

CollisionComponent::CollisionComponent()
{
	projMsg = new ProjectileCollisionMsg();
	limitMsg = new LimitWorldCollMsg();
}

void CircleCollision::SetRadius(float _radius)
{
	radius = _radius;
}

float CircleCollision::GetRadius() const
{
	return radius;
}

void CollisionComponent::SetPos(vec2& _newPos)
{
	newPos = _newPos;
}

vec2* CollisionComponent::GetPosition()
{
	return &pos;
}

void RectCollision::SetSize(vec2& _size)
{
	size = _size;
}

vec2* RectCollision::GetSize()
{
	return &size;
}

float CollisionComponent::Clamp(float _value, float _minvalue, float _maxValue)
{
	if (_value < _minvalue)
	{
		_value = _minvalue;
	}
	else if (_value > _maxValue)
	{
		_value = _maxValue;
	}
	else
		_value = _value;

	return _value;
}


void CollisionComponent::Slot()
{
}

void CollisionComponent::ReceiveMessage(Message* msg)
{
	NewPosMsg* npMsg = dynamic_cast<NewPosMsg*>(msg);
	if (npMsg)
		newPos = (npMsg->newPos);
}

bool CollisionComponent::checkCircleCircle(const vec2& pos1, float radius1, const vec2& pos2, float radius2)
{
	float distance = vlen2(pos1 - pos2);
	float radiusSum = radius1 + radius2;
	if (distance < radiusSum)
		return true;
	else
		return false;
}

bool CollisionComponent::checkCircleRect(const vec2& circlePos, float circleRadius, const vec2& rectPos, const vec2& rectSize)
{
	float closestX = CollisionComponent::Clamp(circlePos.x, rectPos.x, (rectPos.x + rectSize.x));
	float closestY = CollisionComponent::Clamp(circlePos.y, rectPos.y, (rectPos.y + rectSize.y));

	vec2 closestPos(closestX, closestY);
	float shortestDistance = vlen2(closestPos - circlePos);
	if (shortestDistance < circleRadius)
	{
		return true;
	}
	else
		return false;
}

void CircleCollision::Slot()
{
	//const int numBalls = CGameLogic::instance()->GetNumBalls();

	//int colliding_ball = -1;
	//Entity otherEntity;

	bool collision = false;
	std::vector<Entity> entities = *CGameLogic::instance()->GetPlayerEntitiesArray();
	vec2 vel = m_Owner->FindComponent<MovementComponent>()->GetVelocity();

	for (size_t i = 0; i < entities.size(); i++)
	{
		collision = entities[i].FindComponent<CollisionComponent>()->collides(*this);
		if (collision)
		{
			if (entities[i].GetType() == Entity::PROYECTILE)
			{
				m_Owner->ReceiveMessage(projMsg);
			}
			else if (entities[i].GetType() == Entity::PLAYER)
			{
				entities[i].ReceiveMessage(ballMsg);
			}
		}
		/*vec2 otherPos = *entities[i].FindComponent<CollisionComponent>()->GetPosition();
		float otherRadius = entities[i].FindComponent<CollisionComponent>()->GetRadius();
		vec2 otherVel = entities[i].FindComponent<MovementComponent>()->GetVelocity();

		if (newPos + vel != otherPos + otherVel)
		{
			float limit2 = (radius + otherRadius) * (radius + otherRadius);
			if (vlen2(newPos - otherPos) <= limit2)
			{
				collision = true;
				otherEntity = entities[i];
				break;
			}

		}*/
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
		vel *= -1.0;
		m_Owner->ReceiveMessage(limitMsg);
	}
	if ((pos.y > SCR_HEIGHT) || (pos.y < 0)) {
		vel *= -1.0;
		m_Owner->ReceiveMessage(limitMsg);
	}
}

bool CircleCollision::collides(const CollisionComponent& other) const
{
	return other.collides(pos, radius);
}

bool CircleCollision::collides(const vec2& circlePos, float circleRadius) const
{
	return checkCircleCircle(pos, radius, circlePos, circleRadius);
}

bool CircleCollision::collides(const vec2& rectPos, const vec2& rectSize) const
{
	return checkCircleRect(pos, radius, rectPos, rectSize);
}

bool RectCollision::collides(const CollisionComponent& other) const
{
	return other.collides(pos, size);
}

bool RectCollision::collides(const vec2& circlePos, float circleRadius) const
{
	return checkCircleRect(circlePos, circleRadius, pos, size);
}

bool RectCollision::collides(const vec2& rectPos, const vec2& rectSize) const
{
	return false;
}

MovementComponent::MovementComponent(vec2 _pos, vec2 _vel)
{
	pos = _pos;
	vel = _vel;
	newPosMsg = new NewPosMsg();
}

void MovementComponent::Slot()
{
	pos = pos + vel * elapsedTime;
	newPosMsg->newPos = pos;
	m_Owner->ReceiveMessage(newPosMsg);
}

void MovementComponent::SetVelocity(vec2& _vel)
{
	vel = _vel;
}

vec2 MovementComponent::GetVelocity()
{
	return vel;
}

void MovementComponent::SetPosition(vec2& _pos)
{
	pos = _pos;
}

vec2* MovementComponent::GetPosition()
{
	return &pos;
}

void MovementComponent::SetElapsedTime(float _elapsedTime)
{
	elapsedTime = _elapsedTime;
}

void MovementComponent::ReceiveMessage(Message* msg)
{
	EntCollisionMsg* entMsg = dynamic_cast<EntCollisionMsg*>(msg);
	LimitWorldCollMsg* limitMsg = dynamic_cast<LimitWorldCollMsg*>(msg);

	if (entMsg || limitMsg)
		vel *= -1;
}

RenderComponent::RenderComponent(GLuint& _gfx, vec2& _size, CSprite* _sprite)
{
	gfx = _gfx;
	pos = vec2(0, 0);
	SetSize(_size);
	sprite = new CSprite(vec2(0, 0), vec2(0, 0), 0);
	sprite->SetGfx(gfx);
	sprite->SetPos(pos);
	sprite->SetSize(size);
	CRenderer::instance()->SetSprite(0, sprite);

}

void RenderComponent::SetSize(vec2& _size)
{
	size = _size;
}

void RenderComponent::SetGfx(GLuint& _gfx)
{
	gfx = _gfx;
}

void RenderComponent::SetPos(vec2& _pos)
{
	pos = _pos;
	sprite->SetPos(pos);
}

vec2 RenderComponent::GetPos()
{
	return pos;
}


void RenderComponent::ReceiveMessage(Message* msg)
{
	NewPosMsg* npMsg = dynamic_cast<NewPosMsg*>(msg);
	if (npMsg)
		SetPos(npMsg->newPos);
}

void RenderComponent::Slot()
{
}

void RenderComponent::End()
{
	CORE_UnloadPNG(gfx);
}

void Component::SetOwner(Entity* _owner)
{
	m_Owner = _owner;
}

Component::Component()
{
}