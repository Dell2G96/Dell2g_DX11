#include "Framework.h"
#include "SamplerState.h"

CSamplerState::CSamplerState()
{
    // 안전한 기본값으로 Desc를 채워둔다.
    // (C++에서는 .fx와 달리 모든 필드를 명시적으로 채우는 것이 안전하다)
    ZeroMemory(&Desc, sizeof(D3D11_SAMPLER_DESC));
    Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;       // 기본: 선형 보간
    Desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;          // 기본: Wrap
    Desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    Desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    Desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    Desc.MinLOD = 0.0f;
    Desc.MaxLOD = D3D11_FLOAT32_MAX;
    Desc.MaxAnisotropy = 1;
}

CSamplerState::~CSamplerState()
{
    Release(State);
}

void CSamplerState::SetFilter(D3D11_FILTER InFilter)
{
    Desc.Filter = InFilter;
}

void CSamplerState::SetAddress(D3D11_TEXTURE_ADDRESS_MODE InAddress)
{
    Desc.AddressU = InAddress;
    Desc.AddressV = InAddress;
    Desc.AddressW = InAddress;
}

void CSamplerState::SetBorderColor(float InR, float InG, float InB, float InA)
{
    Desc.BorderColor[0] = InR;
    Desc.BorderColor[1] = InG;
    Desc.BorderColor[2] = InB;
    Desc.BorderColor[3] = InA;
}

void CSamplerState::Create()
{
    // 이미 만들어 둔 상태가 있으면 해제 후 재생성 (설정을 바꿔 다시 Create 가능)
    Release(State);

    HRESULT hr = CD3D::Get()->GetDevice()->CreateSamplerState(&Desc, &State);
    Check(hr);
}

void CSamplerState::BindToPS(UINT InSlot)
{
    assert(State != nullptr && "Create() must be called before BindToPS()");
    CD3D::Get()->GetDeviceContext()->PSSetSamplers(InSlot, 1, &State);
}
