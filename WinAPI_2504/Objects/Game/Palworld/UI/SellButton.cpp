#include "Framework.h"

SellButton::SellButton():Button(L"1010")
{
	SetSize(Vector3(60, 60, 60));
}

SellButton::~SellButton()
{
}

void SellButton::OnClick()
{
	int id = 1001;
	EventManager::Get()->ExcuteEvent("SellItem", &id);
}
