#pragma once

class Rock : public MainObject
{
public:
	Rock();
	~Rock();


protected:
	void CreateItems() override;

	void CreateModel() override;


	// MainObject을(를) 통해 상속됨
	void CreateCollider() override;

};