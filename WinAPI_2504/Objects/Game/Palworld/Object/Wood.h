#pragma once

class Wood : public ObjectItem
{
public:
	Wood();
	~Wood();

protected:

	void CreateModel() override;
	void SetItemType() override;


	// ObjectItem��(��) ���� ��ӵ�
	void SetItemData() override;

};