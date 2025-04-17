#include "RTVHeap.h"

RTVHeap::RTVHeap(ID3D12Device* device, int useNum)
{
	_device = device;
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	heapDesc.NodeMask = 0;
	heapDesc.NumDescriptors = useNum;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	auto result = device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&_heap));

	if (FAILED(result))
	{
		assert(false && "CreateDescriptorHeap is failed");
	}
}

void RTVHeap::RegistRTVHeap(ID3D12Resource* buffer, int index)
{
	_device->CreateRenderTargetView(buffer, nullptr, GetCPUHandleAt(index));
}

D3D12_CPU_DESCRIPTOR_HANDLE RTVHeap::GetCPUHandleAt(int index)
{
	D3D12_CPU_DESCRIPTOR_HANDLE handle = _heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += _device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV) * index;
	return handle;
}

