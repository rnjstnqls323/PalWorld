#include "Framework.h"

Camera::Camera()
{
	tag = "Camera";

	viewBuffer = new ViewBuffer();

    center = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    ClientToScreen(hWnd, &center);
    SetCursorPos(center.x, center.y);


}

Camera::~Camera()
{
	delete viewBuffer;
}

void Camera::Update()
{
	projection = Environment::Get()->GetPerspective();

    if (Input::Get()->IsKeyDown(VK_ESCAPE))
    {
        isMouseHide = !isMouseHide;
        ShowCursor(true);
    }

    if (target)
        FollowMode();
    else
	    FreeMode();

	UpdateWorld();	

	view = XMMatrixInverse(nullptr, world);
	viewBuffer->Set(view, world);
	viewBuffer->SetVS(1);
}

void Camera::Edit()
{
	ImGui::DragFloat("MoveSpeed", &moveSpeed, 0.1f, 0.1f, 100.0f);
	ImGui::DragFloat("RotSpeed", &rotSpeed, 0.1f, 0.1f, 100.0f);

    Transform::Edit();
}

Ray Camera::ScreenPointToRay(Vector3 screenPos)
{
    Vector3 screenSize(SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f);    

    Vector2 point;
	point.x = (screenPos.x / screenSize.x) * 2.0f - 1.0f;
	point.y = (screenPos.y / screenSize.y) * 2.0f - 1.0f;
	//-> 0~screen -> -1~1

    Float4x4 temp;
    XMStoreFloat4x4(&temp, projection);

	screenPos.x = point.x / temp._11;
	screenPos.y = point.y / temp._22;
    screenPos.z = 1.0f;

    screenPos = XMVector3TransformNormal(screenPos, world);

    Ray ray;
	ray.origin = localPosition;
	ray.direction = screenPos.GetNormalized();

    return ray;
}

void Camera::FreeMode()
{
    Vector3 delta = mousePos - prevMousePos;
    prevMousePos = mousePos;

    if (Input::Get()->IsKeyPress(VK_RBUTTON))
    {
        if (Input::Get()->IsKeyPress('W'))
            Translate(forward * moveSpeed * DELTA);
        if (Input::Get()->IsKeyPress('S'))
            Translate(-forward * moveSpeed * DELTA);
        if (Input::Get()->IsKeyPress('E'))
            Translate(up * moveSpeed * DELTA);
        if (Input::Get()->IsKeyPress('Q'))
            Translate(-up * moveSpeed * DELTA);
        if (Input::Get()->IsKeyPress('A'))
            Translate(-right * moveSpeed * DELTA);
        if (Input::Get()->IsKeyPress('D'))
            Translate(right * moveSpeed * DELTA);

        Rotate(Vector3::Right(), -delta.y * rotSpeed * DELTA);
        Rotate(Vector3::Up(), delta.x * rotSpeed * DELTA);
    }
}

void Camera::FollowMode()
{
    float distance = 8;
    Vector3 back = -target->GetForward();
    Vector3 camPos = (target->GetGlobalPosition() + (back * distance));
    camPos.y += 5;

    SetLocalPosition(camPos);



    LookAt();
   // localRotation.x = 0.5;
}

void Camera::LookAt()
{
    if (!isMouseHide) return;

    // 1. ���� ���콺 ��ġ ��������
    POINT currentMousePos;
    GetCursorPos(&currentMousePos);

    // 3. ���콺 ��Ÿ ��� (���� ��ġ - �߾�)
    int deltaX = currentMousePos.x - center.x;
    int deltaY = currentMousePos.y - center.y;

    // 4. Ŀ�� �ٽ� ����� �̵� (���콺 ����)
    SetCursorPos(center.x, center.y);

    // 5. ���콺 ���� & ȸ�� �ӵ� ����
    float sensitivity = 0.3f;

    float yaw = deltaX * sensitivity * rotSpeed * DELTA;
    float pitch = deltaY * sensitivity * rotSpeed * DELTA;

    // 6. ȸ�� ����
    Rotate(Vector3::Up(), yaw);         // �¿� ȸ�� (Yaw)
    Rotate(Vector3::Right(), pitch);   // ���� ȸ�� (Pitch)

    // �� pitch�� -�� �ٿ��� �Ϲ����� FPS ��Ÿ�Ϸ� ���� (���콺 ���� �� �Ʒ� ����)
}
