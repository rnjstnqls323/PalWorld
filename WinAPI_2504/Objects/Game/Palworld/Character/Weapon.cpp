#include "Framework.h"

Weapon::Weapon():SphereCollider(15)
{
	tag = "Weapon";
	SetActive(false);
}

Weapon::~Weapon()
{
}

void Weapon::Update()
{
	UpdateWorld();
}
