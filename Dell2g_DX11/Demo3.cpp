#include "Framework.h"
#include "Demo3.h"

void CDemo3::Initialize()
{
    Shader = new CShader(L"06_Pass.fx");

    Vertices[0] = FVector{ -1.0f, +0.5f, 0 };
    Vertices[1] = FVector{ +1.0f, +0.5f, 0 };

    VBuffer = new CVertexBuffer(Vertices, 2, sizeof(FVector));
}

void CDemo3::Destroy()
{
    Delete(VBuffer);
    Delete(Shader);
}

void CDemo3::Tick()
{
}

void CDemo3::Render()
{
    VBuffer->Render();

    CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

    Shader->SetPassNumber(2);
    Shader->Draw(2);

}
