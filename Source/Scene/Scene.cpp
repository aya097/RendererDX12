#include "Scene.h"

Scene* g_Scene;

void Scene::Init()
{
	// メッシュの頂点
	std::vector<XMFLOAT3> vertices =
	{
		{-0.7f, -0.9f, 0.0f},
		{-0.5f, 0.8f, 0.0f},
		{0.7f, -0.8f, 0.0f},
	};
	// メッシュの追加
	_meshes.push_back(std::make_shared<Mesh>(vertices));
	
	// ルートシグネチャ作成
	std::shared_ptr<RootSignature> rootSignature = std::make_shared<RootSignature>();
	
	// シェーダー作成
	std::shared_ptr<ShaderData> shaderData = std::make_shared<ShaderData>();
	shaderData->SetShader(L"BasicVertexShader.hlsl", ShaderType::VS);
	shaderData->SetShader(L"BasicPixelShader.hlsl", ShaderType::PS);
	
	// パイプラインステート作成
	std::unique_ptr<PipelineState> pipelineState = std::make_unique<PipelineState>(rootSignature,shaderData);

}

void Scene::Update()
{

}

void Scene::Draw()
{

}