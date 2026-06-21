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
    UINT Width = 65;
    UINT Height = 65;

private:
    FColor Color = FColor::White;

private:
    float Speed = 5.0f;
    FVector Position = FVector(0, 0, -10);

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
