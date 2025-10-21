#include "Framework.h"

SmallRock::SmallRock():ObjectItem(0.7)
{
	tag = "SmallRockCollider";
	Init();
}

SmallRock::~SmallRock()
{
}

void SmallRock::CreateModel()
{
	model = new Model("SmallRock");
	model->SetLocalPosition(0, 0, 0.4);
}

void SmallRock::SetItemType()
{
	type = ItemType::SmallRock;
}
