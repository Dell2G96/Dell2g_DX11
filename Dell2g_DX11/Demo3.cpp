#include "Framework.h"
#include "Demo3.h"

void CDemo3::Initialize()
{
    
  CContext::Get()->GetCamera()->SetPosition(FVector(0, 0, -2));

    
    Shader = new CHLSLShader(L"12_Sampling.hlsl", "VS", "PS_Filter");
    
    // 정점 / 인덱스 버퍼
    Vertices = new FVertexTexture[VCount];
    
    Vertices[0].Position = FVector(-0.5f+1.0f, -0.5f, 0.0f);
    Vertices[1].Position = FVector(-0.5f+1.0f, +0.5f, 0.0f);
    Vertices[2].Position = FVector(+0.5f+1.0f, -0.5f, 0.0f);
    Vertices[3].Position = FVector(+0.5f+1.0f, +0.5f, 0.0f);

    Vertices[0].Uv = FVector2D(0.0f, 5.0f);
    Vertices[1].Uv = FVector2D(0.0f, 0.0f);
    Vertices[2].Uv = FVector2D(5.0f, 5.0f);
    Vertices[3].Uv = FVector2D(5.0f, 0.0f);
    
    VBuffer = new CVertexBuffer(Vertices, VCount, sizeof(FVertexTexture));
    
    Indices = new UINT[ICount]{0, 1 , 2 ,  2,1,3};
    IBuffer = new CIndexBuffer(Indices, ICount);
    
    Texture = new CTexture2D(L"../_Textures/Grass.png");
    
    // 상수 버퍼 3종 생성
    WorldBuffer = new CConstantBuffer(&World, sizeof(FMatrix));
    VPBuffer = new CConstantBuffer(&VPData, sizeof(FViewProjectionData));
    SamplingBuffer = new CConstantBuffer(&SamplingData, sizeof(FSamplingData));
    
    SamplerPoint = new CSamplerState();
    SamplerPoint->SetFilter(D3D11_FILTER_MIN_MAG_MIP_POINT);
    SamplerPoint->Create();
    
    SamplerLinear = new CSamplerState();
    SamplerPoint->SetFilter(D3D11_FILTER_MIN_MAG_MIP_LINEAR);
    SamplerLinear->Create();
    
    World = FMatrix::Identity;
}
    

void CDemo3::Destroy()
{
    Delete(Shader);
    
    Delete(VBuffer);
    Delete(Shader);
    
    DeleteArray(Vertices);
    Delete(VBuffer);

    DeleteArray(Indices);
    Delete(IBuffer);
    
    Delete(Texture);
    
    Delete(WorldBuffer);
    Delete(VPBuffer);
    Delete(SamplingBuffer);
    
    Delete(SamplerPoint);
    Delete(SamplerLinear);
    
    
    
}

void CDemo3::Tick()
{
    
    ImGui::InputInt("HLSL Filter", (int*)&Filter);
    Filter = FMath::Clamp<UINT>(Filter, 0 , 1);
}

void CDemo3::Render()
{
    ID3D11DeviceContext* deviceContext = CD3D::Get()->GetDeviceContext();
    
    WorldBuffer->Update();
    
    VPData.View = CContext::Get()->GetView();
    VPData.Projection = CContext::Get()->GetProjection();
    VPBuffer->Update();
    
    SamplingData.Filter = Filter;
    SamplingBuffer->Update();
    
    // 상수 버퍼 바인딩
    WorldBuffer->BindToVS(0);
    VPBuffer->BindToVS(1);
    SamplingBuffer->BindToPS(2);
    
    // 텍스처 바인딩
    ID3D11ShaderResourceView* srv = *Texture;
    deviceContext->PSSetShaderResources(0, 1, &srv);
    
    // 샘플러 바인딩
    SamplerPoint->BindToPS(6);
    SamplerLinear->BindToPS(7);

    VBuffer->Render();
    IBuffer->Render();
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Shader->Render();
    deviceContext->DrawIndexed(ICount, 0, 0);

}
