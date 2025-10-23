#pragma once

class BoxCollider : public Collider
{
public:
	struct ObbDesc
	{
		Vector3 center;
		Vector3 axis[3];
		Vector3 halfSize;
	};

public:
	BoxCollider(Vector3 size = Vector3(1, 1, 1));
	~BoxCollider();

	bool IsRayCollision(const Ray& ray, RayHit* hitInfo) override;
	bool IsBoxCollision(BoxCollider* collider) override;
	bool IsSphereCollision(SphereCollider* collider) override;
	bool IsCapsuleCollision(CapsuleCollider* collider) override;
	bool IsPointCollision(const Vector3 pos);

	void GetOBB(ObbDesc& desc);

	void Edit();
	void UpdateMesh();

	void SaveBox();
	void LoadBox();
	Vector3 GetSize() { return size; }
	void SetSize(Vector3 size) { this->size = size; UpdateMesh(); }

private:
	bool IsSeperateAxis(Vector3 D, Vector3 axis, ObbDesc box1, ObbDesc box2);

private:
	void MakeMesh() override;

private:
	Vector3 size;
};
