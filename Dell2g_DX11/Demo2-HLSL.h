#pragma once

#include "Systems/IExecutable.h"

class Demo2_hlsl : public IExecutable
{
public:
    void Initialize() override;
    void Destroy() override;
    void Tick() override;
    void Render() override;

private:
    void Render_Lerp();
    void Render_Lerp2();
    void Render_Tiling();

private:
    CHLSLShader* Shaders[3] = {};

    UINT VCount = 4;
    FVertexTexture* Vertices = nullptr;
    CVertexBuffer* VBuffer = nullptr;

    UINT ICount = 6;
    UINT* Indices = nullptr;
    CIndexBuffer* IBuffer = nullptr;

    CTexture2D* Textures[4] = {};
    ID3D11ShaderResourceView* SRVs[4] = {};

private:
    // Tiling
    struct FTilingData
    {
        FVector2D Tiling;
        FVector2D Padding;
    };

    FMatrix World;
    FVector2D Tiling = FVector2D(1.0f, 1.0f);
    FViewProjectionData VPData;
    FTilingData TilingData;

    CConstantBuffer* WorldBuffer = nullptr;
    CConstantBuffer* VPBuffer = nullptr;
    CConstantBuffer* TilingBuffer = nullptr;

private:
    CSamplerState* LinearSampler = nullptr;
};
