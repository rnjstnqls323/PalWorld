#pragma once

struct CharacterStat
{
	int healthPoint;
	int AttackPower;
};
class Character :public CapsuleCollider
{
protected:
	const float GRAVITY = 9.8;
public:
	Character();
	Character(float radius, float height);
	~Character();

	virtual void Update(BoxCollider* floor);
	virtual void Render();
	virtual void Edit();


protected:
	void Init();
	void PlayClip(size_t index);
	void Rotate();

	void RigidBody();
	bool IsCollisionToFloor(BoxCollider* floor);
	virtual void Move() = 0;
	virtual void CreateModel() = 0;
	virtual void SetStat() = 0;

protected:
	int curIndex = 0;
	
	float rotateSpeed = 10.0f;
	float moveSpeed = 5.0f;

	Vector3 moveDir = Vector3::Zero();

	CharacterStat stat;
	Vector3 velocity;
	ModelAnimator* model;
};