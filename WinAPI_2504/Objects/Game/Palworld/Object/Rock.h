#pragma once

class Rock : public MainObject
{
public:
	Rock();
	~Rock();


protected:
	void CreateItems() override;

	void CreateModel() override;


	// MainObject��(��) ���� ��ӵ�
	void CreateCollider() override;

};