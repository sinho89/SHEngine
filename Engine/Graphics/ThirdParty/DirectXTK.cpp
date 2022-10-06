#include "DirectXTK.h"
#include "DirectXTK/SharedResourcePool.h"
#include "DirectXTK/DemandCreate.h"

using Microsoft::WRL::ComPtr;
using namespace DirectX;

class CommonStatesEx::Impl
{
public:
    Impl(_In_ ID3D11Device* device) noexcept
        : mDevice(device)
    { }

    HRESULT CreateBlendState(D3D11_BLEND srcBlend, D3D11_BLEND destBlend, _Out_ ID3D11BlendState** pResult, const bool bAlphaToCoverage = false)
    {
        D3D11_BLEND_DESC desc = {};

        desc.AlphaToCoverageEnable = bAlphaToCoverage;

        desc.RenderTarget[0].BlendEnable = (srcBlend != D3D11_BLEND_ONE) ||
            (destBlend != D3D11_BLEND_ZERO);

        desc.RenderTarget[0].SrcBlend = desc.RenderTarget[0].SrcBlendAlpha = srcBlend;
        desc.RenderTarget[0].DestBlend = desc.RenderTarget[0].DestBlendAlpha = destBlend;
        desc.RenderTarget[0].BlendOp = desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

        desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

        HRESULT hr = mDevice->CreateBlendState(&desc, pResult);

        if (SUCCEEDED(hr))
            SetDebugObjectName(*pResult, "DirectXTK:CommonStatesEx");

        return hr;
    }
    HRESULT CreateReverseDepthStencilState(bool enable, bool writeEnable, _Out_ ID3D11DepthStencilState** pResult)
    {
        D3D11_DEPTH_STENCIL_DESC desc = {};

        desc.DepthEnable = enable ? TRUE : FALSE;
        desc.DepthWriteMask = writeEnable ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
        desc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;

        desc.StencilEnable = FALSE;
        desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
        desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

        desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
        desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

        desc.BackFace = desc.FrontFace;

        HRESULT hr = mDevice->CreateDepthStencilState(&desc, pResult);

        if (SUCCEEDED(hr))
            SetDebugObjectName(*pResult, "DirectXTK:CommonStatesEx");

        return hr;
    }
    HRESULT CreateRasterizerState(D3D11_CULL_MODE cullMode, D3D11_FILL_MODE fillMode, _Out_ ID3D11RasterizerState** pResult)
    {
        D3D11_RASTERIZER_DESC desc = {};

        desc.CullMode = cullMode;
        desc.FillMode = fillMode;
        desc.DepthClipEnable = TRUE;
        //desc.MultisampleEnable = FALSE;
        desc.MultisampleEnable = TRUE;

        HRESULT hr = mDevice->CreateRasterizerState(&desc, pResult);

        if (SUCCEEDED(hr))
            SetDebugObjectName(*pResult, "DirectXTK:CommonStatesEx");

        return hr;
    }
    HRESULT CreateSceneShadowRasterizerState(_Out_ ID3D11RasterizerState** pResult)
    {
        D3D11_RASTERIZER_DESC desc = {};
        desc.CullMode = D3D11_CULL_BACK;
        desc.FillMode = D3D11_FILL_SOLID;
        desc.DepthClipEnable = FALSE;
        desc.MultisampleEnable = FALSE;
        desc.DepthBias = 6000;
        desc.DepthBiasClamp = 0;
        desc.SlopeScaledDepthBias = 1.f;

        HRESULT hr = mDevice->CreateRasterizerState(&desc, pResult);

        if (SUCCEEDED(hr))
            SetDebugObjectName(*pResult, "DirectXTK:CommonStatesEx CreateSceneShadowRasterizerState");

        return hr;
    }
    HRESULT CreateSamplerState(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE addressMode, _Out_ ID3D11SamplerState** pResult)
    {
        D3D11_SAMPLER_DESC desc = {};

        desc.Filter = filter;

        desc.AddressU = addressMode;
        desc.AddressV = addressMode;
        desc.AddressW = addressMode;

        desc.MaxAnisotropy = (mDevice->GetFeatureLevel() > D3D_FEATURE_LEVEL_9_1) ? D3D11_MAX_MAXANISOTROPY : 2;

        desc.MaxLOD = FLT_MAX;
        desc.ComparisonFunc = D3D11_COMPARISON_NEVER;

        HRESULT hr = mDevice->CreateSamplerState(&desc, pResult);

        if (SUCCEEDED(hr))
            SetDebugObjectName(*pResult, "DirectXTK:CommonStatesEx");

        return hr;
    }
    HRESULT CreateSceneShadowSamplerState(_Out_ ID3D11SamplerState** pResult)
    {
        // https://docs.microsoft.com/ko-kr/windows/uwp/gaming/render-the-scene-with-depth-testing
        D3D11_SAMPLER_DESC desc = {};

        desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
        desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
        desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
        desc.BorderColor[0] = 1.0f;
        desc.BorderColor[1] = 1.0f;
        desc.BorderColor[2] = 1.0f;
        desc.BorderColor[3] = 1.0f;
        desc.MinLOD = 0.f;
        desc.MaxLOD = D3D11_FLOAT32_MAX;
        desc.MipLODBias = 0.f;
        desc.MaxAnisotropy = 16;
        desc.ComparisonFunc = D3D11_COMPARISON_GREATER; // D3D11_COMPARISON_LESS; Reverse-Z 대응
        //desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
        desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
        //desc.Filter = D3D11_FILTER_COMPARISON_ANISOTROPIC;
        // Merge.hlsl의 epsilon을 꺼보면 차이를 쉽게 파악 할 수 있다.

        //{
        //    desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
        //    //desc.Filter = D3D11_FILTER_COMPARISON_ANISOTROPIC;

        //    desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
        //    desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
        //    desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;

        //    desc.MaxAnisotropy = (mDevice->GetFeatureLevel() > D3D_FEATURE_LEVEL_9_1) ? D3D11_MAX_MAXANISOTROPY : 2;

        //    desc.BorderColor[0] = 0.f;
        //    desc.BorderColor[1] = 0.f;
        //    desc.BorderColor[2] = 0.f;
        //    desc.BorderColor[3] = 0.f;
        //    //desc.MaxLOD = FLT_MAX;
        //    desc.ComparisonFunc = D3D11_COMPARISON_LESS;
        //}
        // CSM Shadow PCF
        //{
        //    desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT; // origin
        //    //desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
        //    desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
        //    desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
        //    desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
        //    desc.MipLODBias = 0.0f;
        //    desc.MaxAnisotropy = 0;
        //    desc.ComparisonFunc = D3D11_COMPARISON_LESS;
        //    desc.BorderColor[0] = 0.f;
        //    desc.BorderColor[1] = 0.f;
        //    desc.BorderColor[2] = 0.f;
        //    desc.BorderColor[3] = 1.f;
        //    desc.MinLOD = 0;
        //    desc.MaxLOD = 0;
        //}

        HRESULT hr = mDevice->CreateSamplerState(&desc, pResult);

        if (SUCCEEDED(hr))
            SetDebugObjectName(*pResult, "DirectXTK:CommonStatesEx");

        return hr;
    }
    ComPtr<ID3D11Device> mDevice;

