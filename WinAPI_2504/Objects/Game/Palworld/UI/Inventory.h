#pragma once


class Inventory :public Transform
{
private:
	const int MAX_BUTTON_NUM = 24;
	const int MAX_BAG_WEIGHT = 50;
public:
	Inventory();
	~Inventory();

	void Render();
	void Update();
	
	void AddItem(int key);
	void SellItem(int key);

	void BuyItem(int key);

	void Edit() override;


private:
	void UpdateInventory();
	void CreateBackGround();
	void CreateButtons();

private:
	int buttonNum = 0;

	Vector3 buttonStartPos = Vector3(107, 604, 0);
	Vector3 buttonOffSet = Vector3(62, -63, 0);

	Quad* backGround;
	InventoryButton* button;

	unordered_map<int, pair<ItemData, int>> items;

	vector<InventoryButton*> buttons;
	unordered_map<int, InventoryButton*> stackButtons;

};