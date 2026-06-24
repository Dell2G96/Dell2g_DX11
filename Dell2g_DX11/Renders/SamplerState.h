#pragma once

// =============================================================================
// CSamplerState
//  - Effects11에서는 .fx 파일 안에 SamplerState{ AddressU=Wrap; Filter=...; }를
//    직접 적을 수 있었지만, 순수 HLSL에서는 불가능하다.
//  - 그 "샘플러 상태"를 C++에서 D3D11_SAMPLER_DESC로 만들어 주는 래퍼 클래스.
//  - 사용 흐름: (setter로 상태 설정) -> Create() -> BindToPS(slot)
//  - 자세한 설명: HLSL_Pipeline_Guide.md 참고.
// =============================================================================
class CSamplerState
{
public:
    CSamplerState();
    ~CSamplerState();

public:
    // 필터(확대/축소/밉맵 보간 방식) 설정. 예: D3D11_FILTER_MIN_MAG_MIP_POINT
    void SetFilter(D3D11_FILTER InFilter);

    // 주소 모드(UV가 0~1 밖으로 나갔을 때 처리) 설정. U/V/W 한 번에 지정.
    // 예: D3D11_TEXTURE_ADDRESS_WRAP / MIRROR / CLAMP / BORDER
    void SetAddress(D3D11_TEXTURE_ADDRESS_MODE InAddress);

    // BORDER 모드일 때 테두리 바깥을 채울 색. (.fx의 BorderColor에 대응)
    void SetBorderColor(float InR, float InG, float InB, float InA);

public:
    // 지금까지 설정한 Desc로 실제 ID3D11SamplerState 객체를 생성한다.
    void Create();

    // 생성된 샘플러를 픽셀 셰이더의 sN 슬롯에 바인딩한다.
    void BindToPS(UINT InSlot);

private:
    D3D11_SAMPLER_DESC Desc;
    ID3D11SamplerState* State = nullptr;
};
