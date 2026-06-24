#include "Framework.h"
#include "DemoHLSL.h"

void CDemoHLSL::Initialize()
{
    CContext::Get()->GetCamera()->SetPosition(FVector(0, 0, -2));
    CContext::Get()->SetCameraMoveSpeed(1.0f);
    CContext::Get()->SetCameraRotaionSpeed(0.f);

    // [1] 순수 HLSL 셰이더: VS + PS_Address 를 컴파일해 사용 (= 기존의 pass P0)
    Shader = new CHLSLShader(L"12_Sampling.hlsl", "VS", "PS_Address");

    // [2] 정점 / 인덱스 버퍼 (Demo와 동일)
    Vertices = new FVertexTexture[VCount];

    Vertices[0].Position = FVector(-0.5f, -0.5f, 0.0f);
    Vertices[1].Position = FVector(-0.5f, +0.5f, 0.0f);
    Vertices[2].Position = FVector(+0.5f, -0.5f, 0.0f);
    Vertices[3].Position = FVector(+0.5f, +0.5f, 0.0f);

    Vertices[0].Uv = FVector2D(-2.0f, 2.0f);
    Vertices[1].Uv = FVector2D(-2.0f, 0.0f);
    Vertices[2].Uv = FVector2D(2.0f, 2.0f);
    Vertices[3].Uv = FVector2D(2.0f, 0.0f);

    VBuffer = new CVertexBuffer(Vertices, VCount, sizeof(FVertexTexture));

    Indices = new UINT[ICount]{ 0,1,2, 2,1,3 };
    IBuffer = new CIndexBuffer(Indices, ICount);

    // [3] 텍스처: Effects11과 달리 셰이더에 묶지 않고 SRV만 만든다.
    //     (셰이더 인자가 없는 생성자를 사용 -> 바인딩은 Render에서 직접)
    Texture = new CTexture2D(L"../_Textures/김채원.png");

    // [4] 상수 버퍼 3종 생성 (CPU 구조체 주소 + 크기를 넘김)
    WorldBuffer    = new CConstantBuffer(&World,        sizeof(FMatrix));
    VPBuffer       = new CConstantBuffer(&VPData,       sizeof(FViewProjectionData));
    SamplingBuffer = new CConstantBuffer(&SamplingData, sizeof(FSamplingData));

    // [5] 샘플러 상태 생성 (.fx의 인라인 SamplerState를 C++로 옮긴 것)
    Sampler = new CSamplerState();                                   // s0 기본(Linear/Wrap)
    Sampler->Create();

    SamplerWrap = new CSamplerState();                               // s1 Wrap
    SamplerWrap->SetAddress(D3D11_TEXTURE_ADDRESS_WRAP);
    SamplerWrap->Create();

    SamplerMirror = new CSamplerState();                             // s2 Mirror
    SamplerMirror->SetAddress(D3D11_TEXTURE_ADDRESS_MIRROR);
    SamplerMirror->Create();

    SamplerClamp = new CSamplerState();                              // s3 Clamp
    SamplerClamp->SetAddress(D3D11_TEXTURE_ADDRESS_CLAMP);
    SamplerClamp->Create();

    SamplerBorder = new CSamplerState();                             // s4 Border (파란 테두리)
    SamplerBorder->SetAddress(D3D11_TEXTURE_ADDRESS_BORDER);
    SamplerBorder->SetBorderColor(0, 0, 1, 1);
    SamplerBorder->Create();
    
    SamplerMirrorOnce = new CSamplerState();                             // s5 Mirror_Once
    SamplerMirrorOnce->SetAddress(D3D11_TEXTURE_ADDRESS_MIRROR_ONCE);
    SamplerMirrorOnce->Create();

    World = FMatrix::Identity;
}

void CDemoHLSL::Destroy()
{
    Delete(Shader);

    DeleteArray(Vertices);
    Delete(VBuffer);

    DeleteArray(Indices);
    Delete(IBuffer);

    Delete(Texture);

    Delete(WorldBuffer);
    Delete(VPBuffer);
    Delete(SamplingBuffer);

    Delete(Sampler);
    Delete(SamplerWrap);
    Delete(SamplerMirror);
    Delete(SamplerClamp);
    Delete(SamplerBorder);
    Delete(SamplerMirrorOnce);
}

void CDemoHLSL::Tick()
{
    if (CKeyboard::Get()->Press(VK_RIGHT))
        World.M41 += 1.0f * CTimer::Get()->GetDeltaTime();
    else if (CKeyboard::Get()->Press(VK_LEFT))
        World.M41 -= 1.0f * CTimer::Get()->GetDeltaTime();

    if (CKeyboard::Get()->Press(VK_UP))
        World.M43 += 1.0f * CTimer::Get()->GetDeltaTime();
    else if (CKeyboard::Get()->Press(VK_DOWN))
        World.M43 -= 1.0f * CTimer::Get()->GetDeltaTime();

    ImGui::Text("[HLSL] Position : %s", CMouse::Get()->GetPosition().ToString().c_str());
    ImGui::InputInt("HLSL Address", (int*)&Address);
    Address = FMath::Clamp<UINT>(Address, 0, 6);
}

void CDemoHLSL::Render()
{
    ID3D11DeviceContext* deviceContext = CD3D::Get()->GetDeviceContext();

    // [1] 상수 버퍼 값 갱신 (CPU 구조체 -> GPU)
    WorldBuffer->Update();   // World 멤버를 직접 가리키므로 별도 복사 불필요

    VPData.View = CContext::Get()->GetView();
    VPData.Projection = CContext::Get()->GetProjection();
    VPBuffer->Update();

    SamplingData.Address = Address;
    SamplingBuffer->Update();

    // [2] 상수 버퍼 바인딩 (HLSL의 register 번호와 일치)
    WorldBuffer->BindToVS(0);     // CB_World    : b0 (VS에서 사용)
    VPBuffer->BindToVS(1);        // CB_VP       : b1 (VS에서 사용)
    SamplingBuffer->BindToPS(2);  // CB_Sampling : b2 (PS에서 사용)

    // [3] 텍스처(SRV) 바인딩 -> t0
    ID3D11ShaderResourceView* srv = *Texture;
    deviceContext->PSSetShaderResources(0, 1, &srv);

    // [4] 샘플러 바인딩 -> s0~s5
    Sampler->BindToPS(0);
    SamplerWrap->BindToPS(1);
    SamplerMirror->BindToPS(2);
    SamplerClamp->BindToPS(3);
    SamplerBorder->BindToPS(4);
    SamplerMirrorOnce->BindToPS(5);

    // [5] 정점/인덱스 버퍼 + 토폴로지
    VBuffer->Render();
    IBuffer->Render();
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // [6] 입력 레이아웃 + VS + PS 바인딩 후 드로우
    Shader->Render();
    deviceContext->DrawIndexed(ICount, 0, 0);
}
