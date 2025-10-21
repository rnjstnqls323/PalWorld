#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	vertexShader = Shader::AddVS(L"Tutorial.hlsl");
	pixelShader = Shader::AddPS(L"Tutorial.hlsl");

	vertices.emplace_back(-1, -1, -1, 1, 0, 0);
	vertices.emplace_back(-1, +1, -1, 0, 1, 0);
	vertices.emplace_back(+1, -1, -1, 0, 0, 1);	
	vertices.emplace_back(+1, +1, -1, 1, 1, 0);

	vertices.emplace_back(-1, -1, +1, 1, 0, 0);
	vertices.emplace_back(-1, +1, +1, 0, 1, 0);
	vertices.emplace_back(+1, -1, +1, 0, 0, 1);
	vertices.emplace_back(+1, +1, +1, 1, 1, 0);

	indices = { 
		//Front
		0, 1, 2, 2, 1, 3,
		//Up
		1, 5, 3, 3, 5, 7,
	};

	vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexColor), (UINT)vertices.size());
	indexBuffer = new IndexBuffer(indices.data(), (UINT)indices.size());

	worldBuffer = new MatrixBuffer();
	worldBuffer->Set(XMMatrixIdentity());
	worldBuffer->SetVS(0);
}

TutorialScene::~TutorialScene()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete worldBuffer;
}

void TutorialScene::Update()
{
}

void TutorialScene::PreRender()
{
}

void TutorialScene::Render()
{
	vertexBuffer->Set();
	indexBuffer->Set();

	vertexShader->Set();
	pixelShader->Set();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void TutorialScene::PostRender()
{
}

void TutorialScene::GUIRender()
{
}
