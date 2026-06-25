#pragma once

#include "Systems/IExecutable.h"

class CDemo2 : public IExecutable
{
public:
    void Initialize();
    void Destroy();
    void Tick();
    void Render();
    
    void Render_Lerp();
    void Render_Lerp2();
    void Render_Tiling();

private:
    FVector2D Tiling = FVector2D::One;
    
private:
    CShader* Shader;

    UINT VCount = 4;
    FVertexTexture* Vertices;
    CVertexBuffer* VBuffer;

    UINT ICount = 6;
    UINT* Indices;
    CIndexBuffer* IBuffer;

private:
    CTexture2D* Textures[4];
    ID3D11ShaderResourceView* SRVs[4];
};