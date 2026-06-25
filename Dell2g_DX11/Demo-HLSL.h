#pragma once

#include "Systems/IExecutable.h"

class Demo_hlsl : public IExecutable
{
public:
    void Initialize() override;
    void Destroy() override;
    void Tick() override;
    void Render() override;

private:
    void Render_Lerp();
    void Render_SmoothStep();
    void Render_Step();

private:
    CHLSLShader* Shaders[3] = {};

    UINT VCount = 4;
    FVertexTexture* Vertices = nullptr;
    CVertexBuffer* VBuffer = nullptr;

    UINT ICount = 6;
    UINT* Indices = nullptr;
    CIndexBuffer* IBuffer = nullptr;

private:
    struct FBlendColorData
    {
        FColor Color0;
        FColor Color1;
    };

    FMatrix World;
    FViewProjectionData VPData;
    FBlendColorData ColorData;

    CConstantBuffer* WorldBuffer = nullptr;
    CConstantBuffer* VPBuffer = nullptr;
    CConstantBuffer* ColorBuffer = nullptr;
};
