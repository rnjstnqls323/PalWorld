#pragma once

class PalWorldScene : public Scene
{
public:
	PalWorldScene();
	~PalWorldScene();
	

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
	void GUIRender() override;

private:
	WorldFloor* floor;
	Rock* rock;
	Tree* tree;
	SmallRock* smallRock;
	Wood* wood;
	Jorney* jorney;
	Weapon* weapon;
	Quad* quad;
};