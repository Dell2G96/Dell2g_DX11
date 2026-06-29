#pragma once

class CLandscapeHLSL
{
private:
    typedef FVertexTextureNormal FVertexTerrain;

public:
    CLandscapeHLSL();
    ~CLandscapeHLSL();

    void Tick();
    void Render();

private:
    void CreateVertexData();
    void CreateIndexedData();
    void CreateNormalVector();
    void CreateBuffer();

private:
    struct FDesc
    {
        FVector LightDirection = FVector(-1.f, -1.f, +1.f);
        float MaxHeight = 50.f;

        float LowRatio = 0.2f;
        float HighRatio = 0.65f;
        float GentleAngle = 0.3f;
        float SteepAngle = 0.7f;

        FVector2D Tiling = FVector2D(32, 32);
        float Padding[2];
    } Data;
    CConstantBuffer* CBuffer = nullptr;

private:
    struct FFrameDesc
    {
        FMatrix World;
        FMatrix View;
        FMatrix Projection;
    } FrameData;
    CConstantBuffer* CFrameBuffer = nullptr;

private:
    CHLSLShader* Shader = nullptr;

private:
    CTexture2D* HeightMap = nullptr;

private:
    UINT Width = 0;
    UINT Height = 0;

    UINT VCount = 0;
    FVertexTerrain* Vertices = nullptr;

    UINT ICount = 0;
    UINT* Indices = nullptr;

    CVertexBuffer* VBuffer = nullptr;
    CIndexBuffer* IBuffer = nullptr;

private:
    CTexture2D* Textures[5];
    ID3D11ShaderResourceView* SRVs[5];
    CSamplerState* LinearSampler = nullptr;

private:
    CLine3D* Line3D = nullptr;

private:
    bool bDrawNormal = false;
    UINT DrawGridCount = 1;
};
