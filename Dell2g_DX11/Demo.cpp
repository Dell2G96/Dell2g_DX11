#include "Framework.h"
#include "Demo.h"

void Demo::Initialize()
{
    CContext::Get()->GetCamera()->SetPosition(FVector(0,5.f,-10));
    
    FVertexColor vertices[8];
    
    vertices[0].Position = FVector(0, 0, 0);
    vertices[1].Position = FVector(0, 2, 0);
    vertices[2].Position = FVector(2, 0, 0);
    vertices[3].Position = FVector(2, 2, 0);

    vertices[4].Position = FVector(1, 1, 1);
    vertices[5].Position = FVector(1, 3, 1);
    vertices[6].Position = FVector(3, 1, 1);
    vertices[7].Position = FVector(3, 3, 1);
    
    for (int i =0; i < 4; i++)
    {
        vertices[i].Color = FColor::Red;
        vertices[i+4].Color = FColor::Green;
    }
    
    UINT indices[12] =
    {
        0, 1, 2, 2, 1, 3,
        4, 5, 6, 6, 5, 7,
    };
    
    VBuffer = new CVertexBuffer(vertices, 8, sizeof(FVertexColor));
    IBuffer = new CIndexBuffer(indices, 12);
    
    Shader = new CShader(L"15_DepthStencilView.fx");
    
    Landscape = new CLandscape();
    
}

void Demo::Destroy()
{
    Delete(Shader);
    Delete(VBuffer);
    Delete(IBuffer);

    Delete(Landscape);
}

void Demo::Tick()
{

    
#pragma region 마우스 위치, 델타 값
    ImGui::Text("Position : %s", CMouse::Get()->GetPosition().ToString().c_str());
    ImGui::Text("Delta : %s", CMouse::Get()->GetDelta().ToString().c_str());
#pragma endregion
    
    FMatrix world = FMatrix::Identity;
    Shader->AsMatrix("World")->SetMatrix(world);
    
    FMatrix view = CContext::Get()->GetView();
    Shader->AsMatrix("View")->SetMatrix(view);
    
    FMatrix projection = CContext::Get()->GetProjection();
    Shader->AsMatrix("Projection")->SetMatrix(projection);
    
    Landscape->Tick();
    
}

void Demo::Render()
{
   Landscape->Render();
    
    VBuffer->Render();
    IBuffer->Render();
    
    CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    
    Shader->DrawIndexed(12);
}
