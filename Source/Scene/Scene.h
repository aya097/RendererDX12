#pragma once
#include "../Model/Mesh.h"
#include "../Renderer/PipelineState/RootSignature.h" 
#include "../Renderer/PipelineState/ShaderData.h"

// オブジェクトの生成から描画までのフローを提供するクラス
class Scene
{
public:
	void Init();	// 初期化処理
	void Update();	// 毎フレームの更新処理
	void Draw();	// 描画処理

private:
	std::vector<std::shared_ptr<Mesh>> _meshes;
};

extern Scene* g_Scene;	// 単一利用を想定、最終的には基底クラスとし、自由にシーンを作成予定