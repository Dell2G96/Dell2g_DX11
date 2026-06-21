#include "Framework.h"
#include "Demo2.h"

void CDemo2::Initialize()
{
    Shader = new CShader(L"08_Rectangle.fx");

    Vertices[0] = FVector(-0.5f, +0.0f, 0);
    Vertices[1] = FVector(-0.5f, +0.5f, 0);
    Vertices[2] = FVector(+0.0f, +0.0f, 0);
    Vertices[3] = FVector(+0.0f, +0.5f, 0);

    VBuffer = new CVertexBuffer(Vertices, 4, sizeof(FVector));

}

void CDemo2::Destroy()
{
    Delete(VBuffer);
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
    ImGui::InputInt("Technique - Demo2", (int*)&Technique);
    Technique = FMath::Clamp<UINT>(Technique, 0, 1);
    
    
    
}

void CDemo2::Render()
{
    VBuffer->Render();

    CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    Shader->SetTechniqueNumber(Technique);
    Shader->SetPassNumber(Pass);
    Shader->Draw(4);
}