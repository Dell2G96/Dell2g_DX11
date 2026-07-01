#pragma once

#include "Systems/IExecutable.h"

class Demo : public IExecutable
{
public:
    void Initialize() override;
    void Destroy() override;
    void Tick() override; 
    void Render() override;
    
private:
    CLandscape* Landscape;
    
private:
    CShader* Shader;

    // 1개 모델만 불러올 때
    //const wstring names = L"BlackPanther";
    //CMeshRenderer* MeshRender;
    
    
    // 여러개 모델 불러올 떄
     const wstring names[2]=
         {
         L"BlackPanther",
         L"Ittan_momen"
     };
    CMeshRenderer* MeshRenderers[2];
    
};
