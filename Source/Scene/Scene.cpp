#include "Scene.h"

Scene* g_Scene;

void Scene::Init()
{
	std::vector<XMFLOAT3> vertices =
	{
		{-0.7f, -0.9f, 0.0f},
		{-0.5f, 0.8f, 0.0f},
		{0.7f, -0.8f, 0.0f},
	};
	_meshes.push_back(std::make_shared<Mesh>(vertices));
	std::unique_ptr<RootSignature> rootSignature = std::make_unique<RootSignature>();
	std::unique_ptr<ShaderData> shaderData = std::make_unique<ShaderData>();


}

void Scene::Update()
{

}

void Scene::Draw()
{

}