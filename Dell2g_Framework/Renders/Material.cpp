#include "Framework.h"
#include "Material.h"

CMaterial::CMaterial(CShader* InShader)
    :Shader(InShader)
{
    CBuffer= new CConstantBuffer(Shader, "CB_Material", &Data, sizeof(FDesc));
}

CMaterial::CMaterial(CHLSLShader* InShader)
    :HLSLShader(InShader)
{
    HLSLBuffer = new CConstantBuffer(&Data, sizeof(FDesc));
    
    Sampler = new CSamplerState();
    Sampler->SetFilter(D3D11_FILTER_MIN_MAG_MIP_LINEAR);
    Sampler->SetAddress(D3D11_TEXTURE_ADDRESS_WRAP);
    Sampler->Create();
}

CMaterial::~CMaterial()
{
    Delete(CBuffer);
    Delete(HLSLBuffer);
    Delete(Sampler);
    Delete(DiffuseMap);
}

void CMaterial::Render()
{
    if (bDraw == false)
        return;
    
    CBuffer->Render();
    if (DiffuseMap != nullptr)
        DiffuseMap->Render();
}

void CMaterial::RenderHLSL()
{
    if (bDraw == false)
        return;
    
    HLSLBuffer->Update();
    HLSLBuffer->BindToPS(1);
    
    if (DiffuseMap != nullptr)
        DiffuseMap->BindToPS(0);
    
    Sampler->BindToPS(0);
}

void CMaterial::SetDiffuseMap(wstring InFilePath, bool bDefaultPath)
{
    Delete(DiffuseMap);
    Data.HasDiffuseMap = 1.0f;
    
    if (Shader != nullptr)
        DiffuseMap = new CTexture2D(Shader, "DiffuseMap", InFilePath, bDefaultPath);
    else
        DiffuseMap = new CTexture2D(InFilePath, bDefaultPath);
}
