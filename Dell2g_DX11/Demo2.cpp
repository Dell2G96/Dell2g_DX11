#include "Framework.h"
#include "Demo2.h"

void CDemo2::Initialize()
{
    Shader = new CShader(L"12_Sampling.fx");

    Vertices = new FVertexTexture[VCount];

    Vertices[0].Position = FVector(-0.5f, -0.5f, 0.0f);
    Vertices[1].Position = FVector(-0.5f, +0.5f, 0.0f);
    Vertices[2].Position = FVector(+0.5f, -0.5f, 0.0f);
    Vertices[3].Position = FVector(+0.5f, +0.5f, 0.0f);

    Vertices[0].Uv = FVector2D(0.0f, 5.0f);
    Vertices[1].Uv = FVector2D(0.0f, 0.0f);
    Vertices[2].Uv = FVector2D(5.0f, 5.0f);
    Vertices[3].Uv = FVector2D(5.0f, 0.0f);

    Texture = new CTexture2D(Shader, "Map", L"../_Textures/Grass.png");
    
    VBuffer = new CVertexBuffer(Vertices, VCount, sizeof(FVertexTexture));

    Indices = new UINT[ICount]{ 0, 1, 2, 2, 1, 3 };

    IBuffer = new CIndexBuffer(Indices, ICount);


    World = FMatrix::CreateTranslation(FVector(1.0f, 0, 0));

    //ID3D11SamplerState
    //D3D11_SAMPLER_DESC
    //CD3D::Get()->GetDevice()->CreateSamplerState()
}

void CDemo2::Destroy()
{
    Delete(Shader);

    DeleteArray(Vertices);
    Delete(VBuffer);

    DeleteArray(Indices);
    Delete(IBuffer);
    
    Delete(Texture);
}

void CDemo2::Tick()
{
    ImGui::InputInt("Filter", (int*)&Filter);
    Filter = FMath::Clamp<UINT>(Filter, 0, 1);
}

void CDemo2::Render()
{
    Shader->AsMatrix("World")->SetMatrix(World);

    FMatrix view = CContext::Get()->GetView();
    Shader->AsMatrix("View")->SetMatrix(view);

    FMatrix projection = CContext::Get()->GetProjection();
    Shader->AsMatrix("Projection")->SetMatrix(projection);
    
    Shader->AsScalar("Filter")->SetInt(Filter);

	
    VBuffer->Render();
    IBuffer->Render();
    Texture->Render();


    CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Shader->SetPassNumber(1);
    Shader->DrawIndexed(ICount);
}
