#pragma once

class SmallRock : public ObjectItem
{
public:
	SmallRock();
	~SmallRock();

protected:
	void CreateModel() override;
	void SetItemType() override;


};