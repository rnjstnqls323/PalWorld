#pragma once

class InventoryButton :public Button
{
	//원래라면 이거 나눠서 버튼따로, 아이템 따로 해야됨
public:
	InventoryButton(int key);
	~InventoryButton();

	void SetData(ItemData*& data) { this->data = data; }

	void Render() override;

	void SetNum(int num) { this->num = num; }
	int GetNum() { return num; }

	void RenderTexture();

	void SpawnButton(int key);

protected:
	// Button을(를) 통해 상속됨
	void OnClick() override;

private:
	int num = 0;
	
	ItemData* data;

};