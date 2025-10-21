#pragma once

class Tree : public MainObject
{
public:
	Tree();
	~Tree() {}

protected:

	void CreateItems() override;
	void CreateModel() override;


	// MainObject을(를) 통해 상속됨
	void CreateCollider() override;

};