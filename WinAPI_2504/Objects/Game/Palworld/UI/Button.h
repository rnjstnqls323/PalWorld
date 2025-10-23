#pragma once

class Button : public BoxCollider
{
public:
	Button(wstring fileName);
	Button(wstring imagePath, Vector2 size);
	~Button();

	virtual void Update();
	virtual void Render();

protected:
	virtual void OnClick() = 0;

protected:
	Quad* quad;
};