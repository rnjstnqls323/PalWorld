#pragma once

struct Vertex//���� : 3���� ���������� �� ��
{
    float x, y, z;    

    Vertex(float x = 0, float y = 0, float z = 0)
        : x(x), y(y), z(z)
    {
    }
};

struct VertexColor//���� : 3���� ���������� �� ��
{
    Float3 pos;
    Float4 color;

	VertexColor() : pos(0, 0, 0), color(1, 1, 1, 1)
	{
	}
	VertexColor(float x, float y, float z, float r, float g, float b, float a = 1.0f)
		: pos(x, y, z), color(r, g, b, a)
	{
	}
};

struct VertexUV//���� : 3���� ���������� �� ��
{
    float x, y, z;
	float u, v; // Texture coordinates

    VertexUV(float x = 0, float y = 0, float z = 0, float u = 0, float v = 0)
		: x(x), y(y), z(z), u(u), v(v)
    {
    }
};

struct VertexUVNormal
{
    Float3 pos = {};
    Float2 uv = {};
    Float3 normal = {};

    VertexUVNormal()		
    {
    }

    VertexUVNormal(float x, float y, float z, float u, float v)
        : pos(x, y, z), uv(u, v)
    {
    }
};

struct VertexUVNormalTangent
{
    Float3 pos = {};
    Float2 uv = {};
    Float3 normal = {};
	Float3 tangent = {};

    VertexUVNormalTangent()
    {
    }

    VertexUVNormalTangent(float x, float y, float z, float u, float v)
        : pos(x, y, z), uv(u, v)
    {
    }
};

struct VertexUVNormalTangentBlend
{
    Float3 pos = {};
    Float2 uv = {};
    Float3 normal = {};
    Float3 tangent = {};
	Float4 indices = {};
	Float4 weights = {};

    VertexUVNormalTangentBlend()
    {
    }

    VertexUVNormalTangentBlend(float x, float y, float z, float u, float v)
        : pos(x, y, z), uv(u, v)
    {
    }
};

struct InstanceData
{
	Matrix world;

	Float2 curFrame;
	Float2 maxFrame;
};