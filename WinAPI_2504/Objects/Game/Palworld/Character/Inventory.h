#pragma once


class Inventory
{
public:
	Inventory();
	~Inventory();

	void Render();
	//void Update(); ���� ���� ��� ������Ʈ �����ʿ�������?
	
	void AddItem(int key);
	void SellItem(int key);

	void BuyItem(int key);

private:
	void UpdateInventory();

private:
	Quad* backGround;




};