#include "Framework.h"
#include "MeshRenderer.h"

CMeshRenderer::CMeshRenderer(CShader* InShader)
    :Shader(InShader)
{
}

CMeshRenderer::CMeshRenderer(CHLSLShader* InShader)
    :HLSLShader(InShader)
{
    FrameData.World = FMatrix::Identity;
    FrameData.View = FMatrix::Identity;
    FrameData.Projection = FMatrix::Identity;
    LightData.LightDirection = FVector(1.0f, 0.0f, 0.0f);
    
    FrameBuffer = new CConstantBuffer(&FrameData, sizeof(FFrameDesc));
    LightBuffer = new CConstantBuffer(&LightData, sizeof(FLightDesc));
}

CMeshRenderer::~CMeshRenderer()
{
    for (CModelMesh* mesh : Meshes)
        Delete(mesh);
    
    for (pair<string, CMaterial*> material : MaterialTable)
        Delete(material.second);
    
    Delete(FrameBuffer);
    Delete(LightBuffer);
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

void CMeshRenderer::RenderHLSL()
{
    FrameData.View = CContext::Get()->GetView();
    FrameData.Projection = CContext::Get()->GetProjection();
    LightData.LightDirection = CContext::Get()->GetLightDirection();
    
    FrameBuffer->Update();
    FrameBuffer->BindToVS(0);
    
    LightBuffer->Update();
    LightBuffer->BindToPS(2);
    
    HLSLShader->Render();
    
    for (CModelMesh* mesh : Meshes)
    {
        mesh->RenderHLSL();
    }
}

void CMeshRenderer::ReadMaterial(wstring InFile)
{
    InFile = L"../_Materials/" + InFile + L".material";
    
    ifstream stream;
    stream.open(InFile);
    assert(stream.is_open() && "Material file open failed");
    
    Json::Value root;
    stream >> root;
    stream.close();
    
    Json::Value::Members members = root.getMemberNames();
    for (string name : members)
    {
        CMaterial* material = new CMaterial(Shader);
        Json::Value value = root[name];
        
        if (value["00_Draw"].asBool() == false)
            material->OffDraw();
        else
            material->OnDraw();
        
        material->SetDiffuse(CString::FromColor(value["11_Diffuse"].asString()));
        
        string file;
        file = value["20_DiffuseMap"].asString();
        if (file.size() > 0)
            material->SetDiffuseMap(CString::ToWString(file), false);
        material->SetTiling(CString::FromVector2D(value["30_Tiling"].asString()));
        
        MaterialTable[name] = material;
    }
}

void CMeshRenderer::ReadMaterialHLSL(wstring InFile)
{
    InFile = L"../_Materials/" + InFile + L".material";
    
    ifstream stream;
    stream.open(InFile);
    assert(stream.is_open() && "Material file open failed");
    
    Json::Value root;
    stream >> root;
    stream.close();
    
    Json::Value::Members members = root.getMemberNames();
    for (string name : members)
    {
        CMaterial* material = new CMaterial(HLSLShader);
        Json::Value value = root[name];
        
        if (value["00_Draw"].asBool() == false)
            material->OffDraw();
        else
            material->OnDraw();
        
        material->SetDiffuse(CString::FromColor(value["11_Diffuse"].asString()));
        
        string file = value["20_DiffuseMap"].asString();
        if (file.size() > 0)
            material->SetDiffuseMap(CString::ToWString(file), false);
        
        material->SetTiling(CString::FromVector2D(value["30_Tiling"].asString()));
        
        MaterialTable[name] = material;
    }
}

void CMeshRenderer::ReadMesh(wstring InFile)
{
    InFile = L"../_Models/" + InFile +L".mesh";
    
    CBinaryReader* r = new CBinaryReader(InFile);
    
    UINT count = r->FromUINT();
    for (int i =0; i < count; i++)
    {
        CModelMesh* mesh = Shader != nullptr ? new CModelMesh(Shader) : new CModelMesh(HLSLShader);
        
        mesh->Name = r->FromString();
        mesh->MaterialName = r->FromString();
        
        map<string, CMaterial*>::iterator material = MaterialTable.find(mesh->MaterialName);
        if (material != MaterialTable.end())
            mesh->Material = material->second;
        
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

void CMeshRenderer::SetWorld(FMatrix InWorld)
{
    FrameData.World = InWorld;
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



















