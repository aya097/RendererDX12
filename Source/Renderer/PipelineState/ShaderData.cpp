#include "ShaderData.h"

ShaderData::ShaderData(std::wstring shaderPath)
{
	_shaderPath = shaderPath;
}

void ShaderData::SetShader(std::wstring fileName, ShaderType shaderType, std::string entryPoint)
{
	// マップに追加
	_shaderBlobs[shaderType] = nullptr;
	// シェーダーのフルパス
	std::wstring shaderFullPath = _shaderPath + fileName;

	ID3DBlob* errorBlob = nullptr;
	auto result = D3DCompileFromFile(
		shaderFullPath.c_str(),	// シェーダーのファイル名
		nullptr,	// シェーダーマクロは使用しない
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	// カレントディレクトリからインクルード
		entryPoint.c_str(),	// シェーダーのエントリーポイント
		GetShaderTarget(shaderType).c_str(),	// シェーダーターゲット
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,	// デバッグあり、最適化なし
		0,	// エフェクトコンパイルオプション
		&_shaderBlobs.at(shaderType),	// 適切なシェーダータイプ
		&errorBlob	// エラー用
	);

	if (FAILED(result))
	{
		// シェーダーファイルが見つからない場合
		if (result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
		{
			assert(false && "Shader file is not found");
		}
		else if (result == HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND))
		{
			assert(false && "Shader path is not found");
		}
		else
		{
			std::string errorString;
			errorString.resize(errorBlob->GetBufferSize());
			// エラーのバイナリをstringに変換
			std::copy_n((char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize(), errorString.begin());
			assert(false && errorString.c_str());

		}
	}
}

ID3DBlob* ShaderData::GetShader(ShaderType shaderType) const
{
	if (_shaderBlobs.contains(shaderType))
	{
		return _shaderBlobs.at(shaderType);
	}
	return nullptr;
}

std::string ShaderData::GetShaderTarget(ShaderType shaderType)
{
	switch (shaderType)
	{
	case VS:
		return "vs_5_0";
		break;
	case PS:
		return "ps_5_0";
		break;
	default:
		break;
	}
}

