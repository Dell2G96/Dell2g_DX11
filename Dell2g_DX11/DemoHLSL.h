#pragma once

#include "Systems/IExecutable.h"

// =============================================================================
// CDemoHLSL
//  - 기존 Demo(Effects11) 와 동일한 화면을, "순수 HLSL 파이프라인"으로 그려보는 예제.
//  - 12_Sampling.hlsl + CHLSLShader + CConstantBuffer + CSamplerState 를 사용한다.
//  - 자세한 흐름 설명: HLSL_Pipeline_Guide.md 참고.
// =============================================================================

// -----------------------------------------------------------------------------
// 상수 버퍼용 CPU 구조체 (HLSL의 cbuffer 와 1:1 대응)
//  - HLSL: cbuffer CB_World(b0) / CB_VP(b1) / CB_Sampling(b2)ㅇ
//  - 각 구조체 크기는 반드시 16바이트(float4)의 배수여야 한다.
// -----------------------------------------------------------------------------



class CDemoHLSL : public IExecutable
{
public:
    void Initialize() override;
    void Destroy() override;
    void Tick() override;
    void Render() override;

private:
    CHLSLShader* Shader = nullptr;

    UINT VCount = 4;
    FVertexTexture* Vertices = nullptr;
    CVertexBuffer* VBuffer = nullptr;

    UINT ICount = 6;
    UINT* Indices = nullptr;
    CIndexBuffer* IBuffer = nullptr;

    CTexture2D* Texture = nullptr;

private:
    // 상수 버퍼용 CPU 구조체 (HLSL의 cbuffer 와 1:1 대응)
    //  - 전역 이름 충돌(Demo3.h 등)을 피하기 위해 이 클래스 내부에만 정의한다.
    //  - 각 구조체 크기는 반드시 16바이트(float4)의 배수여야 한다.
    struct FViewProjectionData // -> register(b1), 128바이트
    {
        FMatrix View;
        FMatrix Projection;
    };
    struct FSamplingData       // -> register(b2), 16바이트 (uint 2개 + 패딩 2개)
    {
        UINT Address;
        UINT Filter;
        UINT Padding[2];
    };

private:
    FMatrix World;
    UINT Address = 0; // 0:Wrap, 1:Mirror, 2:Border, 3:Clamp
    // 상수 버퍼 2종 + 그에 대응하는 CPU 데이터
    // (World 행렬은 아래 World 멤버를 그대로 상수 버퍼 데이터로 사용)
    FViewProjectionData VPData;
    FSamplingData SamplingData;

    CConstantBuffer* WorldBuffer = nullptr;
    CConstantBuffer* VPBuffer = nullptr;
    CConstantBuffer* SamplingBuffer = nullptr;

private:
    // 12_Sampling.hlsl 의 s0~s5 슬롯에 대응하는 샘플러들
    CSamplerState* Sampler = nullptr;        // s0 기본
    CSamplerState* SamplerWrap = nullptr;    // s1
    CSamplerState* SamplerMirror = nullptr;  // s2
    CSamplerState* SamplerClamp = nullptr;   // s3
    CSamplerState* SamplerBorder = nullptr;  // s4
    CSamplerState* SamplerMirrorOnce = nullptr;  // s5

};
