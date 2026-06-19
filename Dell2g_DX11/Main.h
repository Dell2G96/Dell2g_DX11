#pragma once
#include "Systems/IExecutable.h"

class CMain : public IExecutable
{
public:
    void Initialize() override;
    void Destroy() override;
    void Tick() override;
    void Render() override;
    
private:
    CShader* Shader;
    
    FVector Vertices [2];
    CVertexBuffer* VBuffer;
};


