#include "Framework.h"

InventoryButton::InventoryButton(int key):Button(to_wstring(key))
{
	tag = "InventoryButton";
	SetSize(Vector3(50, 50, 50));

	
}

InventoryButton::~InventoryButton()
{
}

void InventoryButton::Render()
{
	Button::Render();
	

}

void InventoryButton::RenderTexture()
{
	ImDrawList* drawList = ImGui::GetForegroundDrawList();
	string text = to_string(num);
	drawList->AddText(ImVec2(localPosition.x + 10, SCREEN_HEIGHT - localPosition.y+10), IM_COL32(255, 255,	0, 255), text.c_str());
}

void InventoryButton::SpawnButton(int key)
{
	wstring fileName = to_wstring(key);
	wstring path = L"Resources/Textures/UI/Inventory/" + fileName + L".png";

	quad->GetMaterial()->SetDiffuseMap(path);

	num = 1;
}

void InventoryButton::OnClick()
{
}
