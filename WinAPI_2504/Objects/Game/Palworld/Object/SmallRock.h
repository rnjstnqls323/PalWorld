#pragma once

class SmallRock : public ObjectItem
{
public:
	SmallRock();
	~SmallRock();

protected:
	void CreateModel() override;
	void SetItemType() override;

	// ObjectItem을(를) 통해 상속됨
	void SetItemData() override;

};