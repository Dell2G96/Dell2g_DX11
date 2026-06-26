#pragma once

#include "Systems/IExecutable.h"

class Demo : public IExecutable
{
public:
    void Initialize() override;
    void Destroy() override;
    void Tick() override; 
    void Render() override;
    
    // void Render_Lerp();
    // void Render_SmoothStep();
    // void Render_Step();
    
private:
    CShader* Shader;
    
    CVertexBuffer* VBuffer;
    CIndexBuffer* IBuffer;

private:
    CLandscape* Landscape;
    
    
};
