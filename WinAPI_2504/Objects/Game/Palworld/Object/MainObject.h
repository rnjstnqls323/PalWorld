#pragma once

class MainObject : public Transform
{
protected:
	const int MAX_ITEM_NUM = 50;
public:
	MainObject();
	~MainObject();

	void MineObject(SphereCollider* sphere);

	virtual void Update(BoxCollider*& floor, class Jorney*& jorney);
	void Render();

	void Edit();


protected:
	void Init();
	bool IsJorneyCollision(class Jorney*& jorney);
	void DropItem(Vector3 jorneyPos);

	void PushJorneyToBoxCollider(BoxCollider* box, Jorney*& jorney);
	void PushJorneyToSphereCollider(SphereCollider* sphere, Jorney*& jorney);
	

	virtual void CreateItems() = 0;
	virtual void CreateModel() = 0;
	virtual void CreateCollider() = 0;

protected:
	Collider* collider;
	Model* model;
	vector<ObjectItem*> items;
};