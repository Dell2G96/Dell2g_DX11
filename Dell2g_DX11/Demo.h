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
    UINT Width = 5;
    UINT Height = 5;
    
private:
    FColor Color = FColor::Red;

private:
    CShader* Shader;
    
    UINT VCount;
    FVector* Vertices;
    CVertexBuffer* VBuffer;
    
    UINT ICount;
    UINT* Indices;
    CIndexBuffer* IBuffer;
    
private:
    FMatrix World;
    
    
};
