#include "Framework.h"
#include "Demo.h"

void Demo::Initialize()
{
    CContext::Get()->GetCamera()->SetPosition(FVector(-14,12.f,-15));
    CContext::Get()->GetCamera()->SetRotation(FVector(7,45.f,0.f));
    
    Landscape = new CLandscape();
    
}

void Demo::Destroy()
{
    Delete(Landscape);
}

void Demo::Tick()
{
    
#pragma region 마우스 위치, 델타 값
    ImGui::Text("Position : %s", CMouse::Get()->GetPosition().ToString().c_str());
    ImGui::Text("Delta : %s", CMouse::Get()->GetDelta().ToString().c_str());
#pragma endregion

    Landscape->Tick();
}

void Demo::Render()
{
   Landscape->Render();
}
