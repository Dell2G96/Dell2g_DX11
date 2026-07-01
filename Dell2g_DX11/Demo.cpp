#include "PCH.h"
#include "Demo.h"

void Demo::Initialize()
{
    CContext::Get()->GetCamera()->SetRotation(FVector(14.5f, 0.0f, 0.0f));
    CContext::Get()->GetCamera()->SetPosition(FVector(0.0f, 2.0f, -8.5f));
    
    Landscape = new CLandscape();
    
    Shader = new CShader(L"21_Material-Texture.fx");
    
    
    // 1개 모델 불러올 때
    // MeshRender = new CMeshRenderer(Shader);
    // MeshRender->ReadMaterial(names);
    // MeshRender->ReadMesh(names);
    
    
    for (int i =0; i < 2; i++)
    {
        MeshRenderers[i] = new CMeshRenderer(Shader);
        MeshRenderers[i]->ReadMaterial(names[i]);
        MeshRenderers[i]->ReadMesh(names[i]);
    }
    
    
}

void Demo::Destroy()
{
    Delete(Landscape);
    
    //Delete(MeshRender);
    
    for (int i =0; i < 2; i++)
        Delete(MeshRenderers[i]);
}

void Demo::Tick()
{
    
#pragma region 마우스 위치, 델타 값
    ImGui::Text("Position : %s", CMouse::Get()->GetPosition().ToString().c_str());
    ImGui::Text("Delta : %s", CMouse::Get()->GetDelta().ToString().c_str());
#pragma endregion

    Landscape->Tick();
    
    for (int i =0; i < 2; i++)
        MeshRenderers[i]->Tick();
    
    //MeshRender->Tick();
    
}

void Demo::Render()
{
   Landscape->Render();
   
    
    
    
    // 여러개 모델 불러올 때
    for (int i =0; i < 2; i++)
    {
        FVector position = FVector((float)i * 1.5f, 0.f,(float)i* 1.5f);
        position.Y = MeshRenderers[i]->GetExtent().Y;

        if (i == 0)
        {
            position = FVector(0.f,0.f,1.f);
            position.Y = MeshRenderers[0]->GetExtent().Y;
            
            FMatrix rotation = FMatrix::CreateRotationX(FMath::Pi * 0.5f);
            FMatrix translation = FMatrix::CreateTranslation(position);
    
    
            FMatrix world = rotation * translation;
            Shader->AsMatrix("World")->SetMatrix(world);
    
            MeshRenderers[0]->Render();
            continue;
        }
        if (i == 1)
        {
               float scaleValue = 10.f;
            FMatrix scale = FMatrix::CreateScale(scaleValue);
            
            FMatrix translation = FMatrix::CreateTranslation(position);
            
            FMatrix world = scale * translation;
            Shader->AsMatrix("World")->SetMatrix(world);
            
        }
        
        
        
        MeshRenderers[i]->Render();
    }
}
