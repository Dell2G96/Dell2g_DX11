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
    UINT Pass =0;
    CShader* Shader;
    
    FVector Vertices[3];
    CVertexBuffer* VBuffer;
    
};
