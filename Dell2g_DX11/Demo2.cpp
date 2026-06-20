#include "Framework.h"
#include "Demo2.h"

void CDemo2::Initialize()
{
    Shader = new CShader(L"07_UserInterface.fx");

    Vertices[0] = FVector{ -0.5f, 0.f, 0 };
    Vertices[1] = FVector{ -1.0f, 1.f, 0 };
    Vertices[2] = FVector{ +0.f, 1.f, 0 };

    VBuffer = new CVertexBuffer(Vertices, 3, sizeof(FVector));

}

void CDemo2::Destroy()
{
    Delete(VBuffer);
    Delete(Shader);
}

void CDemo2::Tick()
{
    ImGui::Separator();
    ImGui::SeparatorText("Demo2");
    ImGui::InputInt("Pass", (int*)&Pass);
    Pass = FMath::Clamp<UINT>(Pass, 0 , 5);
    
    
}

void CDemo2::Render()
{
    VBuffer->Render();

    CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Shader->SetPassNumber(Pass);
    Shader->Draw(3);
}