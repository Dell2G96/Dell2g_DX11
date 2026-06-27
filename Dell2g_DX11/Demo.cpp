#include "Framework.h"
#include "Demo.h"

void Demo::Initialize()
{
    CContext::Get()->GetCamera()->SetPosition(FVector(0,5.f,-10));
    
    Line3D = new CLine3D();
    Landscape = new CLandscape();
    
}

void Demo::Destroy()
{
    Delete(Line3D);
    Delete(Landscape);
}

void Demo::Tick()
{
    
#pragma region 마우스 위치, 델타 값
    ImGui::Text("Position : %s", CMouse::Get()->GetPosition().ToString().c_str());
    ImGui::Text("Delta : %s", CMouse::Get()->GetDelta().ToString().c_str());
#pragma endregion
    
    Line3D->Add(FVector::Zero, FVector::Up, FColor::Red);
    Line3D->Add(FVector::Zero,FColor::Blue,  FVector::Right, FColor::Red);
    
    Line3D->Tick();
    Landscape->Tick();
    
}

void Demo::Render()
{
    Line3D->Render();
   Landscape->Render();
}
