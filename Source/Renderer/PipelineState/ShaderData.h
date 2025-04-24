#pragma once

enum ShaderType
{
	VS,
	PS,
};

/// <summary>
/// パイプラインステートにシェーダーデータを渡すためのクラス
/// </summary>
class ShaderData
{
public:
	ShaderData(std::wstring shaderPath = L"../Asset/Shader/");
	// シェーダーをセットしBlobを生成
	void SetShader(std::wstring fileName, ShaderType shaderType, std::string entryPoint = "main");
	// ShaderTypeに応じて、Blobを返す
	ID3DBlob* GetShader(ShaderType shaderType) const;

private:
	// ShaderTypeから"vs_5_0"などのターゲットを取得
	std::string GetShaderTarget(ShaderType shaderType);
	
	std::unordered_map<ShaderType, ID3DBlob*> _shaderBlobs;	// シェーダーのデータを格納するMap
	std::wstring _shaderPath;
};