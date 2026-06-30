#include "Framework.h"
#include "ModelMesh.h"

CModelMesh::CModelMesh(CShader* InShader)
    :Shader(InShader)
{
}

CModelMesh::~CModelMesh()
{
    DeleteArray(Vertices);
    DeleteArray(Indices);
    
    Delete(VBuffer);
    Delete(IBuffer);
}

void CModelMesh::Tick()
{
}

void CModelMesh::Render()
{
    VBuffer->Render();
    IBuffer->Render();
    
    CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    
    Shader->DrawIndexed(ICount);
}

void CModelMesh::CreateBuffer()
{
    VBuffer = new CVertexBuffer(Vertices, VCount, sizeof(FVertexModel));
    IBuffer = new CIndexBuffer(Indices, ICount);
}

FVector CModelMesh::GetSize()
{
    float x = abs(MinPoint.X) + abs(MaxPoint.X);
    float y = abs(MinPoint.Y) + abs(MaxPoint.Y);
    float z = abs(MinPoint.Z) + abs(MaxPoint.Z);
    
    return FVector(x,y,z);
}

FVector CModelMesh::GetExtent()
{
    return GetSize() * 0.5f;
}












