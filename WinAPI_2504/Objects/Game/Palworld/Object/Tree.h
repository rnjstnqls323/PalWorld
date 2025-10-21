#pragma once

class Tree : public MainObject
{
public:
	Tree();
	~Tree() {}

	void Update();

protected:

	void CreateItems() override;
	void CreateModel() override;


	// MainObject��(��) ���� ��ӵ�
	void CreateCollider() override;

};