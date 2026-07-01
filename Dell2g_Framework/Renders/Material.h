#pragma once

class CMaterial
{
public:
    CMaterial(CShader* InShader);
    CMaterial(CHLSLShader* InShader);
    ~CMaterial();
    
    void Render();
    void RenderHLSL();
    
public:
    bool GetDraw() { return bDraw; }
    
    void OnDraw() {bDraw = true;}
    void OffDraw() {bDraw = false;}
    
public:
    void SetDiffuse(const FColor& InColor) { Data.Diffuse = InColor;}
    void SetTiling(const FVector2D& InValue) { Data.Tiling = InValue;}
    void SetDiffuseMap(wstring InFilePath, bool bDefaultPath = true );
    
private:
    struct FDesc
    {
        FColor Diffuse = FColor::White;
        
        FVector2D Tiling = FVector2D::One;
        float HasDiffuseMap = 0.0f;
        float Padding = 0.0f;
    }Data;
    CConstantBuffer* CBuffer = nullptr;
    CConstantBuffer* HLSLBuffer = nullptr;
    CSamplerState* Sampler = nullptr;
    
private:
    CShader* Shader = nullptr;
    CHLSLShader* HLSLShader = nullptr;
    
private:
    bool bDraw = true;
private:
    CTexture2D* DiffuseMap = nullptr;
};
