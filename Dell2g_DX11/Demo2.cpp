#include "Framework.h"
#include "Demo2.h"

void CDemo2::Initialize()
{
    Shader = new CShader(L"09_WorldMatrix.fx");

    // 버텍스 버퍼
    Vertices[0] = FVector(-0.5f, -0.5f, 0);
    Vertices[1] = FVector(-0.5f, +0.5f, 0);
    Vertices[2] = FVector(+0.5f, -0.5f, 0);
    Vertices[3] = FVector(+0.5f, +0.5f, 0);


    VBuffer = new CVertexBuffer(Vertices, 4, sizeof(FVector));

    // 인덱스 버퍼 
    Indices[0] = 0;
    Indices[1] = 1;
    Indices[2] = 2;

    Indices[3] = 2;
    Indices[4] = 1;
    Indices[5] = 3;
 
    IBuffer = new CIndexBuffer(Indices, 6);
    
    World = FMatrix::Identity;
    
    FVector eye = FVector(0,0,-10);
    View = FMatrix::CreateLookAt(eye, eye + FVector::Forward, FVector::Up );
    
    float width = CD3D::Get()->GetWidth();
    float height = CD3D::Get()->GetHeight();
    float aspect = width / height;

    float fov = FMath::Pi * 0.25f;
    Projection = FMatrix::CreatePerspectiveFieldOfView(fov, aspect, 0.1f, 1000.0f);
}

void CDemo2::Destroy()
{
    Delete(VBuffer);
    Delete(IBuffer);
    
    Delete(Shader);
}

void CDemo2::Tick()
{
#pragma region Pass
    // ImGui::Separator();
    // ImGui::SeparatorText("Demo2");
    // ImGui::InputInt("Pass", (int*)&Pass);
    // Pass = FMath::Clamp<UINT>(Pass, 0 , 5);
#pragma endregion

    if (CKeyboard::Get()->Press('L'))
        World.M41 += 1.f * CTimer::Get()->GetDeltaTime();
    else if (CKeyboard::Get()->Press('J'))
        World.M41 -= 1.f * CTimer::Get()->GetDeltaTime();
    
    if (CKeyboard::Get()->Press('I'))
        World.M42 += 1.f * CTimer::Get()->GetDeltaTime();
    else if (CKeyboard::Get()->Press('K'))
        World.M42 -= 1.f * CTimer::Get()->GetDeltaTime();
    
}

void CDemo2::Render()
{
    Shader->AsMatrix("World")->SetMatrix(World);
    Shader->AsMatrix("View")->SetMatrix(View);
    Shader->AsMatrix("Projection")->SetMatrix(Projection);
    Shader->AsVector("Color")->SetFloatVector(Color);
    
    VBuffer->Render();
    IBuffer->Render();

    CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Shader->SetPassNumber(0);
    Shader->DrawIndexed(6);
}
