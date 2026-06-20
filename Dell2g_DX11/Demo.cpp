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
    
    const float x = 5.0f;
    const float y = 5.0f;
    const float lineHeight = 20.f;
    
    // 오늘 날짜 현재 시간 출력
    CGui::Get()->RenderText(x,y,1,1,1,CTimer::Get()->GetCurrentTimeText());
    
    // FPS 출력
    string fps = "";
    fps += "FPS : ";
    fps += to_string(CTimer::Get()->GetFPS());
    CGui::Get()->RenderText(x,y+lineHeight,1,1,1,fps);
    
    // 경과 시간 출력
    string time = "";
    time += "경과시간 : ";
    time += to_string(CTimer::Get()->GetRunningTime());
    CGui::Get()->RenderText(x,y+lineHeight * 2.0f,1,1,1,time);
}

void Demo::Render()
{
    VBuffer->Render();

    CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Shader->SetPassNumber(4);
    Shader->Draw(3);
}