#pragma once

class Jorney : public Character
{
private:
	enum class Status
	{
		Idle, Run, Attack, Walk, SitWalk, Throw, Jump,SitIdle
	};
public:
	Jorney();
	~Jorney();

	void Update(BoxCollider* floor) override;
protected:
	void Move() override;
	void CreateModel() override;
	void SetStat() override;
	void AttackMotion();

private:
	float runSpeed = 5.0f;
	float sitSpeed = 1.5f;
	bool isRun = false;
	bool isSit = false;

	Status status = Status::Idle;
};