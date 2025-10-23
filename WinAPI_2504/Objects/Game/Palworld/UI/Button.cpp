#include "Framework.h"

Button::Button(wstring fileName)
{
	wstring path = L"Resources/Textures/UI/Inventory/" + fileName + L".png";
	quad = new Quad(Vector2(50,50));
	
	quad->GetMaterial()->SetDiffuseMap(path);

	quad->SetParent(this);

	UpdateWorld();
	quad->UpdateWorld();
}

Button::Button(wstring imagePath, Vector2 size)
{
	quad = new Quad(size);
	quad->GetMaterial()->SetDiffuseMap(imagePath);
	
	quad->SetParent(this);

	UpdateWorld();
	quad->UpdateWorld();

}

Button::~Button()
{
	delete quad;
}

void Button::Update()
{
	UpdateWorld();
	quad->UpdateWorld();

	if (IsPointCollision(mousePos))
	{
		GetMaterial()->SetColor(1, 0, 0);
		if (Input::Get()->IsKeyDown(VK_LBUTTON))
			OnClick(); //�̺�Ʈ ������� �߻���Ű����? �ϴ� ��Ŭ���س��� ã�ƿ���
	}
	else
		GetMaterial()->SetColor(0, 1, 0);
}

void Button::Render()
{
	BoxCollider::Render();
	quad->Render();
}
