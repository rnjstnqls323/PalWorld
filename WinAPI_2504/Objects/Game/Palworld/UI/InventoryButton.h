#pragma once

class ItemButton :public Button
{
	//원래라면 이거 나눠서 버튼따로, 아이템 따로 해야됨
	//걍 따로만듦
public:
	ItemButton(Item*& item);
	~ItemButton();

	void Render() override;

	Item*& GetItem() { return item; }

	void SetData(Item*& item);
	void RenderTexture();

protected:
	void SpawnButton();

private:
	Item* item;


};