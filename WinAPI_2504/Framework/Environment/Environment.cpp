#include "Framework.h"
#include "Environment.h"

Environment::Environment()
{
	grid = new Grid();
	mainCamera = new Camera();
	mainCamera->Load();
	uiViewBuffer = new MatrixBuffer();
	lightBuffer = new LightBuffer();

	CreateProjection();
    CreateSamplerState();
	//CreateBlendState();
	CreateStats();
}

Environment::~Environment()
{
	delete grid;
	mainCamera->Save();
	delete mainCamera;
	delete projectionBuffer;
	delete uiViewBuffer;
	delete lightBuffer;

	delete rasterizerState[0];
	delete rasterizerState[1];

    samplerState->Release();
	//alphaBlendState->Release();
}

void Environment::Update()
{
	if (Input::Get()->IsKeyDown(VK_F1))
	{
		Collider::SwitchDraw();
	}

	if (Input::Get()->IsKeyDown(VK_F2))
	{
		isWireFrame = !isWireFrame;		
	}

	mainCamera->Update();
}

void Environment::Edit()
{
	mainCamera->Edit();

	ImGui::Text("Light Option");

	ImGui::ColorEdit3("AmbientLight", (float*)&lightBuffer->GetData()->ambientLight);
	ImGui::ColorEdit3("AmbientCeil", (float*)&lightBuffer->GetData()->ambientCeil);

	if (ImGui::Button("Add"))
		lightBuffer->GetData()->lightCount++;	

	for (UINT i = 0; i < lightBuffer->GetData()->lightCount; i++)
	{
		string name = "Light " + to_string(i);

		if (ImGui::TreeNode(name.c_str()))
		{
			EditLight(lightBuffer->GetData()->lights[i]);
			ImGui::TreePop();
		}
	}
}

void Environment::SetViewport(UINT width, UINT height)
{
	D3D11_VIEWPORT viewport;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	DC->RSSetViewports(1, &viewport);	
}

void Environment::SetRender()
{
	SetViewport();

	projectionBuffer->Set(perspective);
	projectionBuffer->SetVS(2);

	rasterizerState[isWireFrame]->SetState();

	grid->Render();

	lightBuffer->SetPS(1);
}

void Environment::SetPostRender()
{
	uiViewBuffer->SetVS(1);	

	projectionBuffer->Set(orthographic);
	projectionBuffer->SetVS(2);
}

LightBuffer::Light* Environment::AddLight()
{
	lightBuffer->GetData()->lightCount++;

	return &lightBuffer->GetData()->lights[lightBuffer->GetData()->lightCount - 1];
}

void Environment::CreateProjection()
{   
    projectionBuffer = new MatrixBuffer();

    //Orthographic : ���ٰ��� ���� ������ü�� ����ü�� �����ϴ� ������ȯ
    orthographic = XMMatrixOrthographicOffCenterLH(0.0f,
		SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT, -1.0f, 1.0f);
	//Perspective : ���ٰ��� �ִ� ������ȯ
	perspective = XMMatrixPerspectiveFovLH(PI * 0.25f,
		SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.f);
    
    projectionBuffer->SetVS(2);
}

void Environment::CreateSamplerState()
{
	D3D11_SAMPLER_DESC desc = {};
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	desc.MinLOD = 0;
	desc.MaxLOD = D3D11_FLOAT32_MAX;
	//LOD(Level Of Detail) : ī�޶���� �Ÿ��� ���� ����Ƽ�� ������ ���

	DEVICE->CreateSamplerState(&desc, &samplerState);

	DC->PSSetSamplers(0, 1, &samplerState);
}

void Environment::CreateBlendState()
{
	D3D11_BLEND_DESC desc = {};
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	DEVICE->CreateBlendState(&desc, &alphaBlendState);

	float blendFactor[4] = {};
	DC->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff);
}

void Environment::CreateStats()
{
	rasterizerState[0] = new RasterizerState();
	rasterizerState[1] = new RasterizerState();
	rasterizerState[1]->FillMode(D3D11_FILL_WIREFRAME);
}

void Environment::EditLight(LightBuffer::Light& light)
{
	ImGui::Checkbox("Active", (bool*)&light.active);

	const char* items[] = { "Directional", "Point", "Spot", "Capsule" };
	ImGui::Combo("Type", (int*)&light.type, items, IM_ARRAYSIZE(items));

	ImGui::ColorEdit3("Color", (float*)&light.color);
	ImGui::SliderFloat3("Direction", (float*)&light.direction, -1, 1);
	ImGui::DragFloat3("Position", (float*)&light.position);
	ImGui::SliderFloat("Range", &light.range, 0, 500);
	ImGui::SliderFloat("Inner", &light.inner, 0, 180);
	ImGui::SliderFloat("Outer", &light.outer, 0, 180);
	ImGui::DragFloat("Length", &light.length, 0.1f, 10);
}
