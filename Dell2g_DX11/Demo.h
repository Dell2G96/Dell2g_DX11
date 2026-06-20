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
    
    FVector Vertices[3];
    CVertexBuffer* VBuffer;
    
};
