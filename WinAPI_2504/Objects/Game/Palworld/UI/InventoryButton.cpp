#include "Framework.h"

ItemButton::ItemButton(Item*& item) :Button(to_wstring(item->GetItemKey()))
{
	tag = "InventoryButton";
	SetSize(Vector3(50, 50, 50));

	this->item = item;
}

ItemButton::~ItemButton()
{
}

void ItemButton::Render()
{
	Button::Render();
	

}

void ItemButton::SetData(Item*& item)
{
	this->item = item;
	SpawnButton();
}

void ItemButton::RenderTexture()
{
	ImDrawList* drawList = ImGui::GetForegroundDrawList();
	string text;
	if (item->GetItemData().itemStack)
		text = to_string(item->GetItemCount());
	else
		text = to_string(1);

	drawList->AddText(ImVec2(localPosition.x + 10, SCREEN_HEIGHT - localPosition.y+10), IM_COL32(255, 255,	0, 255), text.c_str());
}


void ItemButton::SpawnButton()
{
	wstring fileName = to_wstring(item->GetItemKey());
	wstring path = L"Resources/Textures/UI/Inventory/" + fileName + L".png";

	quad->GetMaterial()->SetDiffuseMap(path);

	//item->SetItemCount(1);
}

void ItemButton::OnClick()
{
	if (onClick == nullptr) return;
	onClick();

	//int key = item->GetItemKey();
	//EventManager::Get()->ExcuteEvent("SelectItem", &key);
}

