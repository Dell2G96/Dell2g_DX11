#include "Framework.h"
#include "Demo-HLSL.h"

void Demo_hlsl::Initialize()
{
    CContext::Get()->GetCamera()->SetPosition(FVector(0, 0, -4));
    CContext::Get()->SetCameraMoveSpeed(1.0f);
    CContext::Get()->SetCameraRotaionSpeed(0.f);

    Shaders[0] = new CHLSLShader(L"13_Blending.hlsl", "VS", "PS_Lerp");
    Shaders[1] = new CHLSLShader(L"13_Blending.hlsl", "VS", "PS_SmoothStep");
    Shaders[2] = new CHLSLShader(L"13_Blending.hlsl", "VS", "PS_Step");

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

    WorldBuffer = new CConstantBuffer(&World, sizeof(FMatrix));
    VPBuffer = new CConstantBuffer(&VPData, sizeof(FViewProjectionData));
    ColorBuffer = new CConstantBuffer(&ColorData, sizeof(FBlendColorData));

    World = FMatrix::Identity;
    ColorData.Color0 = FColor::Red;
    ColorData.Color1 = FColor::Blue;
}

void Demo_hlsl::Destroy()
{
    for (UINT i = 0; i < 3; i++)
        Delete(Shaders[i]);

    DeleteArray(Vertices);
    Delete(VBuffer);

    DeleteArray(Indices);
    Delete(IBuffer);

    Delete(WorldBuffer);
    Delete(VPBuffer);
    Delete(ColorBuffer);
}

void Demo_hlsl::Tick()
{
    ImGui::Text("Position : %s", CMouse::Get()->GetPosition().ToString().c_str());
    ImGui::Text("Delta : %s", CMouse::Get()->GetDelta().ToString().c_str());

    ImGui::ColorEdit3("HLSL Color0", ColorData.Color0);
    ImGui::ColorEdit3("HLSL Color1", ColorData.Color1);
}

void Demo_hlsl::Render()
{
    ID3D11DeviceContext* deviceContext = CD3D::Get()->GetDeviceContext();

    VPData.View = CContext::Get()->GetView();
    VPData.Projection = CContext::Get()->GetProjection();
    VPBuffer->Update();

    ColorBuffer->Update();

    VPBuffer->BindToVS(1);
    ColorBuffer->BindToPS(2);

    VBuffer->Render();
    IBuffer->Render();
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Render_Lerp();
    Render_SmoothStep();
    Render_Step();
}

void Demo_hlsl::Render_Lerp()
{
    World = FMatrix::CreateTranslation(FVector(-0.5f, +1.0f, 0.0f));
    WorldBuffer->Update();
    WorldBuffer->BindToVS(0);

    Shaders[0]->Render();
    CD3D::Get()->GetDeviceContext()->DrawIndexed(ICount, 0, 0);
}

void Demo_hlsl::Render_SmoothStep()
{
    World = FMatrix::CreateTranslation(FVector(-0.5f, 0.0f, 0.0f));
    WorldBuffer->Update();
    WorldBuffer->BindToVS(0);

    Shaders[1]->Render();
    CD3D::Get()->GetDeviceContext()->DrawIndexed(ICount, 0, 0);
}

void Demo_hlsl::Render_Step()
{
    World = FMatrix::CreateTranslation(FVector(-0.5f, -1.0f, 0.0f));
    WorldBuffer->Update();
    WorldBuffer->BindToVS(0);

    Shaders[2]->Render();
    CD3D::Get()->GetDeviceContext()->DrawIndexed(ICount, 0, 0);
}
