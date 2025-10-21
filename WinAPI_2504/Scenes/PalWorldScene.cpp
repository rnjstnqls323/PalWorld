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
}

PalWorldScene::~PalWorldScene()
{
	delete floor;
	delete rock;
	delete tree;
	delete smallRock;
	delete wood;
	delete jorney;
}

void PalWorldScene::Update()
{
	//wood->Update(floor,nullptr);
	//smallRock->Update(floor,nullptr);
	//tree->Update();
	rock->Update();
	jorney->Update(floor);
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
	//tree->Render();
	jorney->Render();
}

void PalWorldScene::PostRender()
{
}

void PalWorldScene::GUIRender()
{
	//wood->Edit();
	//smallRock->Edit();
	rock->Edit();
	//tree->Edit();
	jorney->Edit();
}
