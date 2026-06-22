#include "Framework.h"
#include "Demo.h"

void Demo::Initialize()
{
    Shader = new CShader(L"11_VertexColor.fx");
    
    // 버텍스 버퍼 설정
    Vertices = new FVertexColor[VCount];

    Vertices[0].Position = FVector(-0.5f, 0.0f, -0.5f);
    Vertices[1].Position = FVector(-0.5f, 0.0f, +0.5f);
    Vertices[2].Position = FVector(+0.5f, 0.0f, -0.5f);
    Vertices[3].Position = FVector(+0.5f, 0.0f, +0.5f);

    //Vertices[0].Color = FColor::White;
    //Vertices[1].Color = FColor::Blue;
    //Vertices[2].Color = FColor::Green;
    //Vertices[3].Color = FColor::Red;

    Vertices[0].Color = FColor::White;
    Vertices[1].Color = FColor::White;
    Vertices[2].Color = FColor::White;
    Vertices[3].Color = FColor::White;
    
    VBuffer = new CVertexBuffer(Vertices,VCount, sizeof(FVertexColor));
    
    
    // 인덱서 버퍼 설정
    Indices = new UINT[ICount]{0,1,2, 2,1,3};
    
    IBuffer = new CIndexBuffer(Indices, ICount);
    
    World = FMatrix::CreateScale(FVector(10, 1, 10));
}

void Demo::Destroy()
{
    Delete(Shader);
    
    DeleteArray(Vertices);
    Delete(VBuffer);
    
    DeleteArray(Indices);
    Delete(IBuffer);
    
}

void Demo::Tick()
{
    if (CKeyboard::Get()->Press(VK_RIGHT))
        World.M41 += 1.0f * CTimer::Get()->GetDeltaTime();
    else if (CKeyboard::Get()->Press(VK_LEFT))
        World.M41 -= 1.0f * CTimer::Get()->GetDeltaTime();
    
    if (CKeyboard::Get()->Press(VK_UP))
        World.M43 += 1.0f * CTimer::Get()->GetDeltaTime();
    else if (CKeyboard::Get()->Press(VK_DOWN))
        World.M43 -= 1.0f * CTimer::Get()->GetDeltaTime();
    
    string str = "";
    if (CMouse::Get()->Press(0)) str += "Left,";
    if (CMouse::Get()->Press(1)) str += "Right,";
    if (CMouse::Get()->Press(2)) str += "Middle,";
    
    ImGui::Text("Press : %s", str.c_str());
    
    ImGui::Text("Position : %s", CMouse::Get()->GetPosition().ToString().c_str());
    ImGui::Text("Delta : %s", CMouse::Get()->GetDelta().ToString().c_str());
}

void Demo::Render()
{
    Shader->AsMatrix("World")->SetMatrix(World);
    
    FMatrix view = CContext::Get()->GetView();
    Shader->AsMatrix("View")->SetMatrix(view);
    
    FMatrix projection = CContext::Get()->GetProjection();
    Shader->AsMatrix("Projection")->SetMatrix(projection);
    

    VBuffer->Render();
    IBuffer->Render();
    
    CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Shader->SetPassNumber(0);
    Shader->DrawIndexed(ICount);
}
