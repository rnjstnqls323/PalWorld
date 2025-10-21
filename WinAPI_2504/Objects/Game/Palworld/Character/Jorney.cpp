#include "Framework.h"

Jorney::Jorney():Character(0.5,1.5)
{
	Init();
	Load();
	model->Load();
}

Jorney::~Jorney()
{
}

void Jorney::Update(BoxCollider* floor)
{
	Character::Update(floor);
	AttackMotion();
}


void Jorney::Move()
{
	if (status == Status::Attack)
		return;

	moveDir = Vector3::Zero();
	if (Input::Get()->IsKeyPress(VK_LSHIFT))
	{
		isRun = true;
		isSit = false;
	}
	else if (Input::Get()->IsKeyDown(VK_LCONTROL))
		isSit = !isSit;
	
	else
	{
		isRun = false;
	}

	if (Input::Get()->IsKeyPress('W'))
	{
		moveDir += Vector3::Forward();
	}
	else if (Input::Get()->IsKeyPress('S'))
	{
		moveDir += Vector3::Back();
	}

	if (Input::Get()->IsKeyPress('A'))
	{
		moveDir += Vector3::Left();
	}
	else if (Input::Get()->IsKeyPress('D'))
	{
		moveDir += Vector3::Right();
	}

	if (moveDir.Length() > 0.0f)
	{
		moveDir.Normalize();
		if (isRun)
		{
			Translate(moveDir * runSpeed * DELTA);
			status = Status::Run;
		}
		else if (isSit)
		{
			Translate(moveDir * sitSpeed * DELTA);
			status = Status::SitWalk;
		}
		else
		{
			Translate(moveDir * moveSpeed * DELTA);
			status = Status::Walk;
		}
		Rotate();
	}
	else if (!isSit)
	{
		status = Status::Idle;
	}
	else
		status = Status::SitIdle;
	PlayClip((int)status);
}

void Jorney::CreateModel()
{
	SetLocalPosition(0, 1.4, 0);
	UpdateWorld();
	model = new ModelAnimator("Jorney");
	model->SetVertexShader(L"Model/Model.hlsl");

	model->ReadClip("Idle", 0);
	model->ReadClip("Run", 0);
	model->ReadClip("Attack", 0);
	model->ReadClip("Walk", 0);
	model->ReadClip("SitWalk", 0);
	model->ReadClip("Throw", 0);
	model->ReadClip("Jump", 0);
	model->ReadClip("SitIdle", 0);
	model->CreateTexture();

	model->SetLocalScale(0.015, 0.015, 0.015);
	model->SetLocalPosition(0, -1.3, 0);
	model->UpdateWorld();
	
}

void Jorney::SetStat()
{
	stat.healthPoint = 100;
	stat.AttackPower = 10;

	moveSpeed = 2.0f;

}

void Jorney::AttackMotion()
{
	if (Input::Get()->IsKeyDown(VK_LBUTTON))
		status = Status::Attack;
	PlayClip((int)status);
}
