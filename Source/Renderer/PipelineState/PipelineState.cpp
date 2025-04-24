#include "PipelineState.h"

PipelineState::PipelineState(std::shared_ptr<RootSignature> rootSignature, std::shared_ptr<ShaderData> shaderData)
{
	// 頂点レイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] =
	{
		{
			"POSITION",	// セマンティクス名
			0,	// セマンティクスインデクス
			DXGI_FORMAT_R32G32B32_FLOAT,	// フォーマット
			0,	// 入力スロットインデクス
			D3D12_APPEND_ALIGNED_ELEMENT,	// データが連続
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0	// インスタンシングを利用しない
		},
	};

	// パイプラインステート設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineStateDesc = {};

	// ルートシグネチャをセット
	pipelineStateDesc.pRootSignature = rootSignature->GetRootSignature();

	// シェーダーをセット
	// 頂点シェーダー
	if (shaderData->GetShader(ShaderType::VS))
	{
		pipelineStateDesc.VS.pShaderBytecode = shaderData->GetShader(ShaderType::VS)->GetBufferPointer();
		pipelineStateDesc.VS.BytecodeLength = shaderData->GetShader(ShaderType::VS)->GetBufferSize();
	}
	else
	{
		assert(false && "Vertex Shader is null");
	}

	// ピクセルシェーダー
	if (shaderData->GetShader(ShaderType::PS))
	{
		pipelineStateDesc.PS.pShaderBytecode = shaderData->GetShader(ShaderType::PS)->GetBufferPointer();
		pipelineStateDesc.PS.BytecodeLength = shaderData->GetShader(ShaderType::PS)->GetBufferSize();
	}
	else
	{
		assert(false && "Pixel Shader is null");

	}

	// サンプルマスク
	pipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;	// デフォルト

	// ラスタライザー
	pipelineStateDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;	// カリングしない
	pipelineStateDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;	// 中身を塗りつぶす
	pipelineStateDesc.RasterizerState.DepthClipEnable = true;	// 深度方向クリップをおこなう

	// ブレンドステート
	D3D12_RENDER_TARGET_BLEND_DESC blendDesc = {};
	blendDesc.BlendEnable = false;
	blendDesc.LogicOpEnable = false;
	blendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	pipelineStateDesc.BlendState.RenderTarget[0] = blendDesc;

	// 頂点レイアウト
	pipelineStateDesc.InputLayout.pInputElementDescs = inputLayout;
	pipelineStateDesc.InputLayout.NumElements = _countof(inputLayout);

	// カットしない
	pipelineStateDesc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;

	// プリミティブトポロジー
	pipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	// レンダーターゲット
	pipelineStateDesc.NumRenderTargets = 1;	// 1つだけ
	pipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;	// 正規化されたRGBA

	// アンチエイリアス
	pipelineStateDesc.SampleDesc.Count = 1;	// 1ピクセルにつき1サンプル
	pipelineStateDesc.SampleDesc.Quality = 0;	// 最低品質

	// パイプラインステート作成
	auto result = g_GraphicsDevice->GetDevice()->CreateGraphicsPipelineState(
		&pipelineStateDesc,
		IID_PPV_ARGS(&_pipelineState)
	);

	if (FAILED(result))
	{
		assert(false && "Create PipelineState is failed");
	}
}
