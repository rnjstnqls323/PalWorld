#include "Framework.h"

Rock::Rock():MainObject()
{
	tag = "Rock";
	Init();

	Load();
	UpdateWorld();
	model->UpdateWorld();
	collider->UpdateWorld();
} 

Rock::~Rock()
{
}
void Rock::CreateItems()
{
	items.resize(MAX_ITEM_NUM);
	for (int i = 0; i < MAX_ITEM_NUM;i++)
	{
		items[i] = new SmallRock();
		items[i]->SetActive(false);
	}
}

void Rock::CreateModel()
{
	model = new Model("Rock");
	model->SetLocalPosition(1, -6, 0);
	model->UpdateWorld();
}

void Rock::CreateCollider()
{
	collider = new SphereCollider(50);
	collider->UpdateWorld();
}
