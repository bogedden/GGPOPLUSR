#include "ID3D9Wrapper.h"
#include "ID3D9Wrapper_Device.h"

Direct3D9Wrapper::Direct3D9Wrapper(IDirect3D9 **ppIDirect3D9)
{
	Direct3D9 = *ppIDirect3D9;
	*ppIDirect3D9 = this;
}

Direct3D9Wrapper::~Direct3D9Wrapper() {}

HRESULT APIENTRY Direct3D9Wrapper::QueryInterface(const IID &riid, void **ppvObj)
{
	HRESULT hRes = Direct3D9->QueryInterface(riid, ppvObj);
	if (hRes == S_OK)
		*ppvObj = this;
	else
		*ppvObj = NULL;

	return hRes;
}

ULONG APIENTRY Direct3D9Wrapper::AddRef()
{
	return Direct3D9->AddRef();
}

ULONG APIENTRY Direct3D9Wrapper::Release()
{
	ULONG res = Direct3D9->Release();
	if (res == 0) {
		delete this;
	}

	return res;
}

HRESULT APIENTRY Direct3D9Wrapper::RegisterSoftwareDevice(void* pInitializeFunction)
{
	return Direct3D9->RegisterSoftwareDevice(pInitializeFunction);
}

UINT APIENTRY Direct3D9Wrapper::GetAdapterCount()
{
	return Direct3D9->GetAdapterCount();
}

HRESULT APIENTRY Direct3D9Wrapper::GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9* pIdentifier)
{
	return Direct3D9->GetAdapterIdentifier(Adapter, Flags, pIdentifier);
}

UINT APIENTRY Direct3D9Wrapper::GetAdapterModeCount(UINT Adapter, D3DFORMAT Format)
{
	return Direct3D9->GetAdapterModeCount(Adapter, Format);
}

HRESULT APIENTRY Direct3D9Wrapper::EnumAdapterModes(UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE* pMode)
{
	return Direct3D9->EnumAdapterModes(Adapter, Format, Mode, pMode);
}

HRESULT APIENTRY Direct3D9Wrapper::GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode)
{
	return Direct3D9->GetAdapterDisplayMode(Adapter, pMode);
}

HRESULT APIENTRY Direct3D9Wrapper::CheckDeviceType(UINT Adapter, D3DDEVTYPE DevType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed)
{
	return Direct3D9->CheckDeviceType(Adapter, DevType, AdapterFormat, BackBufferFormat, bWindowed);
}

HRESULT APIENTRY Direct3D9Wrapper::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat)
{
	return Direct3D9->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}

HRESULT APIENTRY Direct3D9Wrapper::CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD* pQualityLevels)
{
	return Direct3D9->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels);
}

HRESULT APIENTRY Direct3D9Wrapper::CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat)
{
	return Direct3D9->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}

HRESULT APIENTRY Direct3D9Wrapper::CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat)
{
	return Direct3D9->CheckDeviceFormatConversion(Adapter, DeviceType, SourceFormat, TargetFormat);
}

HRESULT APIENTRY Direct3D9Wrapper::GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9* pCaps)
{
	return Direct3D9->GetDeviceCaps(Adapter, DeviceType, pCaps);
}

HMONITOR APIENTRY Direct3D9Wrapper::GetAdapterMonitor(UINT Adapter)
{
	return Direct3D9->GetAdapterMonitor(Adapter);
}

HRESULT APIENTRY Direct3D9Wrapper::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DDevice9 **ppReturnedDeviceInterface)
{
	HRESULT hRet = Direct3D9->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);
	if (SUCCEEDED(hRet))
	{
		Direct3DDevice9Wrapper *ret = new Direct3DDevice9Wrapper(ppReturnedDeviceInterface, pPresentationParameters, this);
	}

	return hRet;
}