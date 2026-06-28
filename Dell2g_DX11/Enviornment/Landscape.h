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
    FVector2D Tiling = FVector2D(64, 64);
    float MaxHeight = 25.0;
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
    CTexture2D* Texture;
    
private:
    CLine3D* Line3D;
    FVector LightDirection = FVector(1.0f, 0.0f,0.0f);
    
    
};
