#include "Framework.h"
#include "PalWorldScene.h"

PalWorldScene::PalWorldScene()
{
	floor = new WorldFloor();
	rock = new Rock();
	tree = new Tree();
	smallRock = new SmallRock();
	wood = new Wood();
	jorney = new Jorney();
	weapon = new Weapon();
}

PalWorldScene::~PalWorldScene()
{
	delete floor;
	delete rock;
	delete tree;
	delete smallRock;
	delete wood;
	delete jorney;
	delete weapon;
}

void PalWorldScene::Update()
{
	//wood->Update(floor,nullptr);
	//smallRock->Update(floor,nullptr);
	tree->Update((BoxCollider*&)floor, jorney);
	rock->Update((BoxCollider*&)floor,jorney);
	jorney->Update(floor);
	//weapon->Update();
}

void PalWorldScene::PreRender()
{
}

void PalWorldScene::Render()
{
	floor->Render();
	//wood->Render();
	//smallRock->Render();
	rock->Render();
	tree->Render();
	jorney->Render();
}

void PalWorldScene::PostRender()
{
}

void PalWorldScene::GUIRender()
{
	//wood->Edit();
	//smallRock->Edit();
	//rock->Edit();
	//tree->Edit();
	jorney->Edit();
}
