#pragma once

class Item
{
public:
	Item(int key){ data = DataManager::Get()->GetItem(key); }
	~Item() {}

	void SetItemCount(int count) { this->count = count; }

	void AddItemCount() { count++;}
	void MinusItemCount() { count--; }

	int GetItemCount() { return count; }
	int GetItemKey() { return data.key; }
	ItemData& GetItemData() { return data; }
	
	void SetData(int key) { data = DataManager::Get()->GetItem(key); count = 0; }
private:
	ItemData data;
	int count = 0;
};