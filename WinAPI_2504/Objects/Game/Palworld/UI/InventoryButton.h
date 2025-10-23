#pragma once

class InventoryButton :public Button
{
	//������� �̰� ������ ��ư����, ������ ���� �ؾߵ�
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
	// Button��(��) ���� ��ӵ�
	void OnClick() override;

private:
	int num = 0;
	
	ItemData* data;

};