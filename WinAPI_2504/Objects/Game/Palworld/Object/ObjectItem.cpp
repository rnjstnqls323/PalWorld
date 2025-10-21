#include "Framework.h"

ObjectItem::ObjectItem()
{
}

ObjectItem::ObjectItem(float size):SphereCollider(size)
{
}

ObjectItem::~ObjectItem()
{
	delete model;
}

void ObjectItem::SpawnItem(Vector3 parentPos)
{
	isFloor = false;
}

void ObjectItem::Update(BoxCollider* floor, Jorney* jorney)
{	
	if (localPosition.y < 0)SetLocalPosition(localPosition.x, 1, localPosition.z);
	if (isFloor) return;
	RigidBody();
	isFloor = IsCollisionToFloor(floor);

	UpdateWorld();
	model->UpdateWorld();

}

void ObjectItem::Render()
{
	SphereCollider::Render();
	model->Render();
}

void ObjectItem::Edit()
{
	SphereCollider::Edit();
	model->Edit();
}

void ObjectItem::Init()
{
	SetItemType();
	CreateModel();
	model->SetParent(this);
	UpdateWorld();
	model->UpdateWorld();
}


bool ObjectItem::IsCollisionToFloor(BoxCollider* floor)
{
	Ray ray(localPosition, Vector3(0, -1, 0));
	RayHit hit;

	if (floor->IsRayCollision(ray, &hit))
	{
		float distance = (hit.position - localPosition).Length();

		if (distance < 0.2f) // 캐릭터 높이에 맞게 설정
		{
			localPosition.y = hit.position.y + 0.1f;
			SetLocalPosition(localPosition);
			return true;
		}
	}

	return false;
}

bool ObjectItem::IsCollisionToJorney(Jorney* jorney)
{
	//조니랑 닿으면 인벤들어가는거 구현하기~!
	return false;
}

void ObjectItem::RigidBody()
{
	if (isFloor) return;
	velocity.y -= GRAVITY * DELTA;
	localPosition.y += velocity.y * DELTA;

	SetLocalPosition(localPosition);
}

