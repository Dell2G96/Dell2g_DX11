#pragma once

#include "Systems/IExecutable.h"

class Demo : public IExecutable
{
public:
    void Initialize() override;
    void Destroy() override;
    void Tick() override; 
    void Render() override;
    
    void Render_Lerp();
    void Render_SmoothStep();
    void Render_Step();
    
private:
    CShader* Shader;
    
    UINT VCount = 4;
    FVertexTexture* Vertices;
    CVertexBuffer* VBuffer;
    
    UINT ICount = 6;
    UINT* Indices;
    CIndexBuffer* IBuffer;
    
private:
    FColor Color0 = FColor::Red;
    FColor Color1 = FColor::Blue;
    
    
};
