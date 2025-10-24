#include "Framework.h"
#include "PalWorldScene.h"

PalWorldScene::PalWorldScene()
{
	DataManager::Get()->LoadData("ItemData.csv");
	floor = new WorldFloor();
	rock = new Rock();
	tree = new Tree();
	smallRock = new SmallRock();
	wood = new Wood();
	jorney = new Jorney();
	weapon = new Weapon();

	//quad = new Quad(L"Resources/Textures/Test.jfif");
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
	//delete quad;
}

void PalWorldScene::Update()
{
	//wood->Update(floor,nullptr);
	//smallRock->Update(floor,nullptr);
	tree->Update((BoxCollider*&)floor, jorney);
	rock->Update((BoxCollider*&)floor,jorney);
	jorney->Update(floor);

	//weapon->Update();

	//quad->UpdateWorld();
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
	//quad->Render();
	jorney->GetInventory()->Render();
}

void PalWorldScene::GUIRender()
{
	//wood->Edit();
	//smallRock->Edit();
	//rock->Edit();
	//tree->Edit();
	jorney->Edit();
	//quad->SetTag("Quad");
	//quad->Edit();

}
