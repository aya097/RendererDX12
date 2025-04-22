#pragma once
#include "../GraphicsDevice.h"

// RootSignatureのラップクラス、ディスクリプタテーブルをまとめたもの
class RootSignature
{
public:
	RootSignature();
	

private:
	ComPtr<ID3D12RootSignature> _rootSignature = nullptr;
};