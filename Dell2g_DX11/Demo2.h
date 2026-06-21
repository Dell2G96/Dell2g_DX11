#pragma once

#include "Systems/IExecutable.h"

class CDemo2 : public IExecutable
{
public:
    void Initialize() override;
    void Destroy() override;
    void Tick() override;
    void Render() override;
    
private:
  FColor Color = FColor::Blue;

private:
    CShader* Shader;
    
    FVector Vertices[4];
    CVertexBuffer* VBuffer;
    
    UINT Indices[6];
    CIndexBuffer* IBuffer;
    
private:
    FMatrix World;
    FMatrix View;
    FMatrix Projection;
    
};
