#ifndef __INCLUDED_DX10_HOOK_H__
#define __INCLUDED_DX10_HOOK_H__

#include <d3d10.h>
#include "DirectX_VTables.h"
#include "Base_Hook.h"

class DX10_Hook : public Base_Hook
{
public:
    static constexpr const char *DLL_NAME = "d3d10.dll";

private:
    // Variables
    bool initialized;
    ID3D10Device* pDevice;
    ID3D10RenderTargetView* mainRenderTargetView;

    // Functions
    DX10_Hook();
    virtual ~DX10_Hook();

    void hook_dx10(UINT SDKVersion);
    void resetRenderState();
    void prepareForOverlay(IDXGISwapChain *pSwapChain);

    // Hook to render functions
    static HRESULT STDMETHODCALLTYPE MyPresent(IDXGISwapChain* _this, UINT SyncInterval, UINT Flags);
    static HRESULT STDMETHODCALLTYPE MyResizeTarget(IDXGISwapChain* _this, const DXGI_MODE_DESC* pNewTargetParameters);
    static HRESULT STDMETHODCALLTYPE MyResizeBuffers(IDXGISwapChain* _this, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

    decltype(&IDXGISwapChain::Present)       Present;
    decltype(&IDXGISwapChain::ResizeBuffers) ResizeBuffers;
    decltype(&IDXGISwapChain::ResizeTarget)  ResizeTarget;

    // Hook functions so we know we use DX10
    //static decltype(D3D10CreateDevice) MyD3D10CreateDevice;
    static decltype(D3D10CreateDeviceAndSwapChain) MyD3D10CreateDeviceAndSwapChain;

    //decltype(D3D10CreateDevice)* _D3D10CreateDevice;
    decltype(D3D10CreateDeviceAndSwapChain)* D3D10CreateDeviceAndSwapChain;

public:
    static void Create(); // Initialize DX10 Hook.
    
    void loadFunctions(ID3D10Device *pDevice, IDXGISwapChain *pSwapChain);
};

#endif//__INCLUDED_DX10_HOOK_H__