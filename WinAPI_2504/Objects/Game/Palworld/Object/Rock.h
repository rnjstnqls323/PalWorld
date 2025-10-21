#pragma once

class Rock : public MainObject
{
public:
	Rock();
	~Rock();

	void Update(); //������

protected:
	void CreateItems() override;

	void CreateModel() override;


	// MainObject��(��) ���� ��ӵ�
	void CreateCollider() override;

};