#include "Framework.h"
#include "Demo2.h"

void CDemo2::Initialize()
{
    Shader = new CShader(L"10_GridRendering.fx");

    // 버텍스 버퍼
    VCount = Width * Height;
    Vertices = new FVector[VCount];

    for (UINT z = 0; z < Height; z++)
    {
        for (UINT x = 0; x < Width; x++)
        {
            UINT index = Width * z + x;

            Vertices[index] = FVector((float)x, 0.0f, (float)z);
        }
    }

    VBuffer = new CVertexBuffer(Vertices, VCount, sizeof(FVector));

    // 인덱스 버퍼 
    ICount = (Width - 1) * (Height - 1) * 6;
    Indices = new UINT[ICount];

    UINT index = 0;
    for (UINT y = 0; y < Height - 1; y++)
    {
        for (UINT x = 0; x < Width - 1; x++)
        {
            Indices[index + 0] = Width * y + x;
            Indices[index + 1] = Width * (y + 1) + x;
            Indices[index + 2] = Width * y + x + 1;

            Indices[index + 3] = Width * y + x + 1;
            Indices[index + 4] = Width * (y + 1) + x;
            Indices[index + 5] = Width * (y + 1) + x + 1;

            index += 6;
        }
    }

    IBuffer = new CIndexBuffer(Indices, ICount);


    World = FMatrix::Identity; //단위 행렬
}

void CDemo2::Destroy()
{
    Delete(Shader);

    DeleteArray(Vertices);
    Delete(VBuffer);

    DeleteArray(Indices);
    Delete(IBuffer);
}

void CDemo2::Tick()
{
    
}

void CDemo2::Render()
{
    Shader->AsMatrix("World")->SetMatrix(World);

    FMatrix view = CContext::Get()->GetView();
    Shader->AsMatrix("View")->SetMatrix(view);

    FMatrix projection = CContext::Get()->GetProjection();
    Shader->AsMatrix("Projection")->SetMatrix(projection);

    Shader->AsVector("Color")->SetFloatVector(Color);

    VBuffer->Render();
    IBuffer->Render();

    CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Shader->SetTechniqueByName("T_Wireframe");
    Shader->SetPassNumber(0);
    Shader->DrawIndexed(ICount);
}
