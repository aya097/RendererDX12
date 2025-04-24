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
	ShaderData();
	void SetVS(LPCWSTR fileName);
	void SetPS(LPCWSTR fileName);

};