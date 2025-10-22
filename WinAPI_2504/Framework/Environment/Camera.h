#pragma once

class Camera : public Transform
{
private:
	const int CAMERA_ARM = 10;
public:
	Camera();
	~Camera();

	void Update();
	void Edit();

	void SetTarget(Transform* target) 
	{ this->target = target;     
	// Ä¿¼­ ¼û±â±â
	ShowCursor(false);
	}

	class Ray ScreenPointToRay(Vector3 screenPos);

private:
	void FreeMode();
	void FollowMode();

	void LookAt();

private:
	float moveSpeed = 10.0f;
	float rotSpeed = 10.0f;

	bool isMouseHide = true;
	Vector3 prevMousePos;

	Matrix view;
	Matrix projection;
	ViewBuffer* viewBuffer;	

	POINT center;

	Transform* target = nullptr;	
};