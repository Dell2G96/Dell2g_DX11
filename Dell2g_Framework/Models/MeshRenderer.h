#pragma once

class CMeshRenderer
{
public:
    CMeshRenderer(CShader* InShader);
    ~CMeshRenderer();
    
    void Tick();
    void Render();
    
public:
    void ReadMesh(wstring InFile);
    
    FVector GetSize(UINT InIndex = 0);
    FVector GetExtent(UINT InIndex = 0);
    
private:
    CShader* Shader;
    
    vector<class CModelMesh*> Meshes;
    
};
