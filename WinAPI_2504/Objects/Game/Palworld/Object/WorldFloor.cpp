#include "Framework.h"

WorldFloor::WorldFloor():BoxCollider(Vector3(6000,0.1,6000))
{
	plane = new Plane(Vector2(200, 200));
	plane->Load();
	Load();

	plane->GetMaterial()->SetDiffuseMap(L"Resources/Textures/LandScape/Grass.png");

	UpdateWorld();
	plane->UpdateWorld();
}

WorldFloor::~WorldFloor()
{
	delete plane;
}

void WorldFloor::Render()
{
	plane->Render();
	//BoxCollider::Render();
}

