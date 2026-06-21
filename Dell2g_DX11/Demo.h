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
    FColor Color = FColor::Red;

private:
    CShader* Shader;
    
    FVector Vertices[4];
    CVertexBuffer* VBuffer;
    
    UINT Indices[6];
    ID3D11Buffer* IBuffer;
    
private:
    FMatrix World;
    FMatrix View;
    FMatrix Projection;
    
};
