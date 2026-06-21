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
    UINT Technique = 0;
    UINT Pass = 2;
    FColor Color = FColor::Blue;

private:
    CShader* Shader;
    
    FVector Vertices[4];
    CVertexBuffer* VBuffer;
    
};