    ComPtr<ID3D11BlendState> alphaToCoverage;
    //ComPtr<ID3D11BlendState> opaque;
    //ComPtr<ID3D11BlendState> alphaBlend;
    //ComPtr<ID3D11BlendState> additive;
    //ComPtr<ID3D11BlendState> nonPremultiplied;

    ComPtr<ID3D11DepthStencilState> depthNone;
    ComPtr<ID3D11DepthStencilState> depthDefault;
    ComPtr<ID3D11DepthStencilState> depthRead;

    ComPtr<ID3D11RasterizerState> SceneShadowRasterizerState;
    ComPtr<ID3D11RasterizerState> cullNone;
    ComPtr<ID3D11RasterizerState> cullClockwise;
    ComPtr<ID3D11RasterizerState> cullCounterClockwise;
    //ComPtr<ID3D11RasterizerState> wireframe;

    ComPtr<ID3D11SamplerState> SceneShadowSampler;
    //ComPtr<ID3D11SamplerState> pointWrap;
    //ComPtr<ID3D11SamplerState> pointClamp;
    //ComPtr<ID3D11SamplerState> linearWrap;
    //ComPtr<ID3D11SamplerState> linearClamp;
    //ComPtr<ID3D11SamplerState> anisotropicWrap;
    //ComPtr<ID3D11SamplerState> anisotropicClamp;

