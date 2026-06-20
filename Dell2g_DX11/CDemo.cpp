#include "Framework.h"
#include "CDemo.h"

void CDemo::Initialize()
{
    Shader = new CShader(L"06_Pass.fx");
    
    Vertices[0] = FVector{-1.f, -0.5f, 0};
    Vertices[1] = FVector{+1.f, -0.5f, 0};
    
    VBuffer = new CVertexBuffer(Vertices, 2, sizeof(FVector));
}

void CDemo::Destroy()
{
    Delete(VBuffer);
    Delete(Shader);
}

void CDemo::Tick()
{
    
}

void CDemo::Render()
{
    VBuffer->Render();

    CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

    Shader->SetPassNumber(0);
    Shader->Draw(2);
}