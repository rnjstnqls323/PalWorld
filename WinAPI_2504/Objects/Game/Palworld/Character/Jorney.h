#pragma once

class Jorney : public Character
{
private:
	enum class Status
	{
		Idle, Run, Attack, Walk, SitWalk, Throw, Jump, SitIdle
	};
public:
	Jorney();
	~Jorney();

	void Update(BoxCollider* floor) override;
	void Render() override;
	void Edit() override;

	Weapon*& GetWeapon() { return weapon; }

protected:
	void Move() override;
	void CreateModel() override;
	void SetStat() override;

	void MakeEvent();

	void StartAttack();
	void EndAnimation();
	void OnWeapon();
	void OffWeapon();
	void StartThrowBall();
	void ThrowBall();

private:
	float runSpeed = 5.0f;
	float sitSpeed = 1.5f;
	bool isRun = false;
	bool isSit = false;

	//웨폰작업하기 고른웨폰이랑/ 웨폰리스트

	Weapon* weapon;

	Status status = Status::Idle;
	Transform* leftHand;
	Transform* rightHand;
};