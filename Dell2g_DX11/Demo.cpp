#include "Framework.h"
#include "Demo.h"

void Demo::Initialize()
{
    Shader = new CShader(L"09_WorldMatrix.fx");
    
    Vertices[0] = FVector(-0.5f, -0.5f, 0);
    Vertices[1] = FVector(-0.5f, +0.5f, 0);
    Vertices[2] = FVector(+0.5f, -0.5f, 0);
    Vertices[3] = FVector(+0.5f, -0.5f, 0);
    Vertices[4] = FVector(-0.5f, +0.5f, 0);
    Vertices[5] = FVector(+0.5f, +0.5f, 0);
    
    VBuffer = new CVertexBuffer(Vertices, 6, sizeof(FVector));
    
    World = FMatrix::Identity; // 단위 행렬
    
    FVector eye = FVector(0,0,-10);
    View = FMatrix::CreateLookAt(eye, eye + FVector::Forward, FVector::Up);
    
    float width = CD3D::Get()->GetWidth();
    float height = CD3D::Get()->GetHeight();
    float aspect = width / height;
    
    float fov = FMath::Pi * 0.25f;
    Projection = FMatrix::CreatePerspectiveFieldOfView(fov, aspect, 0.1f, 1000.f);
    

}

void Demo::Destroy()
{
    Delete(VBuffer);
    Delete(Shader);
}

void Demo::Tick()
{
#pragma region 색 설정 
    static FColor color = FColor::White;
    // ImGui::Separator();
    // ImGui::SeparatorText("Demo");
    ImGui::ColorEdit3("Color", color);
    Shader->AsVector("Color")->SetFloatVector(color);
    
#pragma endregion
    
#pragma region FPS, 시간 설정

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
#pragma endregion 
    
#pragma region WireFrame Mode
    ImGui::InputInt("Technique - Demo", (int*)&Technique);
    Technique = FMath::Clamp<UINT>(Technique, 0 ,1);
#pragma endregion 

#pragma region Keyboard UI
    // if (CKeyboard::Get()->Press('A'))
    //     Text = "A Press";
    // else
    // {
    //     Text = "";
    // }
    // ImGui::LabelText("Press", Text.c_str());
    //
    // if (CKeyboard::Get()->Down('B'))
    //     MessageBox(CD3D::Get()->GetHandle(), L"B키 눌림", L"", MB_OK);
    //
    // if (CKeyboard::Get()->Up('C'))
    //     MessageBox(CD3D::Get()->GetHandle(), L"C키 뗌", L"", MB_OK);
#pragma endregion 

    if (CKeyboard::Get()->Press(VK_RIGHT))
        World.M41 += 1.0f * CTimer::Get()->GetDeltaTime();
    else if (CKeyboard::Get()->Press(VK_LEFT))
        World.M41 -= 1.0f * CTimer::Get()->GetDeltaTime();
    
    if (CKeyboard::Get()->Press('D'))
        World.M11 += 1.0f * CTimer::Get()->GetDeltaTime();
    else if (CKeyboard::Get()->Press('A'))
        World.M11 -= 1.0f * CTimer::Get()->GetDeltaTime();
    
    if (CKeyboard::Get()->Press('W'))
        World.M22 += 1.0f * CTimer::Get()->GetDeltaTime();
    else if (CKeyboard::Get()->Press('S'))
        World.M22 -= 1.0f * CTimer::Get()->GetDeltaTime();
    
    if (CKeyboard::Get()->Press(VK_RIGHT))
        World.M41 += 1.0f * CTimer::Get()->GetDeltaTime();
    else if (CKeyboard::Get()->Press(VK_LEFT))
        World.M41 -= 1.0f * CTimer::Get()->GetDeltaTime();
    
    
}

void Demo::Render()
{
    Shader->AsMatrix("World")->SetMatrix(World);
    Shader->AsMatrix("View")->SetMatrix(View);
    Shader->AsMatrix("Projection")->SetMatrix(Projection);
    Shader->AsMatrix("Color")->SetFloatVector(Color);
    VBuffer->Render();

    CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Shader->SetTechniqueNumber(Technique);
    Shader->SetPassNumber(0);
    Shader->Draw(6);
}