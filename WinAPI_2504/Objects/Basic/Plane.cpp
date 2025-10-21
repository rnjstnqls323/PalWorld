#include "Framework.h"

Plane::Plane(Vector2 size) : size(size)
{
	tag = "Plane";

	mesh = new Mesh<VertexType>();
	MakeMesh();
	MakeNormal(mesh);
	MakeTangent(mesh);
	mesh->CreateMesh();
}

Plane::~Plane()
{
	delete mesh;
}

void Plane::Render()
{
	if (!isActive) return;

	SetRender();
	mesh->Draw();
}

void Plane::MakeMesh()
{
	Vector2 halfSize = size * 0.5f;
	Vector3 startPos = { -halfSize.x, 0.0f, -halfSize.y };

	UINT width = (UINT)size.x;
	UINT height = (UINT)size.y;

	vector<VertexType>& vertices = mesh->GetVertices();
	vertices.reserve((width + 1) * (height + 1));

	for (UINT z = 0; z <= height; z++)
	{
		for (UINT x = 0; x <= width; x++)
		{
			float u = (float)x / size.x;
			float v = (float)z / size.y;

			vertices.emplace_back(startPos.x + x, startPos.y, startPos.z + z, u, v);
		}
	}

	vector<UINT>& indices = mesh->GetIndices();
	indices.reserve((width * height) * 6);

	for (UINT z = 0; z < width; z++)
	{
		for (UINT x = 0; x < height; x++)
		{
			indices.push_back(z * (width + 1) + x);//0
			indices.push_back((z + 1) * (width + 1) + x);//1
			indices.push_back((z + 1) * (width + 1) + x + 1);//2

			indices.push_back(z * (width + 1) + x);//0
			indices.push_back((z + 1) * (width + 1) + x + 1);//2
			indices.push_back(z * (width + 1) + x + 1);//3
		}
	}
}
