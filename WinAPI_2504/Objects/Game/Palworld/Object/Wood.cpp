#include "Framework.h"

Wood::Wood():ObjectItem(0.7)
{
	tag = "WoodCollider";
	Init();
}

Wood::~Wood()
{
}

void Wood::CreateModel()
{
	model = new Model("Wood");
	model->SetLocalScale(0.4, 0.4, 0.4);
}

void Wood::SetItemType()
{
	type = ItemType::Wood;
}

void Wood::SetItemData()
{
	data = DataManager::Get()->GetItem(1002);
}
