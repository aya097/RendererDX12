#pragma 

class RTVHeap
{
public:
	RTVHeap(ID3D12Device* device, int useNum);
	void RegistRTVHeap(ID3D12Resource* buffer, int index);
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandleAt(int index);

private:
	ID3D12Device* _device = nullptr;// RTVHeap‚ÌŽõ–½‚ÍDevice‚ÌŽõ–½ˆÈ‰º
	ComPtr<ID3D12DescriptorHeap> _heap = nullptr;
};