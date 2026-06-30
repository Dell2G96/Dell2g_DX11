#include "PCH.h"
#include "Demo.h"

void Demo::Initialize()
{
    CContext::Get()->GetCamera()->SetRotation(FVector(14.5f, 0.0f, 0.0f));
    CContext::Get()->GetCamera()->SetPosition(FVector(0.0f, 2.0f, -8.5f));
    
    Landscape = new CLandscape();
    
    Shader = new CShader(L"20_Meshrenderer.fx");
    
    MeshRender = new CMeshRenderer(Shader);
    MeshRender->ReadMesh(names);
    // for (int i =0; i < 7; i++)
    // {
    //     MeshRenderers[i] = new CMeshRenderer(Shader);
    //     MeshRenderers[i]->ReadMesh(names[i]);
    // }
    
    
}

void Demo::Destroy()
{
    Delete(Landscape);
    
    Delete(MeshRender);
    // for (int i =0; i < 7; i++)
    //     Delete(MeshRenderers[i]);
}

void Demo::Tick()
{
    
#pragma region 마우스 위치, 델타 값
    ImGui::Text("Position : %s", CMouse::Get()->GetPosition().ToString().c_str());
    ImGui::Text("Delta : %s", CMouse::Get()->GetDelta().ToString().c_str());
#pragma endregion

    Landscape->Tick();
    // for (int i =0; i < 7; i++)
    //     MeshRenderers[i]->Tick();
    
    MeshRender->Tick();
    
}

void Demo::Render()
{
   Landscape->Render();
   
    FVector position = FVector(5.f,0.f,1.f);
    position.Y = MeshRender->GetExtent().Y;
    
    FMatrix rotation = FMatrix::CreateRotationX(FMath::Pi * 0.5f);
    FMatrix translation = FMatrix::CreateTranslation(position);
    
    
    FMatrix world = rotation * translation;
    Shader->AsMatrix("World")->SetMatrix(world);
    
    MeshRender->Render();
    // for (int i =0; i < 7; i++)
    // {
    //     FVector position = FVector((float)i * 1.5f, 0.f,(float)i* 1.5f);
    //     position.Y = MeshRenderers[i]->GetExtent().Y;
    //     
    //     FMatrix world = FMatrix::CreateTranslation(position);
    //     Shader->AsMatrix("World")->SetMatrix(world);
    //     
    //     MeshRenderers[i]->Render();
    // }
}
