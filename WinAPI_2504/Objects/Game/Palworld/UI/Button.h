#pragma once

class Button : public BoxCollider
{
public:
	Button(wstring fileName);
	Button(wstring imagePath, Vector2 size);
	~Button();

	virtual void Update();
	virtual void Render();

	void SetOnClick(function<void()> func) { onClick = func; }

protected:
	virtual void OnClick() = 0;

protected:
	function<void()> onClick;
	Quad* quad;
};