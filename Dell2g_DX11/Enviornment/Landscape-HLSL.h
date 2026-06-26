#pragma once

class CLandscapeHLSL
{
public:
    CLandscapeHLSL();
    ~CLandscapeHLSL();

    void Tick();
    void Render();

private:
    void CreateVertexData();
    void CreateIndexData();
    void CreateBuffer();

private:
    struct FTilingData
    {
        FVector2D Tiling;
        FVector2D Padding;
    };

private:
    CHLSLShader* Shader = nullptr;

    CTexture2D* HeightMap = nullptr;
    CTexture2D* Texture = nullptr;
    ID3D11ShaderResourceView* TextureSRV = nullptr;
    CSamplerState* LinearSampler = nullptr;

private:
    FVector2D Tiling = FVector2D(64.0f, 64.0f);
    float MaxHeight = 25.0f;
    UINT Width = 0;
    UINT Height = 0;

    UINT VCount = 0;
    FVertexTexture* Vertices = nullptr;

    UINT ICount = 0;
    UINT* Indices = nullptr;

    CVertexBuffer* VBuffer = nullptr;
    CIndexBuffer* IBuffer = nullptr;

private:
    FMatrix World;
    FViewProjectionData VPData;
    FTilingData TilingData;

    CConstantBuffer* WorldBuffer = nullptr;
    CConstantBuffer* VPBuffer = nullptr;
    CConstantBuffer* TilingBuffer = nullptr;
};
