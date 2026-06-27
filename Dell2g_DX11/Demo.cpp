#include "Framework.h"
#include "Demo.h"

void Demo::Initialize()
{
    CContext::Get()->GetCamera()->SetPosition(FVector(0,0.f,-10));
    
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
    
    // Vector
    {
        Line3D->Add(FVector::Zero, FVector::Up, FColor::Red);
        Line3D->Add(FVector::Zero,FColor::Blue,  FVector::Right, FColor::Red);
        
        FMatrix yaw = FMatrix::Identity;
        FVector rotation = FVector::Zero;
        
        yaw = FMatrix::CreateRotationY(45.0f);
        rotation = FVector::TransformNormal(FVector::Forward, yaw);
        
        Line3D->Add(FVector::Zero, rotation, 1.0f, FColor::Yellow);
        
        yaw = FMatrix::CreateRotationY(-45.0f);
        rotation = FVector::TransformNormal(FVector::Forward, yaw);
        
        Line3D->Add(FVector::Zero, FColor::Blue, rotation, 1.0f, FColor::Yellow);
    }
    
    // Vector - Dot
    {
        if (CKeyboard::Get()->Press(VK_RIGHT))
            Rotation += 50.f * CTimer::Get()->GetDeltaTime();
        else if (CKeyboard::Get()->Press(VK_LEFT))
            Rotation -= 50.f * CTimer::Get()->GetDeltaTime();
        
        Rotation = FMath::WrapAngle(Rotation);
        ImGui::Text("Rotation : %f", Rotation );
        
        FMatrix rotation = FMatrix::CreateRotationY(FMath::ToRadians(Rotation));
        FVector direction = FVector::TransformNormal(FVector::Right, rotation);
        direction = FVector::Normalize(direction);
        ImGui::Text("Direction : %s", direction.ToString().c_str());
        
        float dot = FVector::Dot(FVector::Forward, direction);
        ImGui::Text("Dot : %f", dot);
        
        Line3D->Add(FVector::Zero, FVector::Zero + FVector::Forward * LineLength, FColor::Green);
        Line3D->Add(FVector::Zero, FVector::Zero + direction * LineLength, FColor::Red);
    }
    
    Line3D->SetWorld(FMatrix::CreateTranslation(FVector(3,0,0)));
    Line3D->Tick();
    Landscape->Tick();
    
}

void Demo::Render()
{
    Line3D->Render();
   Landscape->Render();
}
