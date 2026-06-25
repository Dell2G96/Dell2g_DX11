#include "Framework.h"
#include "Demo2.h"

void CDemo2::Initialize()
{
    Shader = new CShader(L"13_Blending.fx");

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

    Textures[0] = new CTexture2D(L"../_Textures/Box.png");
    Textures[1] = new CTexture2D(L"../_Textures/Floor.png");
    Textures[2] = new CTexture2D(L"../_Textures/Linear.png");
    Textures[3] = new CTexture2D(L"../_Textures/Checker.png");

    for (UINT i = 0; i < 4; i++)
    {
        SRVs[i] = *Textures[i];
    }

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
    
    for (UINT i = 0; i < 4; i++)
        Delete(Textures[i]);

}

void CDemo2::Tick()
{
    ImGui::InputFloat("TilingX", &Tiling.X, 1.0f);
    ImGui::InputFloat("TilingY", &Tiling.Y, 1.0f);
}

void CDemo2::Render()
{

    FMatrix view = CContext::Get()->GetView();
    Shader->AsMatrix("View")->SetMatrix(view);

    FMatrix projection = CContext::Get()->GetProjection();
    Shader->AsMatrix("Projection")->SetMatrix(projection);
    
    Shader->AsSRV("Maps")->SetResourceArray(SRVs, 0, 4);
	
    VBuffer->Render();
    IBuffer->Render();

    CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Render_Lerp();
    Render_Lerp2();
    Render_Tiling();
}

void CDemo2::Render_Lerp()
{
    FMatrix world = FMatrix::CreateTranslation(FVector(+0.5f, +1.0f, 0.0f));
    Shader->AsMatrix("World")->SetMatrix(world);
    
    Shader->SetTechniqueNumber(1);
    Shader->SetPassNumber(0);
    Shader->DrawIndexed(ICount);
    
}

void CDemo2::Render_Lerp2()
{
    FMatrix world = FMatrix::CreateTranslation(FVector(+0.5f, +0.0f, 0.0f));
    Shader->AsMatrix("World")->SetMatrix(world);
    
    Shader->SetTechniqueNumber(1);
    Shader->SetPassNumber(1);
    Shader->DrawIndexed(ICount);
}

void CDemo2::Render_Tiling()
{
    FMatrix world = FMatrix::CreateTranslation(FVector(+0.5f, -1.0f, 0.0f));
    Shader->AsMatrix("World")->SetMatrix(world);
    
    Shader->AsVector("Tiling")->SetFloatVector(Tiling);
    
    Shader->SetTechniqueNumber(1);
    Shader->SetPassNumber(2);
    Shader->DrawIndexed(ICount);
}