    std::mutex mutex;

    static inline SharedResourcePool<ID3D11Device*, Impl> instancePool;
};

CommonStatesEx::CommonStatesEx(ID3D11Device* device)
    : pImpl(Impl::instancePool.DemandCreate(device))
{
}

CommonStatesEx::CommonStatesEx(CommonStatesEx&& moveFrom) noexcept
    : pImpl(std::move(moveFrom.pImpl))
{
}

CommonStatesEx& CommonStatesEx::operator=(CommonStatesEx&& moveFrom) noexcept
{
    pImpl = std::move(moveFrom.pImpl);
    return *this;
}

CommonStatesEx::~CommonStatesEx()
{
}

ID3D11BlendState* __cdecl CommonStatesEx::AlphaToCoverage() const
{
    return DemandCreate(pImpl->alphaToCoverage, pImpl->mutex, [&](ID3D11BlendState** pResult)
    {
        return pImpl->CreateBlendState(D3D11_BLEND_ONE, D3D11_BLEND_ZERO, pResult, true);
    });
}

ID3D11DepthStencilState* __cdecl CommonStatesEx::ReverseZDepthNone() const
{
    return DemandCreate(pImpl->depthNone, pImpl->mutex, [&](ID3D11DepthStencilState** pResult)
        {
            return pImpl->CreateReverseDepthStencilState(false, false, pResult);
        });
}

ID3D11DepthStencilState* __cdecl CommonStatesEx::ReverseZDepthDefault() const
{
    return DemandCreate(pImpl->depthDefault, pImpl->mutex, [&](ID3D11DepthStencilState** pResult)
        {
            return pImpl->CreateReverseDepthStencilState(true, true, pResult);
        });
}

ID3D11DepthStencilState* __cdecl CommonStatesEx::ReverseZDepthRead() const
{
    return DemandCreate(pImpl->depthRead, pImpl->mutex, [&](ID3D11DepthStencilState** pResult)
        {
            return pImpl->CreateReverseDepthStencilState(true, false, pResult);
        });
}

ID3D11RasterizerState* CommonStatesEx::RSSceneShadow() const
{
    return DemandCreate(pImpl->SceneShadowRasterizerState, pImpl->mutex, [&](ID3D11RasterizerState** pResult)
        {
            return pImpl->CreateSceneShadowRasterizerState(pResult);
        });
}

ID3D11RasterizerState* CommonStatesEx::CullNone() const
{
    return DemandCreate(pImpl->cullNone, pImpl->mutex, [&](ID3D11RasterizerState** pResult)
        {
            return pImpl->CreateRasterizerState(D3D11_CULL_NONE, D3D11_FILL_SOLID, pResult);
        });
}


ID3D11RasterizerState* CommonStatesEx::CullClockwise() const
{
    return DemandCreate(pImpl->cullClockwise, pImpl->mutex, [&](ID3D11RasterizerState** pResult)
        {
            return pImpl->CreateRasterizerState(D3D11_CULL_FRONT, D3D11_FILL_SOLID, pResult);
        });
}


ID3D11RasterizerState* CommonStatesEx::CullCounterClockwise() const
{
    return DemandCreate(pImpl->cullCounterClockwise, pImpl->mutex, [&](ID3D11RasterizerState** pResult)
        {
            return pImpl->CreateRasterizerState(D3D11_CULL_BACK, D3D11_FILL_SOLID, pResult);
        });
}

ID3D11SamplerState* __cdecl CommonStatesEx::SSSceneShadow() const
{
    return DemandCreate(pImpl->SceneShadowSampler, pImpl->mutex, [&](ID3D11SamplerState** pResult)
        {
            return pImpl->CreateSceneShadowSamplerState(pResult);
        });
}
