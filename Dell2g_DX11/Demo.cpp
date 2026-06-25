#include "Framework.h"
#include "Demo.h"

void Demo::Initialize()
{
    CContext::Get()->GetCamera()->SetPosition(FVector(0,0,-4));
    CContext::Get()->SetCameraMoveSpeed(1.0f);
    CContext::Get()->SetCameraRotaionSpeed(0.f);
    
    Shader = new CShader(L"13_Blending.fx");
    
    // 버텍스 버퍼 설정
    Vertices = new FVertexTexture[VCount];

    Vertices[0].Position = FVector(-0.5f, -0.5f, 0.0f);
    Vertices[1].Position = FVector(-0.5f, +0.5f, 0.0f);
    Vertices[2].Position = FVector(+0.5f, -0.5f, 0.0f);
    Vertices[3].Position = FVector(+0.5f, +0.5f, 0.0f);

    Vertices[0].Uv = FVector2D(0.0f, 1.0f);
    Vertices[1].Uv = FVector2D(0.0f, 0.0f);
    Vertices[2].Uv = FVector2D(1.0f, 1.0f);
    Vertices[3].Uv = FVector2D(1.0f, 0.0f);
    
    VBuffer = new CVertexBuffer(Vertices,VCount, sizeof(FVertexTexture));
    
    
    // 인덱서 버퍼 설정
    Indices = new UINT[ICount]{0,1,2, 2,1,3};
    IBuffer = new CIndexBuffer(Indices, ICount);
    
}

void Demo::Destroy()
{
    Delete(Shader);
    
    DeleteArray(Vertices);
    Delete(VBuffer);
    
    DeleteArray(Indices);
    Delete(IBuffer);
}

void Demo::Tick()
{

    
#pragma region 마우스 위치, 델타 값
    ImGui::Text("Position : %s", CMouse::Get()->GetPosition().ToString().c_str());
    ImGui::Text("Delta : %s", CMouse::Get()->GetDelta().ToString().c_str());
#pragma endregion
    
    ImGui::ColorEdit3("Color0", Color0);
    ImGui::ColorEdit3("Color1", Color1);
    
}

void Demo::Render()
{
    FMatrix view = CContext::Get()->GetView();
    Shader->AsMatrix("View")->SetMatrix(view);
    
    FMatrix projection = CContext::Get()->GetProjection();
    Shader->AsMatrix("Projection")->SetMatrix(projection);
    
    Shader->AsVector("Color0")->SetFloatVector(Color0);
    Shader->AsVector("Color1")->SetFloatVector(Color1);

    VBuffer->Render();
    IBuffer->Render();
    
    CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Render_Lerp();
    Render_SmoothStep();
    Render_Step();
}

void Demo::Render_Lerp()
{
    FMatrix world = FMatrix::CreateTranslation(FVector(-0.5f, +1.f, 0.0f ));
    Shader->AsMatrix("World")->SetMatrix(world);
    
    Shader->SetPassNumber(0);
    Shader->DrawIndexed(ICount);
}

void Demo::Render_SmoothStep()
{
    FMatrix world = FMatrix::CreateTranslation(FVector(-0.5f, 0.0f, 0.0f));
    Shader->AsMatrix("World")->SetMatrix(world);

    Shader->SetPassNumber(1);
    Shader->DrawIndexed(ICount);
}

void Demo::Render_Step()
{
    FMatrix world = FMatrix::CreateTranslation(FVector(-0.5f, -1.0f, 0.0f));
    Shader->AsMatrix("World")->SetMatrix(world);

    Shader->SetPassNumber(2);
    Shader->DrawIndexed(ICount);
}
