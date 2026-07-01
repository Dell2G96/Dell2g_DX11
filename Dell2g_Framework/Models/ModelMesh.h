#pragma once

class CModelMesh
{
private:
    friend class CMeshRenderer;
    
private:
    CModelMesh(CShader* InShader);
    CModelMesh(CHLSLShader* InShader);
    ~CModelMesh();
    
    void Tick();
    void Render();
    void RenderHLSL();
    
private:
    void CreateBuffer();
    
    FVector GetSize();
    FVector GetExtent();
    
private:
    CShader* Shader = nullptr;
    CHLSLShader* HLSLShader = nullptr;
    
    string Name;
    string MaterialName;
    CMaterial* Material = nullptr;
    
    FVector MinPoint;
    FVector MaxPoint;
    
    UINT VCount;
    FVertexModel* Vertices;
    
    UINT ICount;
    UINT* Indices;
    
    CVertexBuffer* VBuffer;
    CIndexBuffer* IBuffer;
    
};
