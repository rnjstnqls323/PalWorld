#pragma once


class Inventory :public Transform
{
private:
	const int MAX_BUTTON_COUNT = 24;
	const int MAX_BAG_WEIGHT = 50;
public:
	Inventory();
	~Inventory();

	void Render();
	void Update();
	
	Item* GetChoiceItem() { return choiceItem; }	

	bool AddItem(int key);
	bool SellItem(int key);

	bool BuyItem(int key);

	void Edit() override;

	bool IsOn() { return isOn; }

	void OnInventory()
	{
		isOn = true;
		choiceItem = nullptr;
		ShowCursor(true);
	}
	void OffInventory() { isOn = false; ShowCursor(false);}


private:
	void SpawnButton(ItemButton*& button, bool isShowButton = false);
	void UpdateInventory();
	void CreateBackGround();
	void CreateButtons();
	void CreateItems();

	void SetEventFunc();

	void RenderTexture();

	void SetChoiceItem(int key);


private:
	bool isOn = true;

	int money = 0;

	int buttonCount = 0;
	int bagWeight = 0;

	ImVec4 color = { 0,0,0,255 };

	Vector3 buttonStartPos = Vector3(107, 604, 0);
	Vector3 buttonOffSet = Vector3(62, -63, 0);

	Quad* backGround;
	ItemButton* choiceItemButton;
	Item* choiceItem;

	unordered_map<int, Item*> items;

	vector<ItemButton*> buttons;
	unordered_map<int, ItemButton*> stackButtons;

	list<ItemButton*> showButtons;

};