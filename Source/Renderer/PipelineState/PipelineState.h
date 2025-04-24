#pragma once
#include "RootSignature.h"
#include "ShaderData.h"

/// <summary>
/// パイプラインステートに関するクラス
/// </summary>
class PipelineState
{
public:
	PipelineState(std::shared_ptr<RootSignature> rootSignature, std::shared_ptr<ShaderData> shaderData);

private:
	ComPtr<ID3D12PipelineState> _pipelineState = nullptr;
};