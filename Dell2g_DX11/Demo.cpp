#include "Framework.h"
#include "Demo.h"

void Demo::Initialize()
{
    CContext::Get()->GetCamera()->SetPosition(FVector(0,0.f,-10));
    CContext::Get()->GetCamera()->SetRotation(FVector(0.f,0.f,0.f));
    
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
    
#pragma region vector - Dot
    // // Vector
    // {
    //     Line3D->Add(FVector::Zero, FVector::Up, FColor::Red);
    //     Line3D->Add(FVector::Zero,FColor::Blue,  FVector::Right, FColor::Red);
    //     
    //     FMatrix yaw = FMatrix::Identity;
    //     FVector rotation = FVector::Zero;
    //     
    //     yaw = FMatrix::CreateRotationY(45.0f);
    //     rotation = FVector::TransformNormal(FVector::Forward, yaw);
    //     
    //     Line3D->Add(FVector::Zero, rotation, 1.0f, FColor::Yellow);
    //     
    //     yaw = FMatrix::CreateRotationY(-45.0f);
    //     rotation = FVector::TransformNormal(FVector::Forward, yaw);
    //     
    //     Line3D->Add(FVector::Zero, FColor::Blue, rotation, 1.0f, FColor::Yellow);
    // }
    //
    // // Vector - Dot
    // {
    //     if (CKeyboard::Get()->Press(VK_RIGHT))
    //         Rotation += 50.f * CTimer::Get()->GetDeltaTime();
    //     else if (CKeyboard::Get()->Press(VK_LEFT))
    //         Rotation -= 50.f * CTimer::Get()->GetDeltaTime();
    //     
    //     Rotation = FMath::WrapAngle(Rotation);
    //     ImGui::Text("Rotation : %f", Rotation );
    //     
    //     FMatrix rotation = FMatrix::CreateRotationY(FMath::ToRadians(Rotation));
    //     FVector direction = FVector::TransformNormal(FVector::Right, rotation);
    //     direction = FVector::Normalize(direction);
    //     ImGui::Text("Direction : %s", direction.ToString().c_str());
    //     
    //     float dot = FVector::Dot(FVector::Forward, direction);
    //     ImGui::Text("Dot : %f", dot);
    //     
    //     Line3D->Add(FVector::Zero, FVector::Zero + FVector::Forward * LineLength, FColor::Green);
    //     Line3D->Add(FVector::Zero, FVector::Zero + direction * LineLength, FColor::Red);
    // }
    
#pragma endregion
    
    //Tick_Cross();
    
    Tick_Cross2();
    //Tick_Cross3();
    
    Line3D->Tick();
    Landscape->Tick();
    
}

void Demo::Render()
{
    Line3D->Render();
   Landscape->Render();
}

void Demo::Tick_Cross()
{
    Line3D->Add(FVector::Zero, FVector::Forward, LineLength, FColor::Green);
    Line3D->Add(FVector::Zero, FVector::Right, LineLength, FColor::Red);
    
    FVector cross = FVector::Cross(FVector::Right, FVector::Forward);
    Line3D->Add(FVector::Zero, cross, LineLength, FColor::Blue);
}

void Demo::Tick_Cross2()
{
    if (CKeyboard::Get()->Press(VK_RIGHT))
        Position.X += 1.0f * CTimer::Get()->GetDeltaTime();
    else if (CKeyboard::Get()->Press(VK_LEFT))
        Position.X -= 1.0f * CTimer::Get()->GetDeltaTime();
    
    if (CKeyboard::Get()->Press(VK_UP))
        Position.Z += 1.0f * CTimer::Get()->GetDeltaTime();
    else if (CKeyboard::Get()->Press(VK_DOWN))
        Position.Z -= 1.0f * CTimer::Get()->GetDeltaTime();
    
    Line3D->Add(Position, FVector::Up, 0.5f, FColor::Magenta);
    
    FVector direction = FVector::Normalize(Position);
    Line3D->Add(FVector::Zero, direction, LineLength, FColor::Red);
    Line3D->Add(FVector::Zero, FVector::Forward, LineLength, FColor::Green);
    
    FVector cross = FVector::Cross(FVector::Forward, direction);
    ImGui::Text("Cross : %s", cross.ToString().c_str());
    
    Line3D->Add(FVector::Zero, cross, FColor::Blue);
    
    
    
}

void Demo::Tick_Cross3()
{
    if (CKeyboard::Get()->Press(VK_UP))
        Rotation += 1.0f * CTimer::Get()->GetDeltaTime();
    else if (CKeyboard::Get()->Press(VK_DOWN))
        Rotation -= 1.0f * CTimer::Get()->GetDeltaTime();
    
    Line3D->Add(FVector::Zero, FVector::Up, LineLength, FColor::Red);
    Line3D->Add(FVector::Zero, FVector::Forward, LineLength, FColor::Green);
    
    FMatrix roll = FMatrix::CreateRotationZ(Rotation);
    FVector right = FVector::TransformNormal(FVector::Right, roll);
    
    Line3D->Add(FVector::Zero, right, LineLength, FColor::Blue);

    FVector cross = FVector::Cross(FVector::Forward, right);
    Line3D->Add(FVector::Zero, cross, LineLength, FColor::Yellow);
  
    float dot = FVector::Dot(FVector::Up, cross);
    ImGui::Text("Dot : %f", dot);
}


















