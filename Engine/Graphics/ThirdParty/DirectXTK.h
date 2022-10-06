#pragma once
#include <ixrEngine/01.Core/CoreMinimal.h>
#include <DirectXTK/BufferHelpers.h>
#include <DirectXTK/CommonStates.h>
#include <DirectXTK/DDSTextureLoader.h>
#include <DirectXTK/Effects.h>
#include <DirectXTK/GeometricPrimitive.h>
#include <DirectXTK/GraphicsMemory.h>
#include <DirectXTK/Model.h>
#include <DirectXTK/PostProcess.h>
#include <DirectXTK/PrimitiveBatch.h>
#include <DirectXTK/ScreenGrab.h>
#include <DirectXTK/SpriteBatch.h>
#include <DirectXTK/SpriteFont.h>
#include <DirectXTK/VertexTypes.h>
#include <DirectXTK/WICTextureLoader.h>
#include <DirectXTK/DirectXHelpers.h>

// Core모듈에서 대체
//#include "DirectXTK/Inc/GamePad.h"
//#include "DirectXTK/Inc/Keyboard.h"
//#include "DirectXTK/Inc/Mouse.h"
//#include "DirectXTK/Inc/SimpleMath.h"

class CommonStatesEx
{
public:
    explicit CommonStatesEx(_In_ ID3D11Device* device);
    CommonStatesEx(CommonStatesEx&& moveFrom) noexcept;
    CommonStatesEx& operator= (CommonStatesEx&& moveFrom) noexcept;

    CommonStatesEx(CommonStatesEx const&) = delete;
    CommonStatesEx& operator= (CommonStatesEx const&) = delete;

    virtual ~CommonStatesEx();

    // Blend states.
    ID3D11BlendState* __cdecl AlphaToCoverage() const;
    //ID3D11BlendState* __cdecl AlphaBlend() const;
    //ID3D11BlendState* __cdecl Additive() const;
    //ID3D11BlendState* __cdecl NonPremultiplied() const;

    //// Depth stencil states.
    ID3D11DepthStencilState* __cdecl ReverseZDepthNone() const;
    ID3D11DepthStencilState* __cdecl ReverseZDepthDefault() const;
    ID3D11DepthStencilState* __cdecl ReverseZDepthRead() const;

    //// Rasterizer states.
    ID3D11RasterizerState* __cdecl RSSceneShadow() const;
    ID3D11RasterizerState* __cdecl CullNone() const;
    ID3D11RasterizerState* __cdecl CullClockwise() const;
    ID3D11RasterizerState* __cdecl CullCounterClockwise() const;
    //ID3D11RasterizerState* __cdecl Wireframe() const;

    //// Sampler states.
    ID3D11SamplerState* __cdecl SSSceneShadow() const;
    //ID3D11SamplerState* __cdecl PointWrap() const;
    //ID3D11SamplerState* __cdecl PointClamp() const;
    //ID3D11SamplerState* __cdecl LinearWrap() const;
    //ID3D11SamplerState* __cdecl LinearClamp() const;
    //ID3D11SamplerState* __cdecl AnisotropicWrap() const;
    //ID3D11SamplerState* __cdecl AnisotropicClamp() const;

private:
    // Private implementation.
    class Impl;

    std::shared_ptr<Impl> pImpl;
};

FORCEINLINE Matrix ReversedZOrthoMatrix(float Width, float Height, float ZScale, float ZOffset)
{ 
    Matrix ProjMatrix = Matrix(
        (Width != 0.0f) ? (1.0f / Width) : 1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, (Height != 0.0f) ? (1.0f / Height) : 1.f, 0.0f, 0.0f,
        0.0f, 0.0f, -ZScale, 0.0f,
        0.0f, 0.0f, 1.0f - ZOffset * ZScale, 1.0f
    );

    return std::move(ProjMatrix);
}

FORCEINLINE Matrix ReversedZOrthoMatrix(float Left, float Right, float Bottom, float Top, float ZScale, float ZOffset)
{
    Matrix ProjMatrix = Matrix(
        1.0f / (Right - Left), 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f / (Top - Bottom), 0.0f, 0.0f,
        0.0f, 0.0f, -ZScale, 0.0f,
        (Left + Right) / (Left - Right), (Top + Bottom) / (Bottom - Top), 1.0f - ZOffset * ZScale, 1.0f
        );

    return std::move(ProjMatrix);
}