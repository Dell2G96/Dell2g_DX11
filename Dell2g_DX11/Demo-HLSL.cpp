#include "PCH.h"
#include "Demo-HLSL.h"

void Demo_hlsl::Initialize()
{
    CContext::Get()->GetCamera()->SetPosition(FVector(128.0f, 45.0f, -80.0f));
    CContext::Get()->GetCamera()->SetRotation(FVector(-15.0f, 0.0f, 0.0f));
    CContext::Get()->SetCameraMoveSpeed(30.0f);
    CContext::Get()->SetCameraRotaionSpeed(120.0f);

    Landscape = new CLandscapeHLSL();
}

void Demo_hlsl::Destroy()
{
    Delete(Landscape);
}

void Demo_hlsl::Tick()
{
    ImGui::Text("Position : %s", CMouse::Get()->GetPosition().ToString().c_str());
    ImGui::Text("Delta : %s", CMouse::Get()->GetDelta().ToString().c_str());

    Landscape->Tick();
}

void Demo_hlsl::Render()
{
    Landscape->Render();
}
