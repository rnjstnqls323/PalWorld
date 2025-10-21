#include "Framework.h"

Tree::Tree():MainObject()
{
	tag = "Tree";
	Init();
	//model->SetLocalPosition(0, -5, 0);

	UpdateWorld();
	model->UpdateWorld();
}

void Tree::Update()
{
	UpdateWorld();
	model->UpdateWorld();
	collider->UpdateWorld();
}


void Tree::CreateItems()
{
	items.resize(MAX_ITEM_NUM);
	for (int i = 0; i < MAX_ITEM_NUM; i++)
	{
		items[i] = new Wood();
		items[i]->SetActive(false);
	}
}

void Tree::CreateModel()
{
	model = new Model("Tree");
	model->SetLocalScale(30, 30, 30);
	model->UpdateWorld();
}

void Tree::CreateCollider()
{
	collider = new BoxCollider(Vector3(1.5,4,1.5));
	collider->SetLocalPosition(0, 2, 0);
	collider->UpdateWorld();
}
