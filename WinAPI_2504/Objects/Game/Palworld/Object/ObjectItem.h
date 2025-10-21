#pragma once

enum class ItemType
{
	SmallRock, Wood
};

class ObjectItem : public SphereCollider
{
protected:
	const float GRAVITY = 9.8;

public:
	ObjectItem();
	ObjectItem(float size);
	~ObjectItem();

	void SpawnItem(Vector3 pos);
	void Update(BoxCollider*& floor, class Jorney*& jorney);
	void Render();

	void Edit();
	//���϶� ������ ó���ϴ� �ڵ� �ۼ��ϱ�
protected:
	void Init();
	virtual void CreateModel() = 0;
	virtual void SetItemType() = 0;

	bool IsCollisionToFloor(BoxCollider* floor);
	bool IsCollisionToJorney(class Jorney* jorney);

	void RigidBody();
protected:

	bool isFloor = false;
	ItemType type;


	Vector3 velocity;
	Model* model;

};