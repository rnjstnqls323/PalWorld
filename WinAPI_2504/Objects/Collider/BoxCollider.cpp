#include "Framework.h"

BoxCollider::BoxCollider(Vector3 size) : size(size)
{
    type = Type::Box;

    MakeMesh();
    mesh->CreateMesh();
}

BoxCollider::~BoxCollider()
{
	delete mesh;
}

bool BoxCollider::IsRayCollision(const Ray& ray, RayHit* hitInfo)
{
	if (!IsActive()) return false;

	UpdateWorld();

	ObbDesc box;
	GetOBB(box);

	Vector3 min = box.halfSize * -1.0f;
	Vector3 max = box.halfSize;

	Vector3 delta = box.center - ray.origin;

	Vector3 D = ray.direction.GetNormalized();

	float tMin = 0.0f;
	float tMax = FLT_MAX;
	int axisIndex = 0;

	for (int i = 0; i < 3; i++)
	{
		Vector3 axis = box.axis[i];
		float e = Vector3::Dot(axis, delta);
		float f = Vector3::Dot(D, axis);

		if (GameMath::NearlyEqual(f, 0.0f))
		{
			if (min[i] > e || e > max[i])
				return false;
		}
		else
		{
			float t1 = (e + min[i]) / f;
			float t2 = (e + max[i]) / f;

			if (t1 > t2)
				swap(t1, t2);

			if (t2 < tMax)
				tMax = t2;
			if (t1 > tMin)
			{
				tMin = t1;
				axisIndex = i;
			}

			if (tMax < tMin)
				return false;
		}
	}

	if (hitInfo)
	{
		hitInfo->isHit = true;
		hitInfo->distance = tMin;
		hitInfo->position = ray.origin + D * hitInfo->distance;
		//hitInfo->normal = (hitInfo->position - box.center).GetNormalized();
		hitInfo->normal = (Vector3::Dot(D, box.axis[axisIndex]) < 0) ?
			box.axis[axisIndex] : box.axis[axisIndex] * -1.0f;
	}

    return true;
}

bool BoxCollider::IsBoxCollision(BoxCollider* collider)
{
	ObbDesc box1, box2;
	GetOBB(box1);
	collider->GetOBB(box2);

	Vector3 D = box2.center - box1.center;

	for (UINT i = 0; i < 3; i++)
	{
		if (IsSeperateAxis(D, box1.axis[i], box1, box2)) return false;
		if (IsSeperateAxis(D, box2.axis[i], box1, box2)) return false;
	}

	for (UINT i = 0; i < 3; i++)
	{
		for (UINT j = 0; j < 3; j++)
		{
			if (box1.axis[i] == box2.axis[j]) return true;
		}
	}

	for (UINT i = 0; i < 3; i++)
	{
		for (UINT j = 0; j < 3; j++)
		{
			Vector3 cross = Vector3::Cross(box1.axis[i], box2.axis[j]);
			if (IsSeperateAxis(D, cross, box1, box2)) return false;
		}
	}

	return true;
}

bool BoxCollider::IsSphereCollision(SphereCollider* collider)
{
	ObbDesc box;
	GetOBB(box);

	Vector3 closestPointToSphere = box.center;

	for (UINT i = 0; i < 3; i++)
	{
		Vector3 direction = collider->GetGlobalPosition() - box.center;
		float length = Vector3::Dot(direction, box.axis[i]);
		float mult = (length < 0.0f) ? -1.0f : 1.0f;
		length = min(abs(length), box.halfSize[i]);
		closestPointToSphere += box.axis[i] * length * mult;
	}

	float distance = Vector3::Distance(collider->GetGlobalPosition(), closestPointToSphere);

    return distance <= collider->Radius();
}

