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
	//다시 잡자 
	isFloor = false;
	SetActive(true);
	Vector3 pos = CAM->GetGlobalPosition() - parentPos;
	pos.Normalize();

	SetLocalPosition(parentPos);
	//SetLocalPosition(localPosition + (pos* SPAWN_DISTANCE));

	UpdateWorld();
	model->UpdateWorld();

	isSpawn = true;
	spawnTime = 0.0f;
}

void ObjectItem::Update(BoxCollider*& floor, Jorney*& jorney)
{	
	if (localPosition.y < 0)SetLocalPosition(localPosition.x, 1, localPosition.z);
	if (isFloor) return;
	RigidBody();
	isFloor = IsCollisionToFloor(floor);


	//if(!isSpawn)
	//	IsCollisionToJorney(jorney);
	//else
	//{
	//	spawnTime += DELTA;
	//	if (spawnTime > 1.0f)
	//		isSpawn = false;
	//}

	//조니 닿으면 흡수
	IsCollisionToJorney(jorney);

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
	SetItemData();
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
	int key = data.key;
	EventManager::Get()->ExcuteEvent("AddItem",&key);
	SetActive(false);
	return false;
}

void ObjectItem::RigidBody()
{
	if (isFloor) return;
	velocity.y -= GRAVITY * DELTA;
	localPosition.y += velocity.y * DELTA;

	SetLocalPosition(localPosition);
}

