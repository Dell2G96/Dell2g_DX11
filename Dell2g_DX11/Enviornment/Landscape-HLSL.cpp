#include "Framework.h"
#include "Landscape-HLSL.h"

CLandscapeHLSL::CLandscapeHLSL()
{
    Shader = new CHLSLShader(L"14_Landscape.hlsl", "VS", "PS");

    HeightMap = new CTexture2D(L"Landscape/Height256x256.png");
    Texture = new CTexture2D(L"Checker.png");
    TextureSRV = *Texture;

    CreateVertexData();
    CreateIndexData();
    CreateBuffer();

    World = FMatrix::Identity;
    TilingData.Tiling = Tiling;
    TilingData.Padding = FVector2D(0.0f, 0.0f);

    WorldBuffer = new CConstantBuffer(&World, sizeof(FMatrix));
    VPBuffer = new CConstantBuffer(&VPData, sizeof(FViewProjectionData));
    TilingBuffer = new CConstantBuffer(&TilingData, sizeof(FTilingData));

    LinearSampler = new CSamplerState();
    LinearSampler->SetFilter(D3D11_FILTER_MIN_MAG_MIP_LINEAR);
    LinearSampler->SetAddress(D3D11_TEXTURE_ADDRESS_WRAP);
    LinearSampler->Create();
}

CLandscapeHLSL::~CLandscapeHLSL()
{
    Delete(Shader);

    Delete(HeightMap);
    Delete(Texture);

    DeleteArray(Vertices);
    DeleteArray(Indices);

    Delete(VBuffer);
    Delete(IBuffer);

    Delete(WorldBuffer);
    Delete(VPBuffer);
    Delete(TilingBuffer);

    Delete(LinearSampler);
}

void CLandscapeHLSL::Tick()
{
    ImGui::InputFloat("HLSL Landscape Tiling X", &Tiling.X, 1.0f);
    ImGui::InputFloat("HLSL Landscape Tiling Y", &Tiling.Y, 1.0f);
}

void CLandscapeHLSL::Render()
{
    ID3D11DeviceContext* deviceContext = CD3D::Get()->GetDeviceContext();

    VPData.View = CContext::Get()->GetView();
    VPData.Projection = CContext::Get()->GetProjection();
    TilingData.Tiling = Tiling;

    WorldBuffer->Update();
    VPBuffer->Update();
    TilingBuffer->Update();

    WorldBuffer->BindToVS(0);
    VPBuffer->BindToVS(1);
    TilingBuffer->BindToPS(2);

    deviceContext->PSSetShaderResources(0, 1, &TextureSRV);
    LinearSampler->BindToPS(0);

    VBuffer->Render();
    IBuffer->Render();
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Shader->Render();
    deviceContext->DrawIndexed(ICount, 0, 0);
}

void CLandscapeHLSL::CreateVertexData()
{
    vector<FColor> pixels;
    HeightMap->GetImage()->GetPixels(pixels);

    Width = HeightMap->GetImage()->GetWidth();
    Height = HeightMap->GetImage()->GetHeight();

    VCount = Width * Height;
    Vertices = new FVertexTexture[VCount];

    for (UINT z = 0; z < Height; z++)
    {
        for (UINT x = 0; x < Width; x++)
        {
            UINT index = Width * z + x;

            Vertices[index].Position.X = (float)x;
            Vertices[index].Position.Y = pixels[index].R * MaxHeight;
            Vertices[index].Position.Z = (float)z;

            Vertices[index].Uv.X = (float)x / (float)Width;
            Vertices[index].Uv.Y = (float)z / (float)Height;
        }
    }
}

void CLandscapeHLSL::CreateIndexData()
{
    ICount = (Width - 1) * (Height - 1) * 6;
    Indices = new UINT[ICount];

    UINT index = 0;
    for (UINT z = 0; z < Height - 1; z++)
    {
        for (UINT x = 0; x < Width - 1; x++)
        {
            Indices[index + 0] = Width * z + x;
            Indices[index + 1] = Width * (z + 1) + x;
            Indices[index + 2] = Width * z + x + 1;

            Indices[index + 3] = Width * z + x + 1;
            Indices[index + 4] = Width * (z + 1) + x;
            Indices[index + 5] = Width * (z + 1) + x + 1;

            index += 6;
        }
    }
}

void CLandscapeHLSL::CreateBuffer()
{
    VBuffer = new CVertexBuffer(Vertices, VCount, sizeof(FVertexTexture));
    IBuffer = new CIndexBuffer(Indices, ICount);
}
