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
    CShader* Shader;
    UINT Pass =0;
    
private:
    CTexture2D* HeightMap;
    
private:
    FVector2D Tiling = FVector2D(32, 32);
    
    float MaxHeight = 50.0;
    
    float LowRatio = 0.2f;
    float HighRatio = 0.65f;
    
    float GentleAngle = 0.3f;
    float SteepAngle = 0.3f;
    
    
    UINT Width, Height;
    
    UINT VCount;
    FVertexTerrain* Vertices;
    
    UINT ICount;
    UINT* Indices;
    
    CVertexBuffer* VBuffer;
    CIndexBuffer* IBuffer;
    
private:
    FMatrix World;
    
private:
    CTexture2D* Textures[5];
    
    ID3D11ShaderResourceView* SRVs[5];
    ID3DX11EffectShaderResourceVariable* sSRVs;
    
private:
    CLine3D* Line3D;
    
private:
    FVector LightDirection = FVector(1.0f, 0.0f,0.0f);
    
private:
    bool bDrawNormal = false;
    UINT DrawGridCount = 1;
    
    
};
