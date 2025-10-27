#pragma once

class ItemButton :public Button
{
	//������� �̰� ������ ��ư����, ������ ���� �ؾߵ�
	//�� ���θ���
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