#include "Framework.h"

MainObject::MainObject()
{
}

MainObject::~MainObject()
{
	for (int i = 0; i < MAX_ITEM_NUM; i++)
	{
		delete items[i];
	}
	delete model;
	delete collider;
}

void MainObject::MineObject(SphereCollider* sphere)
{
	if (!sphere->IsActive()) return;

	if (collider->IsSphereCollision(sphere))
	{
		DropItem(sphere->GetGlobalPosition());
		sphere->SetActive(false);
	}

	
}

bool MainObject::IsJorneyCollision(Jorney*& jorney)
{
	if (collider->IsCapsuleCollision(jorney))
	{
		collider->SetColor(1, 0, 0);
		if (SphereCollider* sphere = dynamic_cast<SphereCollider*>(collider))
			PushJorneyToSphereCollider(sphere, jorney);
		else if (BoxCollider* box = dynamic_cast<BoxCollider*>(collider))
			PushJorneyToBoxCollider(box, jorney);
			
		return true;
	}
	collider->SetColor(0, 1, 0);
	return false;
}


void MainObject::Update(BoxCollider*& floor, Jorney*& jorney)
{
	UpdateWorld();
	model->UpdateWorld();
	collider->UpdateWorld();

	for (int i = 0; i < MAX_ITEM_NUM; i++)
	{
		if (!items[i]->IsActive())	continue;

		items[i]->Update(floor, jorney);
	}

	//조니 getweapon 해서 mineobject하기!
	IsJorneyCollision(jorney);
	MineObject(jorney->GetWeapon());
}

void MainObject::Render()
{
	for (int i = 0; i < MAX_ITEM_NUM; i++)
	{
		if (!items[i]->IsActive())	continue;

		items[i]->Render();
	}
	model->Render();
	collider->Render();
}

void MainObject::Edit()
{
	Transform::Edit();
	collider->SetTag("MainCollider");
	collider->Edit();
	model->SetTag("MainModel");
	model->Edit();
}

void MainObject::Init()
{
	CreateItems();
	CreateModel();
	CreateCollider();

	model->SetParent(this);
	collider->SetParent(this);
	UpdateWorld();
	model->UpdateWorld();
	collider->UpdateWorld();
}

void MainObject::DropItem(Vector3 jorneyPos)
{
	for (ObjectItem* item : items)
	{
		if (item->IsActive()) continue;

		item->SpawnItem(jorneyPos);
		return;
	}
}

void MainObject::PushJorneyToBoxCollider(BoxCollider* box, Jorney*& jorney)
{
	Vector3 boxCenter = box->GetGlobalPosition();
	Vector3 boxHalfSize = box->GetSize() * 0.5f;

	CapsuleCollider* capsule = jorney;
	Vector3 capsuleCenter = (capsule->GetStartPoint() + capsule->GetEndPoint()) * 0.5f;

	Vector3 delta = capsuleCenter - boxCenter;
	delta.y = 0;

	float dx = std::abs(delta.x) - boxHalfSize.x;
	float dz = std::abs(delta.z) - boxHalfSize.z;

	dx = max(0.0f, dx);
	dz = max(0.0f, dz);

	float distanceToBox = sqrtf(dx * dx + dz * dz);

	float capsuleRadius = capsule->Radius();
	float minDist = capsuleRadius;

	if (distanceToBox < minDist)
	{
		float pushAmount = minDist - distanceToBox + 0.001f;

		// 부호를 유지한 방향으로 밀기
		float signX = (delta.x >= 0) ? 1.0f : -1.0f;
		float signZ = (delta.z >= 0) ? 1.0f : -1.0f;

		Vector3 pushDir = Vector3(dx * signX, 0, dz * signZ);

		if (pushDir.Length() > 0.0001f)
		{
			pushDir.Normalize();
			jorney->SetLocalPosition(jorney->GetLocalPosition() + pushDir * pushAmount);
		}
	}
}


void MainObject::PushJorneyToSphereCollider(SphereCollider* sphere, Jorney*& jorney)
{
	Vector3 sphereCenter = sphere->GetGlobalPosition();
	CapsuleCollider* capsule = jorney;
    Vector3 capsuleStart = capsule->GetStartPoint();
    Vector3 capsuleEnd = capsule->GetEndPoint();
    float capsuleRadius = capsule->Radius();

    Vector3 closestPoint = GameMath::ClosestPointOnLineSegment(sphereCenter, capsuleStart, capsuleEnd);

    Vector3 dir = closestPoint - sphereCenter;
    float dist = dir.Length();
    float minDist = capsuleRadius + sphere->Radius();
	dir.Normalize();
	dir.y = 0;
    if (dist < minDist && dist > 0.0001f)
    {
        float pushAmount = minDist - dist + 0.001f;
        jorney->SetLocalPosition(jorney->GetLocalPosition() + dir * pushAmount);
    }
}

