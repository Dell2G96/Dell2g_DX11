#include "Framework.h"
#include "Demo2-HLSL.h"

void Demo2_hlsl::Initialize()
{
    CContext::Get()->GetCamera()->SetPosition(FVector(0, 0, -6));
    CContext::Get()->SetCameraMoveSpeed(1.0f);
    CContext::Get()->SetCameraRotaionSpeed(0.f);

    Shaders[0] = new CHLSLShader(L"13_Blending.hlsl", "VS", "PS_Lerp_UV");
    Shaders[1] = new CHLSLShader(L"13_Blending.hlsl", "VS", "PS_Lerp_UV2");
    Shaders[2] = new CHLSLShader(L"13_Blending.hlsl", "VS", "PS_Lerp_Tiling");

    Vertices = new FVertexTexture[VCount];

    Vertices[0].Position = FVector(-0.5f, -0.5f, 0.0f);
    Vertices[1].Position = FVector(-0.5f, +0.5f, 0.0f);
    Vertices[2].Position = FVector(+0.5f, -0.5f, 0.0f);
    Vertices[3].Position = FVector(+0.5f, +0.5f, 0.0f);

    Vertices[0].Uv = FVector2D(0.0f, 1.0f);
    Vertices[1].Uv = FVector2D(0.0f, 0.0f);
    Vertices[2].Uv = FVector2D(1.0f, 1.0f);
    Vertices[3].Uv = FVector2D(1.0f, 0.0f);

    VBuffer = new CVertexBuffer(Vertices, VCount, sizeof(FVertexTexture));

    Indices = new UINT[ICount]{ 0, 1, 2, 2, 1, 3 };
    IBuffer = new CIndexBuffer(Indices, ICount);

    Textures[0] = new CTexture2D(L"../_Textures/Box.png");
    Textures[1] = new CTexture2D(L"../_Textures/Floor.png");
    Textures[2] = new CTexture2D(L"../_Textures/Linear.png");
    Textures[3] = new CTexture2D(L"../_Textures/Checker.png");

    for (UINT i = 0; i < 4; i++)
        SRVs[i] = *Textures[i];

    WorldBuffer = new CConstantBuffer(&World, sizeof(FMatrix));
    VPBuffer = new CConstantBuffer(&VPData, sizeof(FViewProjectionData));
    TilingBuffer = new CConstantBuffer(&TilingData, sizeof(FTilingData));

    LinearSampler = new CSamplerState();
    LinearSampler->SetFilter(D3D11_FILTER_MIN_MAG_MIP_LINEAR);
    LinearSampler->SetAddress(D3D11_TEXTURE_ADDRESS_WRAP);
    LinearSampler->Create();

    World = FMatrix::Identity;
    TilingData.Tiling = Tiling;
    TilingData.Padding = FVector2D(0.0f, 0.0f);
}

void Demo2_hlsl::Destroy()
{
    for (UINT i = 0; i < 3; i++)
        Delete(Shaders[i]);

    DeleteArray(Vertices);
    Delete(VBuffer);

    DeleteArray(Indices);
    Delete(IBuffer);

    for (UINT i = 0; i < 4; i++)
        Delete(Textures[i]);

    Delete(WorldBuffer);
    Delete(VPBuffer);
    Delete(TilingBuffer);

    Delete(LinearSampler);
}

void Demo2_hlsl::Tick()
{
    ImGui::InputFloat("HLSL TilingX", &Tiling.X, 1.0f);
    ImGui::InputFloat("HLSL TilingY", &Tiling.Y, 1.0f);

    // 각 도형 위에 기법 이름 표시 (월드 좌표를 넘기면 내부에서 화면 좌표로 변환)
    CGui::Get()->RenderText(FVector(+0.5f, +1.5f + 0.6f, 0.0f), 1, 1, 1, "Lerp_UV");
    CGui::Get()->RenderText(FVector(+0.5f, 0.0f + 0.6f, 0.0f), 1, 1, 1, "Lerp_UV2");
    CGui::Get()->RenderText(FVector(+0.5f, -1.5f + 0.6f, 0.0f), 1, 1, 1, "Lerp_Tiling");
}

void Demo2_hlsl::Render()
{
    ID3D11DeviceContext* deviceContext = CD3D::Get()->GetDeviceContext();

    VPData.View = CContext::Get()->GetView();
    VPData.Projection = CContext::Get()->GetProjection();
    VPBuffer->Update();

    TilingData.Tiling = Tiling;
    TilingBuffer->Update();

    VPBuffer->BindToVS(1);
    TilingBuffer->BindToPS(3);

    deviceContext->PSSetShaderResources(0, 4, SRVs);
    LinearSampler->BindToPS(0);

    VBuffer->Render();
    IBuffer->Render();
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Render_Lerp();
    Render_Lerp2();
    Render_Tiling();
}

void Demo2_hlsl::Render_Lerp()
{
    World = FMatrix::CreateTranslation(FVector(+1.f, +1.5f, 0.0f));
    WorldBuffer->Update();
    WorldBuffer->BindToVS(0);

    Shaders[0]->Render();
    CD3D::Get()->GetDeviceContext()->DrawIndexed(ICount, 0, 0);
}

void Demo2_hlsl::Render_Lerp2()
{
    World = FMatrix::CreateTranslation(FVector(+1.f, 0.0f, 0.0f));
    WorldBuffer->Update();
    WorldBuffer->BindToVS(0);

    Shaders[1]->Render();
    CD3D::Get()->GetDeviceContext()->DrawIndexed(ICount, 0, 0);
}

void Demo2_hlsl::Render_Tiling()
{
    World = FMatrix::CreateTranslation(FVector(+1.f, -1.5f, 0.0f));
    WorldBuffer->Update();
    WorldBuffer->BindToVS(0);

    Shaders[2]->Render();
    CD3D::Get()->GetDeviceContext()->DrawIndexed(ICount, 0, 0);
}
