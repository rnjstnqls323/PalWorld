#pragma once

class WorldFloor :public BoxCollider
{
public:
	WorldFloor();
	~WorldFloor();

	void Render() override;

private:
	Plane* plane;
};