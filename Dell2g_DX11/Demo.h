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

    const wstring names = L"BlackPanther";
    CMeshRenderer* MeshRender;
    // const wstring names[7]=
    //     {
    //     L"Arrow",
    //     L"Capsule",
    //     L"Cone",
    //     L"Cube",
    //     L"Cylinder",
    //     L"Sphere",
    //     L"Torus"
    // };
    //CMeshRenderer* MeshRenderers[7];
    
};
