#pragma once

class CMeshRenderer
{
public:
    CMeshRenderer(CShader* InShader);
    CMeshRenderer(CHLSLShader* InShader);
    ~CMeshRenderer();
    
    void Tick();
    void Render();
    
public:
    void ReadMaterial(wstring InFile);
    void ReadMaterialHLSL(wstring InFile);
    void ReadMesh(wstring InFile);
    void SetWorld(FMatrix InWorld);
    void RenderHLSL();
    
    FVector GetSize(UINT InIndex = 0);
    FVector GetExtent(UINT InIndex = 0);
    
private:
    CShader* Shader = nullptr;
    CHLSLShader* HLSLShader = nullptr;
    
    struct FFrameDesc
    {
        FMatrix World;
        FMatrix View;
        FMatrix Projection;
    } FrameData;
    
    struct FLightDesc
    {
        FVector LightDirection;
        float Padding = 0.0f;
    } LightData;
    
    CConstantBuffer* FrameBuffer = nullptr;
    CConstantBuffer* LightBuffer = nullptr;
    
    map<string, CMaterial*> MaterialTable;
    vector<class CModelMesh*> Meshes;
    
};
