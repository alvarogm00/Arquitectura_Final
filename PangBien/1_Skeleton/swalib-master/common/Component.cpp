#include "Component.h"
#include "GameLogic.h"
#include "Entity.h"
#include "Renderer.h"

CollisionComponent::CollisionComponent(float _radius, int _id)
{
	radius = _radius;
	id = _id;
	entMsg = new EntCollisionMsg();
	limitMsg = new LimitWorldCollMsg();
}

void CollisionComponent::SetIndex(int _id)
{
	id = _id;
}

int CollisionComponent::GetIndex() const
{
	return id;
}

void CollisionComponent::SetRadius(float _radius)
{
	radius = _radius;
}

float CollisionComponent::GetRadius() const
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

void CollisionComponent::Slot()
{
	const int numBalls = CGameLogic::instance()->GetNumBalls();
	std::vector<Entity> entities = *CGameLogic::instance()->GetEntitiesArray();

	vec2 vel = m_Owner->FindComponent<MovementComponent>()->GetVelocity();

	bool collision = false;
	int colliding_ball = -1;
	for (int j = 0; j < numBalls; j++)
	{
		if (id != j)
		{
			vec2 otherPos = entities[j].FindComponent<CollisionComponent>()->pos;
			vec2 otherVel = entities[j].FindComponent<MovementComponent>()->GetVelocity();
			float otherRadius = entities[j].FindComponent<CollisionComponent>()->radius;
			if (newPos + vel != otherPos + otherVel) {
				float limit2 = (radius + otherRadius) * (radius + otherRadius);
				if (vlen2(newPos - otherPos) <= limit2) {
					collision = true;
					colliding_ball = j;
					break;
				}
			}
		}
	}

	if (!collision) {
		pos = newPos;
		//m_Owner->FindComponent<RenderComponent>()->SetPos(pos);
	}
	else {
		// Rebound!
		vel = vel * -1.0f;
		entities[colliding_ball].FindComponent<MovementComponent>()->GetVelocity() *= -1;
		//m_Owner->FindComponent<MovementComponent>()->SetVelocity(vel);
		m_Owner->ReceiveMessage(entMsg);
	}

	// Rebound on margins.
	if ((pos.x > SCR_WIDTH) || (pos.x < 0)) {
		vel.x *= -1.0;
		m_Owner->ReceiveMessage(limitMsg);
		//m_Owner->FindComponent<MovementComponent>()->SetVelocity(vel);
	}
	if ((pos.y > SCR_HEIGHT) || (pos.y < 0)) {
		vel.y *= -1.0;
		m_Owner->ReceiveMessage(limitMsg);
		//m_Owner->FindComponent<MovementComponent>()->SetVelocity(vel);
	}
}

void CollisionComponent::ReceiveMessage(Message* msg)
{
	NewPosMsg* npMsg = dynamic_cast<NewPosMsg*>(msg);
	if (npMsg)
		newPos = (npMsg->newPos);
}

MovementComponent::MovementComponent(vec2 _pos, vec2 _vel)
{
	pos = _pos;
	vel = _vel;
	newPosMsg = new NewPosMsg();
}

void MovementComponent::Slot()
{
	pos = pos + vel * elapsedTime;//m_Owner->GetElapsedTime();
	//m_Owner->FindComponent<CollisionComponent>()->SetPos(pos);
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
