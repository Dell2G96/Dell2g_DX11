#include "Framework.h"
#include "MeshRenderer.h"

CMeshRenderer::CMeshRenderer(CShader* InShader)
    :Shader(InShader)
{
}

CMeshRenderer::~CMeshRenderer()
{
}

void CMeshRenderer::Tick()
{
    for (CModelMesh* mesh : Meshes)
        mesh->Tick();
}

void CMeshRenderer::Render()
{
    FMatrix view = CContext::Get()->GetView();
    Shader->AsMatrix("View")->SetMatrix(view);
    
    FMatrix projection = CContext::Get()->GetProjection();
    Shader->AsMatrix("Projection")->SetMatrix(projection);
    
    FVector lightDirection = CContext::Get()->GetLightDirection();
    Shader->AsVector("LightDirection")->SetFloatVector(lightDirection);
    
    for (CModelMesh* mesh : Meshes)
    {
        mesh->Render();
    }
    
    
}

void CMeshRenderer::ReadMesh(wstring InFile)
{
    InFile = L"../_Models/" + InFile +L".mesh";
    
    CBinaryReader* r = new CBinaryReader(InFile);
    
    UINT count = r->FromUINT();
    for (int i =0; i < count; i++)
    {
        CModelMesh* mesh = new CModelMesh(Shader);
        
        mesh->Name = r->FromString();
        
        mesh->MinPoint = r->FromVector();
        mesh->MaxPoint = r->FromVector();
        
        mesh->VCount = r->FromUINT();
        mesh->Vertices = new FVertexModel[mesh->VCount];
        r->FromByte((void**)&mesh->Vertices, sizeof(FVertexModel) * mesh->VCount);
        
        mesh->ICount = r-> FromUINT();
        mesh->Indices = new UINT[mesh->ICount];
        r->FromByte((void**)&mesh->Indices, sizeof
            (UINT)* mesh->ICount);
        
        mesh->CreateBuffer();
        
        Meshes.push_back(mesh);
    }
    r->Close();
    Delete(r);
}

FVector CMeshRenderer::GetSize(UINT InIndex)
{
    assert(InIndex < Meshes.size());
    return Meshes[InIndex]->GetSize();
    
}

FVector CMeshRenderer::GetExtent(UINT InIndex)
{
    assert(InIndex < Meshes.size());
    return Meshes[InIndex]->GetExtent();
}



















