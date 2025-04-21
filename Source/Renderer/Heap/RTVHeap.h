#pragma 

class RTVHeap
{
public:
	RTVHeap(ID3D12Device* device, int useNum);	// ヒープを生成
	void RegistRTVHeap(ID3D12Resource* buffer, int index);	// ヒープに紐づけ
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandleAt(int index);

private:
	ID3D12Device* _device = nullptr;// RTVHeapの寿命はDeviceの寿命以下
	ComPtr<ID3D12DescriptorHeap> _heap = nullptr;
};