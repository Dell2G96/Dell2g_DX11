#pragma once

#include "Systems/IExecutable.h"



class CDemo3 : public IExecutable
{
    
public:
    void Initialize() override;
    void Destroy() override;
    void Tick()override;
    void Render()override;

    
private:
    CHLSLShader* Shader;
    
    UINT VCount = 4;
    FVertexTexture* Vertices;
    CVertexBuffer* VBuffer;
    
    UINT ICount = 6;
    UINT* Indices;
    CIndexBuffer* IBuffer;
    
    CTexture2D* Texture = nullptr;
    
private:
    UINT Filter = 0;
    
    FMatrix World;
    FViewProjectionData VPData;
    FSamplingData SamplingData;
    
    CConstantBuffer* WorldBuffer = nullptr;
    CConstantBuffer* VPBuffer = nullptr;
    CConstantBuffer* SamplingBuffer = nullptr;
    
private:
    CSamplerState* SamplerPoint = nullptr  ; //(s6); // C++에서 Filter = MIN_MAG_MIP_POINT
    CSamplerState* SamplerLinear = nullptr ;//(s7); // C++에서 Filter = MIN_MAG_MIP_LINEAR

    
};
