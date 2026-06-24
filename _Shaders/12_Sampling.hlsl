// =============================================================================
// 12_Sampling.hlsl
// 12_Sampling.fx (Effects11) -> 순수 HLSL 변환 버전
//
// Effects11(.fx)에서만 동작하던 문법(전역 변수 상수, 인라인 SamplerState,
// technique11/pass)을 제거하고, 런타임(C++)에서 직접 바인딩하는 방식으로 변환.
// 자세한 1:1 대응 설명은 12_Sampling_FX_to_HLSL.md 참고.
// =============================================================================

// -----------------------------------------------------------------------------
// 상수 버퍼 (Constant Buffer)
//  - .fx의 전역 변수(World/View/Projection, Address, Filter)는
//    HLSL에서 반드시 cbuffer 안에 명시적으로 배치해야 한다.
//  - register(bN)으로 슬롯을 직접 지정 -> C++에서 VSSetConstantBuffers /
//    PSSetConstantBuffers의 슬롯 번호와 1:1로 맞춘다.
//  - 16바이트 정렬 규칙 때문에 uint 하나라도 16바이트(float4) 단위를 차지한다.
// -----------------------------------------------------------------------------
cbuffer CB_World : register(b0)
{
    matrix World;
};

cbuffer CB_VP : register(b1)
{
    matrix View;
    matrix Projection;
};

cbuffer CB_Sampling : register(b2)
{
    uint Address; // 0:Wrap, 1:Mirror, 2:Border, 3:Clamp, else:기본
    uint Filter;  // 0:Point, 1:Linear, else:기본
    // float2 padding; // 필요 시 16바이트 정렬용 패딩 (C++ 구조체와 맞출 것)
};

// -----------------------------------------------------------------------------
// 리소스 바인딩
//  - .fx에서는 "Texture2D Map;" 한 줄이면 프레임워크가 슬롯을 자동 배정했지만,
//    순수 HLSL에서는 register(tN)/register(sN)으로 슬롯을 직접 지정한다.
//  - 인라인 SamplerState(AddressU = Wrap; Filter = ...;)는 Effects11 전용 문법.
//    순수 HLSL에서는 상태값을 셰이더에 쓸 수 없으므로, C++에서
//    ID3D11SamplerState를 만들어 각 슬롯(s0~s5)에 바인딩한다.
// -----------------------------------------------------------------------------
Texture2D Map : register(t0);

SamplerState Sampler        : register(s0); // 기본 샘플러
SamplerState Sampler_Wrap   : register(s1); // C++에서 AddressMode = WRAP
SamplerState Sampler_Mirror : register(s2); // C++에서 AddressMode = MIRROR
SamplerState Sampler_Clamp  : register(s3); // C++에서 AddressMode = CLAMP
SamplerState Sampler_Border : register(s4); // C++에서 AddressMode = BORDER, BorderColor=(0,0,1,1)
SamplerState Sampler_MirrorOnce : register(s5); // C++에서 AddressMode = SamplerMirrorOnce
SamplerState Sampler_Point  : register(s6); // C++에서 Filter = MIN_MAG_MIP_POINT
SamplerState Sampler_Linear : register(s7); // C++에서 Filter = MIN_MAG_MIP_LINEAR

// -----------------------------------------------------------------------------
// 입출력 구조체 (변경 없음 — 순수 HLSL과 .fx 문법이 동일)
// -----------------------------------------------------------------------------
struct VertexInput
{
    float4 Position : Position;
    float2 Uv : Uv;
};

struct VertexOutput
{
    float4 Position : SV_Position;
    float2 Uv : Uv;
};

// -----------------------------------------------------------------------------
// 정점 셰이더 (본문 로직 동일)
// -----------------------------------------------------------------------------
VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

    output.Uv = input.Uv;

    return output;
}

// -----------------------------------------------------------------------------
// 픽셀 셰이더 - Address Mode 비교 (pass P0 대응)
// -----------------------------------------------------------------------------
float4 PS_Address(VertexOutput input) : SV_Target
{
    if (Address == 0)
        return Map.Sample(Sampler_Wrap, input.Uv);

    if (Address == 1)
        return Map.Sample(Sampler_Mirror, input.Uv);

    if (Address == 2)
        return Map.Sample(Sampler_Border, input.Uv);

    if (Address == 3)
        return Map.Sample(Sampler_Clamp, input.Uv);
        
    if (Address == 4)
            return Map.Sample(Sampler_MirrorOnce, input.Uv);

    return Map.Sample(Sampler, input.Uv);
}

// -----------------------------------------------------------------------------
// 픽셀 셰이더 - Filter Mode 비교 (pass P1 대응)
// -----------------------------------------------------------------------------
float4 PS_Filter(VertexOutput input) : SV_Target
{
    if (Filter == 0)
        return Map.Sample(Sampler_Point, input.Uv);

    if (Filter == 1)
        return Map.Sample(Sampler_Linear, input.Uv);

    return Map.Sample(Sampler, input.Uv);
}

// -----------------------------------------------------------------------------
// technique11 / pass 제거
//  - 순수 HLSL에는 technique/pass 개념이 없다.
//  - 각 엔트리 포인트를 따로 컴파일한다:
//      VS         -> 타겟 "vs_5_0"
//      PS_Address -> 타겟 "ps_5_0"  (P0에 해당)
//      PS_Filter  -> 타겟 "ps_5_0"  (P1에 해당)
//  - 어떤 PS를 쓸지, 어떤 샘플러/상수버퍼를 바인딩할지는 모두 C++ 측에서 결정.
// -----------------------------------------------------------------------------
