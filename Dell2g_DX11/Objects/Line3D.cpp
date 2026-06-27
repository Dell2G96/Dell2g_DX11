#include "Framework.h"
#include "Line3D.h"

CLine3D::CLine3D(UINT InMaxCount)
    :MaxCount(InMaxCount)
{
    Shader = new CShader(L"16_Line3D.fx");
    World = FMatrix::Identity;
    
    Vertices = new FVertexColor[MaxCount * 2];
    ZeroMemory(Vertices, sizeof(FVertexColor) * MaxCount * 2);
    
    VBuffer = new CVertexBuffer(Vertices, MaxCount * 2, sizeof(FVertexColor), true, false);
    
}

CLine3D::~CLine3D()
{
    Delete(Shader);
    
    DeleteArray(Vertices);
    Delete(VBuffer);
    
}
void CLine3D::Tick()
{
    Shader->AsMatrix("World")->SetMatrix(World);
    
    FMatrix view = CContext::Get()->GetView();
    Shader->AsMatrix("View")->SetMatrix(view);
    
    FMatrix projection = CContext::Get()->GetProjection();
    Shader->AsMatrix("Projection")->SetMatrix(projection);
}

void CLine3D::Render()
{
    if (DrawCount > 1 == false)
        return;
    VBuffer->Map();
    VBuffer->Render();
    CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);
    
    Shader->Draw(DrawCount);
    
    DrawCount = 0;
    ZeroMemory(Vertices, sizeof(FVertexColor) * MaxCount * 2);
    
    
}

void CLine3D::SetWorld(const FMatrix& InMatrix)
{
    World = InMatrix;
}

void CLine3D::Add(const FVector& InStart, const FVector& InEnd, const FColor& InColor)
{
    Add(InStart, InColor, InEnd, InColor);
}

void CLine3D::Add(const FVector& InStart, const FColor& InStartColor, const FVector& InEnd, const FColor& InEndColor)
{
    assert(DrawCount < MaxCount * 2);
    
    Vertices[DrawCount].Color = InStartColor;
    Vertices[DrawCount++].Position = InStart;
    
    Vertices[DrawCount].Color = InEndColor;
    Vertices[DrawCount++].Position = InEnd;
}
