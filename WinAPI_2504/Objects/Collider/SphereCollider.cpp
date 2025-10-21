#include "Framework.h"

SphereCollider::SphereCollider(float radius, UINT stackCount, UINT sliceCount)
	: radius(radius), stackCount(stackCount), sliceCount(sliceCount)
{
    type = Type::Sphere;

    MakeMesh();
    mesh->CreateMesh();
}

bool SphereCollider::IsRayCollision(const Ray& ray, RayHit* hitInfo)
{
	UpdateWorld();

	Vector3 P = ray.origin;
	Vector3 D = ray.direction;

	Vector3 C = GetGlobalPosition();
	Vector3 A = P - C;
		
	float b = Vector3::Dot(A, D);
	float c = Vector3::Dot(A, A) - Radius() * Radius();

	if (b * b >= c)
	{
		if (hitInfo)
		{
			hitInfo->isHit = true;
			hitInfo->distance = -b - sqrt(b * b - c);
			hitInfo->position = P + D * hitInfo->distance;
			hitInfo->normal = (hitInfo->position - C).GetNormalized();
		}

		return true;
	}

    return false;
}

bool SphereCollider::IsBoxCollision(BoxCollider* collider)
{
	return collider->IsSphereCollision(this);
}

bool SphereCollider::IsSphereCollision(SphereCollider* collider)
{
	float scaledRadiusA = radius * GetGlobalScale().x;  // ���� x,y,z �������� ���ٰ� �����ϰų�
	float scaledRadiusB = collider->radius * collider->GetGlobalScale().x;

	float distance = Vector3::Distance(GetGlobalPosition(), collider->GetGlobalPosition());
	float radiusSum = scaledRadiusA + scaledRadiusB;

	return distance <= radiusSum;
}

bool SphereCollider::IsCapsuleCollision(CapsuleCollider* capsule)
{
	Vector3 capsuleStart = capsule->GetStartPoint();
	Vector3 capsuleEnd = capsule->GetEndPoint();
	float capsuleRadius = capsule->Radius();

	Vector3 sphereCenter = this->GetGlobalPosition();  // ���Ǿ� �߽�
	float sphereRadius = this->Radius();

	// === 1. ���� �߽ɿ��� ĸ�� ���п� ���� ����� �� ���ϱ� ===
	Vector3 closestPoint = GameMath::ClosestPointOnLineSegment(sphereCenter, capsuleStart, capsuleEnd);

	// === 2. ���� ����� ���� ���� �߽� ���� �Ÿ� ��� ===
	float distance = Vector3::Distance(closestPoint, sphereCenter);

	// === 3. �� ������ �պ��� ������ �浹 ===
	return distance <= (capsuleRadius + sphereRadius);
}

void SphereCollider::MakeMesh()
{
	float thetaStep = XM_2PI / sliceCount;
	float phiStep = XM_PI / stackCount;

	vector<Vertex>& vertices = mesh->GetVertices();
	vertices.reserve((stackCount + 1) * (sliceCount + 1));

	for (UINT i = 0; i <= stackCount; i++)
	{
		float phi = i * phiStep;

		for (UINT j = 0; j <= sliceCount; j++)
		{
			float theta = j * thetaStep;

			float x = cos(theta) * sin(phi) * radius;
			float y = cos(phi) * radius;
			float z = sin(theta) * sin(phi) * radius;
			
			vertices.emplace_back(x, y, z);
		}
	}

	vector<UINT>& indices = mesh->GetIndices();	
	indices.reserve(stackCount * sliceCount * 4);

	for (UINT i = 0; i < stackCount; i++)
	{
		for (UINT j = 0; j < sliceCount; j++)
		{
			indices.push_back(i * (sliceCount + 1) + j);//0
			indices.push_back((i + 1) * (sliceCount + 1) + j);//1

			indices.push_back(i * (sliceCount + 1) + j);//0
			indices.push_back(i * (sliceCount + 1) + j + 1);//2
		}
	}
}
