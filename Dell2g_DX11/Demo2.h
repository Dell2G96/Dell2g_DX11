#pragma once

#include "Systems/IExecutable.h"

class CDemo2 : public IExecutable
{
public:
    void Initialize();
    void Destroy();
    void Tick();
    void Render();

private:
    CShader* Shader;

    UINT VCount = 6 * 4;
    FVertexColor* Vertices;
    CVertexBuffer* VBuffer;

    UINT ICount = 6 * 6;
    UINT* Indices;
    CIndexBuffer* IBuffer;

private:
    FMatrix World;

private:
    float Speed = 200.0f;
    float RotationY = 0.0f;

    float Radian = 0.0f;
};