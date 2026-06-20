#include "Framework.h"
#include "Demo2.h"

void CDemo2::Initialize()
{
    Shader = new CShader(L"06_Pass.fx");

    Vertices[0] = FVector{ -1.0f, 0.f, 0 };
    Vertices[1] = FVector{ +1.0f, 0.f, 0 };

    VBuffer = new CVertexBuffer(Vertices, 2, sizeof(FVector));

}

void CDemo2::Destroy()
{
    Delete(VBuffer);
    Delete(Shader);
}

void CDemo2::Tick()
{
}

void CDemo2::Render()
{
    VBuffer->Render();

    CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

    Shader->SetPassNumber(1);
    Shader->Draw(2);
}