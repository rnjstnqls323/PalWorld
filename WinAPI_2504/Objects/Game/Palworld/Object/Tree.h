#pragma once

class Tree : public MainObject
{
public:
	Tree();
	~Tree() {}

protected:

	void CreateItems() override;
	void CreateModel() override;


	// MainObject��(��) ���� ��ӵ�
	void CreateCollider() override;

};