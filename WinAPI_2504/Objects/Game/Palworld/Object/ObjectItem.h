#pragma once

enum class ItemType
{
	SmallRock, Wood
};

class ObjectItem : public SphereCollider
{
protected:
	const float GRAVITY = 9.8;
	const float SPAWN_DISTANCE = 0.7;

public:
	ObjectItem();
	ObjectItem(float size);
	~ObjectItem();

	virtual void SpawnItem(Vector3 pos);
	void Update(BoxCollider*& floor, class Jorney*& jorney);
	void Render();

	void Edit();
	const ItemData& GetItemData() { return data; }
	//조니랑 닿으면 처리하는 코드 작성하기
protected:
	void Init();
	virtual void CreateModel() = 0;
	virtual void SetItemType() = 0;
	virtual void SetItemData() = 0;

	bool IsCollisionToFloor(BoxCollider* floor);
	bool IsCollisionToJorney(class Jorney* jorney);

	void RigidBody();
protected:
	float spawnTime = 0.0f;
	bool isSpawn = false;
	bool isFloor = false;
	ItemType type;


	Vector3 velocity;
	Model* model;

	ItemData data;

};