bool BoxCollider::IsCapsuleCollision(CapsuleCollider* capsule)
{
	ObbDesc box;
	GetOBB(box);

	Vector3 p1 = capsule->GetStartPoint();  // 캡슐 선분 시작점
	Vector3 p2 = capsule->GetEndPoint();    // 캡슐 선분 끝점
	float radius = capsule->Radius();

	// === 1. OBB에서 캡슐 중심선분(p1~p2)과 가장 가까운 지점 찾기 ===
	//     → 이건 캡슐과 OBB 사이에서 가장 가깝게 만날 수 있는 가능성 있는 지점

	// 우선 OBB에서 캡슐 선분을 향하는 방향 벡터 계산
	// 박스에서 선분(p1~p2) 전체에 대해 가장 가까운 점 찾기
	// 가장 가까운 지점은 보통 "OBB의 외부 점"에 대해서 OBB 표면에 투영

	// 여기서는 OBB의 가장 가까운 점을 구하기 위해 선분을 하나의 점이라고 보고 시작
	// 캡슐 선분과 OBB가 서로 영향을 주므로, OBB 중심에 대해 먼저 closest point 찾기

	// OBB에서 캡슐 중심선분과 가장 가까운 점을 구하기 위해 샘플링
	const int steps = 10;
	float minDist = FLT_MAX;
	Vector3 closestOnBox;
	Vector3 closestOnCapsule;

	for (int i = 0; i <= steps; ++i)
	{
		float t = static_cast<float>(i) / steps;
		Vector3 sample = GameMath::Lerp(p1, p2, t);

		// OBB에 대해 sample 점에서 가장 가까운 지점 구하기
		Vector3 point = box.center;
		Vector3 dir = sample - box.center;

		for (int axis = 0; axis < 3; ++axis)
		{
			float distOnAxis = Vector3::Dot(dir, box.axis[axis]);
			float clamped = GameMath::Clamp(distOnAxis, -box.halfSize[axis], box.halfSize[axis]);
			point += box.axis[axis] * clamped;
		}

		float dist = Vector3::Distance(sample, point);
		if (dist < minDist)
		{
			minDist = dist;
			closestOnCapsule = sample;
			closestOnBox = point;
		}
	}

	// === 2. 가장 가까운 위치를 기준으로 가상의 Sphere 생성 ===
	// Sphere 중심은 closestOnCapsule, 반지름은 capsule->Radius()

	// === 3. OBB와 해당 Sphere의 충돌 검사 ===
	// OBB에서 closestOnCapsule에 가장 가까운 점 다시 구함 (정확한 거리)
	Vector3 point = box.center;
	Vector3 dir = closestOnCapsule - box.center;

	for (int axis = 0; axis < 3; ++axis)
	{
		float distOnAxis = Vector3::Dot(dir, box.axis[axis]);
		float clamped = GameMath::Clamp(distOnAxis, -box.halfSize[axis], box.halfSize[axis]);
		point += box.axis[axis] * clamped;
	}

	float finalDist = Vector3::Distance(closestOnCapsule, point);
	return finalDist <= radius;
}





void BoxCollider::GetOBB(ObbDesc& desc)
{	
	desc.center = GetGlobalPosition();
	desc.axis[0] = GetRight();
	desc.axis[1] = GetUp();
	desc.axis[2] = GetForward();
	desc.halfSize = size * 0.5f * GetGlobalScale();
}

void BoxCollider::Edit()
{
	Transform::Edit();
	if (ImGui::DragFloat3("Size", (float*)&size, 0.1f, 0.1f, 100.0f))
	{
		UpdateMesh();
	}
}

void BoxCollider::UpdateMesh()
{
	Vector3 halfSize = size * 0.5f;
	vector<Vertex>& vertices = mesh->GetVertices();
	vertices.clear();

	vertices.emplace_back(-halfSize.x, +halfSize.y, -halfSize.z);
	vertices.emplace_back(+halfSize.x, +halfSize.y, -halfSize.z);
	vertices.emplace_back(+halfSize.x, -halfSize.y, -halfSize.z);
	vertices.emplace_back(-halfSize.x, -halfSize.y, -halfSize.z);

	vertices.emplace_back(-halfSize.x, +halfSize.y, +halfSize.z);
	vertices.emplace_back(+halfSize.x, +halfSize.y, +halfSize.z);
	vertices.emplace_back(+halfSize.x, -halfSize.y, +halfSize.z);
	vertices.emplace_back(-halfSize.x, -halfSize.y, +halfSize.z);

	mesh->UpdateVertices();
}

void BoxCollider::SaveBox()
{
}

void BoxCollider::LoadBox()
{
}

bool BoxCollider::IsSeperateAxis(Vector3 D, Vector3 axis, ObbDesc box1, ObbDesc box2)
{
	float distance = abs(Vector3::Dot(D, axis));

	float a = 0.0f;
	float b = 0.0f;

	for (UINT i = 0; i < 3; i++)
	{
		Vector3 temp = box1.axis[i] * box1.halfSize[i];
		a += abs(Vector3::Dot(temp, axis));
		temp = box2.axis[i] * box2.halfSize[i];
		b += abs(Vector3::Dot(temp, axis));
	}

	return distance > a + b;
}

void BoxCollider::MakeMesh()
{
	Vector3 halfSize = size * 0.5f;
	vector<Vertex>& vertices = mesh->GetVertices();
	
	vertices.emplace_back(-halfSize.x, +halfSize.y, -halfSize.z);
	vertices.emplace_back(+halfSize.x, +halfSize.y, -halfSize.z);
	vertices.emplace_back(+halfSize.x, -halfSize.y, -halfSize.z);
	vertices.emplace_back(-halfSize.x, -halfSize.y, -halfSize.z);
    
	vertices.emplace_back(-halfSize.x, +halfSize.y, +halfSize.z);
	vertices.emplace_back(+halfSize.x, +halfSize.y, +halfSize.z);
	vertices.emplace_back(+halfSize.x, -halfSize.y, +halfSize.z);
	vertices.emplace_back(-halfSize.x, -halfSize.y, +halfSize.z);

	vector<UINT>& indices = mesh->GetIndices();
	indices = {
		0, 1, 3, 2, 4, 5, 7, 6,
		0, 3, 1, 2, 4, 7, 5, 6,
		0, 4, 1, 5, 3, 7, 2, 6
	};
}
