#include "Framework.h"

Inventory::Inventory()
{
	tag = "Inventory";

	CreateBackGround();
	localPosition = { 200,400,0 };

	UpdateWorld();
	backGround->UpdateWorld();

	
	
}

Inventory::~Inventory()
{
	delete backGround;
	delete button;
}

void Inventory::Render()
{
	button->Render();
	backGround->Render();
}

void Inventory::Update()
{
	UpdateWorld();
	backGround->UpdateWorld();
	button->Update();
}

void Inventory::AddItem(int key)
{
	if (items[key].first.itemStack)
	{
		items[key].second += 1;
		//��ư ������ �ִ��� num�ٱžߵǴµ� ��� �����ؾߵ���,,? �������ϰԳ�����?

	}
	else
	{

	}
}

void Inventory::SellItem(int key)
{
}

void Inventory::BuyItem(int key)
{
}

void Inventory::Edit()
{
	Transform::Edit();
	button->Edit();
	button->RenderTexture();
}


void Inventory::UpdateInventory()
{
}

void Inventory::CreateBackGround()
{
	backGround = new Quad(L"Resources/Textures/UI/Inventory/Inventory_BackGround.jpg");
	backGround->SetLocalScale(0.5f, 0.5f, 0.5f);
	backGround->SetParent(this);
}

void Inventory::CreateButtons()
{
	buttons.resize(MAX_BUTTON_NUM - DataManager::Get()->GetStackItemCount());
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i] = new InventoryButton(1001);
		button->SetActive(false);
	}

	for (int i = 0; i < DataManager::Get()->GetItemCount(); i++)
	{
		if (!DataManager::Get()->GetItem(1000 + i).itemStack) continue;
		//��ư �������ֱ�
	}
}
