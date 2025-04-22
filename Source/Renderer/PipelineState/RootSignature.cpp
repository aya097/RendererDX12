#include "RootSignature.h"

RootSignature::RootSignature()
{
	// ルートシグネチャの設定ファイル
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT; // 頂点情報

	ID3DBlob* rootBlob = nullptr;	// バイナリコード
	ID3DBlob* errorBlob = nullptr;	// エラーコード

	// バイナリコード作成
	auto result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &rootBlob, &errorBlob);

	if (FAILED(result))
	{
		assert(false && "Serialize RootSignature is failed");
	}

	// ルートシグネチャ作成
	result = g_GraphicsDevice->GetDevice()->CreateRootSignature(
		0,	// nodemask
		rootBlob->GetBufferPointer(),	// バイナリのポインタ
		rootBlob->GetBufferSize(),		// バイナリのサイズ
		IID_PPV_ARGS(&_rootSignature));

	if (FAILED(result))
	{
		assert(false && "Create RootSignature is failed");
	}

	rootBlob->Release();
}