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
	if(collider->IsSphereCollision(sphere))
		DropItem(sphere->GetLocalPosition());
}

bool MainObject::IsJorneyCollision(Jorney* jorney)
{
	if (collider->IsCapsuleCollision(jorney))
	{
		// 1. 전체 방향 벡터 (수평 + 수직 포함)
		Vector3 toJorney = jorney->GetLocalPosition() - localPosition;

		if (toJorney.Length() > 0.0001f)
		{
			// 2. 방향 정규화
			toJorney.Normalize();

			// 3. 밀어내는 세기
			float pushStrength = 5.0f;

			// 4. 위치 보정
			Vector3 correctedPos = jorney->GetLocalPosition() + toJorney * pushStrength;

			jorney->SetLocalPosition(correctedPos);
		}

		return true;
	}

	return false;
}


void MainObject::Update(BoxCollider* floor, Jorney* jorney)
{
	for (int i = 0; i < MAX_ITEM_NUM; i++)
	{
		if (!items[i]->IsActive())	continue;

		items[i]->Update(floor, jorney);
	}
}

void MainObject::Render()
{
	model->Render();
	collider->Render();
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

		item->SetActive(true);
		item->SpawnItem(jorneyPos);
		return;
	}
}

