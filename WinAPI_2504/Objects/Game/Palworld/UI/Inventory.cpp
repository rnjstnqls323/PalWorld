#include "Framework.h"

Inventory::Inventory()
{
	tag = "Inventory";

	CreateBackGround();
	CreateItems();
	CreateButtons();

	localPosition = { 200,400,0 };


	UpdateWorld();
	backGround->UpdateWorld();
	
	SetEventFunc();
}

Inventory::~Inventory()
{
	delete backGround;
	for (auto& pair : stackButtons)
	{
		delete pair.second;
	}
	for (ItemButton* button : buttons)
	{
		delete button;
	}
}

void Inventory::Render()
{
	if (!isOn) return;
	for (auto& pair : stackButtons)
	{
		if (!pair.second->IsActive()) continue;
		pair.second->Render();
	}
	for (ItemButton* button : buttons)
	{
		if (!button->IsActive()) continue;
		button->Render();
	}

	if(choiceItem != nullptr)
		choiceItemButton->Render();

	backGround->Render();
}

void Inventory::Update()
{
	for (auto& pair : stackButtons)
	{
		pair.second->Update();
	}
	for (ItemButton* button : buttons)
	{
		button->Update();
	}

	choiceItemButton->Update();
	UpdateWorld();
	backGround->UpdateWorld();

	if (bagWeight == MAX_BAG_WEIGHT)
		color = { 255,0,0,255 };
	else
		color = { 0,0,0,255 };
}

bool Inventory::AddItem(int key)
{

	if (items[key]->GetItemData().itemStack)
	{
		if (items[key]->GetItemCount() == 0 && buttonCount != MAX_BUTTON_COUNT)
		{
			//버튼 호출
			SpawnButton(stackButtons[key]);
			buttonCount++;
		}

	}
	else
	{
		if (buttonCount == MAX_BUTTON_COUNT || bagWeight + items[key]->GetItemData().weight > MAX_BAG_WEIGHT)
			return false;
		for (ItemButton* button : buttons)
		{
			if (button->IsActive()) continue;
			button->SetData(items[key]);
			SpawnButton(button);
			buttonCount++;
			break;
		}

	}
	if (bagWeight + items[key]->GetItemData().weight > MAX_BAG_WEIGHT)
		return false;


	items[key]->SetItemCount(items[key]->GetItemCount() + 1);
	bagWeight += items[key]->GetItemData().weight;
	return true;
}

bool Inventory::SellItem(int key)
{
	ItemData& data = items[key]->GetItemData();

	if (data.itemStack)
	{
		items[key]->MinusItemCount();
		if (items[key]->GetItemCount() == 0)
		{
			stackButtons[key]->SetActive(false);
		}
	}
	else
	{
		for (ItemButton* button : buttons)
		{
			if (!button->IsActive()) continue;
			if (button->GetItem()->GetItemKey() != key) continue;

			button->SetActive(false);
			break;
		}
	}

	buttonCount = 0;


	for (auto it = showButtons.begin(); it != showButtons.end(); )
	{
		ItemButton* button = *it;

		if (button->IsActive())
		{
			SpawnButton(button, true);
			buttonCount++;
			++it; // 다음 요소로 이동
		}
		else
		{
			it = showButtons.erase(it); // 삭제만, Spawn 안 함
		}
	}



	bagWeight -= data.weight;
	money += data.price;
	choiceItem = nullptr;


	return false;
}

bool Inventory::BuyItem(int key)
{
	ItemData data = items[key]->GetItemData();
	if(money< data.price)
		return false;
	if (bagWeight + data.weight > MAX_BAG_WEIGHT || buttonCount == MAX_BUTTON_COUNT)
		return false;

	AddItem(key);
	return true;
}

void Inventory::Edit()
{
	if (!isOn) return;

	for (auto& pair : stackButtons)
	{
		if (!pair.second->IsActive()) continue;
		pair.second->RenderTexture();
	}
	for (ItemButton* button : buttons)
	{
		if (!button->IsActive()) continue;
		button->RenderTexture();
	}

	RenderTexture(); 
}

void Inventory::SpawnButton(ItemButton*& button, bool isShowButton)
{
	button->SetActive(true);

	Vector3 pos;
	pos.x = buttonStartPos.x + (buttonOffSet.x * (buttonCount % 4));
	pos.y = buttonStartPos.y + (buttonOffSet.y * (buttonCount / 4) + 1);


	button->SetLocalPosition(pos);
	button->UpdateWorld();

	if (isShowButton) return;
	showButtons.push_back(button);
}

void Inventory::UpdateInventory()
{
	buttonCount = 0;
	for (ItemButton* button : showButtons)
	{
		SpawnButton(button);
		buttonCount++;
	}
}

void Inventory::CreateBackGround()
{
	backGround = new Quad(L"Resources/Textures/UI/Inventory/Inventory_BackGround.jpg");
	backGround->SetLocalScale(0.5f, 0.5f, 0.5f);
	backGround->SetParent(this);
}

void Inventory::CreateButtons()
{
	buttons.resize(MAX_BUTTON_COUNT);
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i] = new ItemButton(items[1001]);
		buttons[i]->SetActive(false);
		ItemButton* button = buttons[i];
		button->SetOnClick([this, button]() {SetChoiceItem(button->GetItem()->GetItemKey()); });
	}

	stackButtons.reserve(DataManager::Get()->GetStackItemCount());
	for (int i = 0; i < DataManager::Get()->GetItemCount(); i++)
	{
		if (!DataManager::Get()->GetItem(1001 + i).itemStack) continue;
		{
			ItemButton* button = new ItemButton(items[1001 + i]);
			button->SetActive(false);
			button->SetOnClick([this, button]() {SetChoiceItem(button->GetItem()->GetItemKey());});
			stackButtons.emplace(1001 + i, button);
		}
	}


	choiceItemButton = new ItemButton(items[1001]);
	choiceItemButton->SetLocalPosition(100,200,0);
}

void Inventory::CreateItems()
{
	items.reserve(DataManager::Get()->GetItemCount());

	for (int i = 0; i < DataManager::Get()->GetItemCount(); i++)
	{
		Item* item = new Item(1001 + i);
		items.emplace(1001 + i, item);
	}
}

void Inventory::SetEventFunc()
{
	EventManager::Get()->AddEvent("AddItem", [this](void* param) {AddItem(*(int*)param); });
	EventManager::Get()->AddEvent("SellItem", [this](void* param) {SellItem(*(int*)param); });
	EventManager::Get()->AddEvent("BuyItem", [this](void* param) {BuyItem(*(int*)param); });
}

void Inventory::RenderTexture()
{
	ImDrawList* drawList = ImGui::GetForegroundDrawList();
	string text = to_string(bagWeight) + " / " + to_string(MAX_BAG_WEIGHT);

	ImFont* font = ImGui::GetFont(); // 현재 폰트
	float fontSize = 16.0f; // 원하는 크기

	ImU32 col = ImGui::ColorConvertFloat4ToU32(color);

	drawList->AddText(font, fontSize,
		ImVec2(localPosition.x + 50, localPosition.y + 70),
		col,
		text.c_str());
}

void Inventory::SetChoiceItem(int key)
{
	choiceItem = items[key];
	choiceItemButton->SetData(items[key]);
}

