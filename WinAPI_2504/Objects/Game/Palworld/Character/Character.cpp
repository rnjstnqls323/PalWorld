#include "Framework.h"

Character::Character()
{
}
Character::Character(float radius, float height):CapsuleCollider(radius, height)
{
}

Character::~Character()
{
	delete model;
}


void Character::Update(BoxCollider* floor)
{
	Move();
	if (localPosition.y < Radius() + (this->Height() / 2.0f)) localPosition.y = Radius() + (this->Height() / 2.0f) + 0.3f;
	if (!isFloor)
	{
		RigidBody();
		isFloor = IsCollisionToFloor(floor);
	}
	

	model->Update();
	UpdateWorld();
	model->UpdateWorld();
}

void Character::Render()
{
	CapsuleCollider::Render();
	model->Render();
}

void Character::Edit()
{
	CapsuleCollider::Edit();
	model->Edit();
}

void Character::Init()
{
	CreateModel();
	SetStat();

	model->SetParent(this);

	SetLocalRotation(0, 180, 0);
	UpdateWorld();
	model->UpdateWorld();
}

void Character::PlayClip(size_t index)
{
	if (curIndex == index)
		return;
	curIndex = index;
	model->PlayClip(index);
}

void Character::Rotate()
{
	Vector3 lookDir = moveDir;
	lookDir.y = 0.0f;
	lookDir.Normalize();
	Vector3 forward = GetForward();
	forward.y = 0.0f;
	forward.Normalize();
	float dot = Vector3::Dot(forward, lookDir);
	dot = GameMath::Clamp(dot, -1.0f, 1.0f);
	float angle = acosf(dot);
	Vector3 cross = Vector3::Cross(forward, lookDir);

	if (cross.y < 0.0f)
		angle = -angle;

	Transform::Rotate(Vector3::Up(), angle * rotateSpeed * DELTA);
}


void Character::RigidBody()
{
	if (isFloor) return;
	velocity.y -= GRAVITY * DELTA;
	localPosition.y += velocity.y * DELTA;

	SetLocalPosition(localPosition);
}

bool Character::IsCollisionToFloor(BoxCollider* floor)
{
	if (floor->IsCapsuleCollision(this))
	{
		// 위치 보정: 캡슐 아래가 바닥 위에 올라가도록 조정
		Vector3 pos = GetLocalPosition();
		float halfHeight = this->Height() / 2.0f;
		pos.y = halfHeight+Radius();
		SetLocalPosition(pos);
		return true;
	}
	return false;
	//float capsuleHalfHeight = this->Height() / 2.0f;
	//float capsuleRadius = this->Radius(); // 캡슐 반지름
	//
	//// 발 위치 근처에서 Ray 시작
	//Vector3 footPos = localPosition - Vector3(0, -(capsuleHalfHeight + capsuleRadius), 0);
	//Ray ray(footPos, Vector3(0, -1, 0));
	//RayHit hit;
	//
	//if (floor->IsRayCollision(ray, &hit))
	//{
	//	float distance = (footPos - hit.position).Length();
	//
	//	// 너무 멀면 땅이 아님
	//	if (distance < 0.2f) // 접지 임계값
	//	{
	//		// 발이 바닥에 얹히게 위치 조정
	//		localPosition.y = hit.position.y + capsuleHalfHeight;
	//		SetLocalPosition(localPosition);
	//		return true;
	//	}
	//}
	//
	//return false;
}
