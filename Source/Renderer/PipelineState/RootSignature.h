#pragma once
#include "../GraphicsDevice.h"

// RootSignatureのラップクラス、ディスクリプタテーブルをまとめたもの
class RootSignature
{
public:
	RootSignature();
	ID3D12RootSignature* GetRootSignature() const { return _rootSignature.Get(); }

private:
	ComPtr<ID3D12RootSignature> _rootSignature = nullptr;
};