#pragma once

class CModelMesh
{
private:
    friend class CMeshRenderer;
    
private:
    CModelMesh(CShader* InShader);
    ~CModelMesh();
    
    void Tick();
    void Render();
    
private:
    void CreateBuffer();
    
    FVector GetSize();
    FVector GetExtent();
    
private:
    CShader* Shader;
    
    string Name;
    
    FVector MinPoint;
    FVector MaxPoint;
    
    UINT VCount;
    FVertexModel* Vertices;
    
    UINT ICount;
    UINT* Indices;
    
    CVertexBuffer* VBuffer;
    CIndexBuffer* IBuffer;
    
};
