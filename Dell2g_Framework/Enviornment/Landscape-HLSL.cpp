#include "Framework.h"
#include "Landscape-HLSL.h"

CLandscapeHLSL::CLandscapeHLSL()
{
    Shader = new CHLSLShader(L"19_ConstantBuffer.hlsl", "VS", "PS");

    HeightMap = new CTexture2D(L"Landscape/Height256x256_2.png");

    FrameData.World = FMatrix::Identity;

    CBuffer = new CConstantBuffer(&Data, sizeof(FDesc));
    CFrameBuffer = new CConstantBuffer(&FrameData, sizeof(FFrameDesc));

    CreateVertexData();
    CreateIndexedData();
    CreateNormalVector();
    CreateBuffer();

    Textures[0] = new CTexture2D(L"Landscape/BaseMap.png");
    Textures[1] = new CTexture2D(L"Landscape/LowMap.png");
    Textures[2] = new CTexture2D(L"Landscape/HighMap.png");
    Textures[3] = new CTexture2D(L"Landscape/HighestMap.png");
    Textures[4] = new CTexture2D(L"Landscape/SlopeMap.png");

    for (UINT i = 0; i < 5; i++)
        SRVs[i] = *Textures[i];

    LinearSampler = new CSamplerState();
    LinearSampler->SetFilter(D3D11_FILTER_MIN_MAG_MIP_LINEAR);
    LinearSampler->SetAddress(D3D11_TEXTURE_ADDRESS_WRAP);
    LinearSampler->Create();

    Line3D = new CLine3D(Width * Height);
}

CLandscapeHLSL::~CLandscapeHLSL()
{
    Delete(Shader);
    Delete(HeightMap);

    DeleteArray(Vertices);
    DeleteArray(Indices);

    Delete(VBuffer);
    Delete(IBuffer);

    for (CTexture2D* texture : Textures)
        Delete(texture);

    Delete(CBuffer);
    Delete(CFrameBuffer);
    Delete(LinearSampler);
    Delete(Line3D);
}

void CLandscapeHLSL::Tick()
{
    FrameData.View = CContext::Get()->GetView();
    FrameData.Projection = CContext::Get()->GetProjection();

    
    ImGui::Separator();
    ImGui::SeparatorText("HLSL Tiling");

    ImGui::InputFloat("HLSL Tiling - X", &Data.Tiling.X, 1.0f);
    ImGui::InputFloat("HLSL Tiling - Y", &Data.Tiling.Y, 1.0f);

    
    ////////////////////////////////////////////////////////////////////
    ImGui::Separator();
    ImGui::SeparatorText("HLSL LightDirection");
    ImGui::SliderFloat3("HLSL LightDirection", Data.LightDirection, -1.0f, +1.0f);


    ////////////////////////////////////////////////////////////////////
    ImGui::Separator();
    ImGui::SeparatorText("HLSL Height");
    
    ImGui::InputFloat("HLSL LowRatio", &Data.LowRatio, 0.05f);
    Data.LowRatio = FMath::Clamp<float>(Data.LowRatio, 0.0f, 0.5f);


    ImGui::InputFloat("HLSL HighRatio", &Data.HighRatio, 0.05f);
    Data.HighRatio = FMath::Clamp<float>(Data.HighRatio, 0.5f, 1.0f);

    ImGui::InputFloat("HLSL GentleAngle", &Data.GentleAngle, 0.05f);
    Data.GentleAngle = FMath::Clamp<float>(Data.GentleAngle, 0.0f, 0.5f);

    ImGui::InputFloat("HLSL SteepAngle", &Data.SteepAngle, 0.05f);
    Data.SteepAngle = FMath::Clamp<float>(Data.SteepAngle, 0.5f, 1.0f);

    ////////////////////////////////////////////////////////////////////

    ImGui::Separator();
    ImGui::SeparatorText("HLSL Normal");

    ImGui::Checkbox("HLSL DrawNormal", &bDrawNormal);
    ImGui::InputInt("HLSL DrawGridCount", (int*)&DrawGridCount);
    DrawGridCount = FMath::Clamp<UINT>(DrawGridCount, 1, 10);

    if (bDrawNormal)
    {
        for (UINT z = 0; z < Height; z += DrawGridCount)
        {
            for (UINT x = 0; x < Width; x += DrawGridCount)
            {
                UINT index = Width * z + x;

                FVector position = Vertices[index].Position;
                FVector normal = Vertices[index].Normal;
                Line3D->Add(position, position + normal, FColor::Blue);
            }
        }

        Line3D->Tick();
    }
}

void CLandscapeHLSL::Render()
{
    ID3D11DeviceContext* deviceContext = CD3D::Get()->GetDeviceContext();

    if (bDrawNormal)
        Line3D->Render();

    VBuffer->Render();
    IBuffer->Render();

    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    CFrameBuffer->Update();
    CBuffer->Update();

    CFrameBuffer->BindToVS(0);
    CBuffer->BindToPS(1);

    deviceContext->PSSetShaderResources(0, 5, SRVs);
    LinearSampler->BindToPS(0);

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
    Vertices = new FVertexTerrain[VCount];

    for (UINT z = 0; z < Height; z++)
    {
        for (UINT x = 0; x < Width; x++)
        {
            UINT index = Width * z + x;

            Vertices[index].Position.X = (float)x;
            Vertices[index].Position.Y = pixels[index].R * Data.MaxHeight;
            Vertices[index].Position.Z = (float)z;

            Vertices[index].Uv.X = (float)x / (float)Width;
            Vertices[index].Uv.Y = (float)z / (float)Height;
        }
    }
}

void CLandscapeHLSL::CreateIndexedData()
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
            Indices[index + 2] = Width * z + (x + 1);

            Indices[index + 3] = Width * z + (x + 1);
            Indices[index + 4] = Width * (z + 1) + x;
            Indices[index + 5] = Width * (z + 1) + (x + 1);

            index += 6;
        }
    }
}

void CLandscapeHLSL::CreateNormalVector()
{
    for (UINT i = 0; i < ICount / 3; i++)
    {
        UINT index0 = Indices[i * 3 + 0];
        UINT index1 = Indices[i * 3 + 1];
        UINT index2 = Indices[i * 3 + 2];

        FVertexTerrain& v0 = Vertices[index0];
        FVertexTerrain& v1 = Vertices[index1];
        FVertexTerrain& v2 = Vertices[index2];

        FVector e1 = v1.Position - v0.Position;
        FVector e2 = v2.Position - v0.Position;

        FVector normal = FVector::Cross(e1, e2);

        v0.Normal += normal;
        v1.Normal += normal;
        v2.Normal += normal;
    }

    for (UINT i = 0; i < VCount; i++)
        Vertices[i].Normal = FVector::Normalize(Vertices[i].Normal);
}

void CLandscapeHLSL::CreateBuffer()
{
    VBuffer = new CVertexBuffer(Vertices, VCount, sizeof(FVertexTerrain));
    IBuffer = new CIndexBuffer(Indices, ICount);
}
