#include "Framework.h"
#include "Demo.h"

void Demo::Initialize()
{
    Shader = new CShader(L"07_UserInterface.fx");
    
    Vertices[0] = FVector{ -1.0f, -1.0f, 0 };
    Vertices[1] = FVector{	0.0f, +1.0f, 0 };
    Vertices[2] = FVector{ +1.0f, -1.0f, 0 };
    
    VBuffer = new CVertexBuffer(Vertices, 3, sizeof(FVector));
}

void Demo::Destroy()
{
    Delete(VBuffer);
    Delete(Shader);
}

void Demo::Tick()
{
    static FColor color = FColor::White;
    // ImGui::Separator();
    // ImGui::SeparatorText("Demo");
    ImGui::ColorEdit3("Color", color);
    Shader->AsVector("Color")->SetFloatVector(color);
}

void Demo::Render()
{
    VBuffer->Render();

    CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Shader->SetPassNumber(4);
    Shader->Draw(3);
}