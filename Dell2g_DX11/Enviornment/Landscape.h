#pragma once

class CLandscape
{
private:
    typedef FVertexTextureNormal FVertexTerrain;
    
public:
    CLandscape();
    ~CLandscape();
    
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
        
        FVector2D Tiling = FVector2D(32,32);
        float Padding[2];
    } Data;
    CConstantBuffer* CBuffer;
    
private:
    struct FFrameDesc
    {
        FMatrix World;
        FMatrix View;
        FMatrix Projection;
    } FrameData;
    CConstantBuffer* CFrameBuffer;
    
private:
    CShader* Shader;
    UINT Pass =0;
    
private:
    CTexture2D* HeightMap;


private:
    UINT Width, Height;
    
    UINT VCount;
    FVertexTerrain* Vertices;
    
    UINT ICount;
    UINT* Indices;
    
    CVertexBuffer* VBuffer;
    CIndexBuffer* IBuffer;

    
private:
    CTexture2D* Textures[5];
    
    ID3D11ShaderResourceView* SRVs[5];
    ID3DX11EffectShaderResourceVariable* sSRVs;
    
private:
    CLine3D* Line3D;


private:
    bool bDrawNormal = false;
    UINT DrawGridCount = 1;
    
    
};
