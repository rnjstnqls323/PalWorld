#pragma once


class Inventory
{
public:
	Inventory();
	~Inventory();

	void Render();
	//void Update(); 보류 굳이 계속 업데이트 해줄필요있을까?
	
	void AddItem(int key);
	void SellItem(int key);

	void BuyItem(int key);

private:
	void UpdateInventory();

private:
	Quad* backGround;




};