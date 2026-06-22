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
    CShader* Shader;
    
    UINT VCount = 4;
    FVertexColor* Vertices;
    CVertexBuffer* VBuffer;
    
    UINT ICount = 6;
    UINT* Indices;
    CIndexBuffer* IBuffer;
    
private:
    FMatrix World;
    
    
};
