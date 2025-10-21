#pragma once

class Rock : public MainObject
{
public:
	Rock();
	~Rock();

	void Update(); //ª©µµµ 

protected:
	void CreateItems() override;

	void CreateModel() override;


	// MainObject¿ª(∏¶) ≈Î«ÿ ªÛº”µ 
	void CreateCollider() override;

};