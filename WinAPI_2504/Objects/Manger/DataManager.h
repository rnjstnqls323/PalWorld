#pragma once

struct ItemData
{
	int key;
	string name;
	int price;
	int weight;
	float value;
	bool itemStack;
};

class DataManager : public Singleton<DataManager>
{
	friend class Singleton;

private:
	DataManager();
	~DataManager();

public:
	void LoadData(const string& fileName);
	
	ItemData GetItem(int key) { return itemDatas[key]; }
	int GetItemCount() { return itemDatas.size(); }

	int GetStackItemCount() {return stackItemCount;}

private:
	int stackItemCount = 0;
	unordered_map<int, ItemData> itemDatas;

};