#include "Framework.h"

Jorney::Jorney():Character(0.5,1.5)
{
	leftHand = new Transform();
	rightHand = new Transform();

	leftHand->SetTag("LeftHand");
	rightHand->SetTag("RightHand");

	Init();
	Load();
	model->Load();

	MakeEvent();

	weapon = new Weapon();
	weapon->Load();
	weapon->SetParent(leftHand);

	CAM->SetTarget(this);
}

Jorney::~Jorney()
{
	delete leftHand;
	delete rightHand;
	delete weapon;
}

void Jorney::Update(BoxCollider* floor)
{
	rightHand->SetWorld(model->GetTransformByNode(35));
	leftHand->SetWorld(model->GetTransformByNode(11));

	Character::Update(floor);
	weapon->Update();

	StartAttack();
	StartThrowBall();
}

void Jorney::Render()
{
	Character::Render();
	weapon->Render();
}

void Jorney::Edit()
{
	Character::Edit();
	rightHand->Edit();
	leftHand->Edit();
	weapon->Edit();
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

	model->ReadClip("Idle");
	model->ReadClip("Run");
	model->ReadClip("Attack");
	model->ReadClip("Walk");
	model->ReadClip("SitWalk");
	model->ReadClip("Throw");
	model->ReadClip("Jump"); //할까?
	model->ReadClip("SitIdle");
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

void Jorney::MakeEvent()
{
	model->GetClip((int)Status::Attack)->SetEvent(bind(&Jorney::EndAnimation, this), 0.9f);

	model->GetClip((int)Status::Attack)->SetEvent(bind(&Jorney::OnWeapon, this), 0.1f);
	model->GetClip((int)Status::Attack)->SetEvent(bind(&Jorney::OffWeapon, this), 0.7f);

	model->GetClip((int)Status::Throw)->SetEvent(bind(&Jorney::EndAnimation, this), 0.9f);
	model->GetClip((int)Status::Throw)->SetEvent(bind(&Jorney::ThrowBall, this), 0.5f);
}

void Jorney::StartAttack()
{
	if (Input::Get()->IsKeyPress(VK_LBUTTON))
		status = Status::Attack;
	PlayClip((int)status);
}

void Jorney::EndAnimation()
{
	status = Status::Idle;
	PlayClip((int)status);
}

void Jorney::OnWeapon()
{
	weapon->SetActive(true);
}

void Jorney::OffWeapon()
{
	weapon->SetActive(false);
}

void Jorney::StartThrowBall()
{
	if (Input::Get()->IsKeyDown('Q'))
		status = Status::Throw;
	PlayClip((int)status);
}

void Jorney::ThrowBall()
{
	//공 날라가는거 추가하기 (weapon으로 부모둬야될까?)
}

