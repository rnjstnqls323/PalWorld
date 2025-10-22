#pragma once

class Wood : public ObjectItem
{
public:
	Wood();
	~Wood();

protected:

	void CreateModel() override;
	void SetItemType() override;


	// ObjectItem을(를) 통해 상속됨
	void SetItemData() override;

};