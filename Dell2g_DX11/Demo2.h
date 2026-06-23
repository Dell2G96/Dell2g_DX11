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
    UINT Filter = 0;

private:
    CShader* Shader;

    UINT VCount = 4;
    FVertexTexture* Vertices;
    CVertexBuffer* VBuffer;

    UINT ICount = 6;
    UINT* Indices;
    CIndexBuffer* IBuffer;

private:
    FMatrix World;

    CTexture2D* Texture;
};