#include "PCH.h"
#include "Converter.h"
#include "Types.h"

CConverter::CConverter()
{
    
    Loader = new Assimp::Importer();
}

CConverter::~CConverter()
{
    Delete(Loader);
}

void CConverter::ReadFile(wstring InFile, float InGlobalScale)
{
    File = L"../_Assets/" + InFile;
    
    Loader->SetPropertyFloat(AI_CONFIG_GLOBAL_SCALE_FACTOR_KEY, InGlobalScale);
    
    string file = CString::ToString(File);
    Scene = Loader->ReadFile
    (
        file,
        aiProcess_ConvertToLeftHanded
        | aiProcess_Triangulate
        | aiProcess_GenUVCoords
        | aiProcess_GenNormals
        | aiProcess_CalcTangentSpace
        | aiProcess_GlobalScale
        | aiProcess_GenBoundingBoxes
        | aiProcess_JoinIdenticalVertices
        );
    
    assert(Scene != nullptr && "모델 정상 로드 안됨");
}

void CConverter::ExportMesh(wstring InSaveFile)
{
    ReadMeshData();
    
    InSaveFile = L"../_Models/" + InSaveFile + L".mesh";
    WriteMeshData(InSaveFile);
}

void CConverter::ReadMeshData()
{
    for (UINT i = 0; i < Scene->mNumMeshes; i++)
    {
        aiMesh* mesh = Scene->mMeshes[i];
        printf("--%s,%d,%d\n", mesh->mName.C_Str(), mesh->mNumVertices, mesh->mNumFaces);
        printf("Min : %+f,%+f,%+f\n", mesh->mAABB.mMin.x, mesh->mAABB.mMin.y, mesh->mAABB.mMin.z);
        printf("Max : %+f,%+f,%+f\n", mesh->mAABB.mMax.x, mesh->mAABB.mMax.y, mesh->mAABB.mMax.z);
        
        FMeshData* data = new FMeshData();
        data->Name = mesh->mName.C_Str();
        
        memcpy_s(&data->MinPoint, sizeof(FVector), &mesh->mAABB.mMin, sizeof(aiVector3D));
        
        memcpy_s(&data->MaxPoint, sizeof(FVector), &mesh->mAABB.mMax, sizeof(aiVector3D));
        for (UINT v = 0; v < mesh->mNumVertices; v++)
        {
            printf("0%2d : %+f, %+f, %+f\n" ,v, mesh->mVertices[v].x,mesh->mVertices[v].y, mesh->mVertices[v].z);
            
            FVertexModel vertex;
            memcpy_s(&vertex.Position, sizeof(FVector), &mesh->mVertices[v], sizeof(aiVector3D));
            memcpy_s(&vertex.Uv, sizeof(FVector2D), &mesh->mTextureCoords[0][v], sizeof(aiVector2D));
            memcpy_s(&vertex.Normal, sizeof(FVector), &mesh->mNormals[v], sizeof(aiVector3D));
            
            data->Vertices.push_back(vertex);
        }
        
        for (UINT f = 0; f < mesh->mNumFaces; f++)
        {
            aiFace& face = mesh->mFaces[f];
            
            for (UINT k =0; k < face.mNumIndices; k++)
            {
                printf("%d, %d, %d\n", f, k, face.mIndices[k]);
                data->Indices.push_back(face.mIndices[k]);
            }
        }
        Meshes.push_back(data);
    }
}

void CConverter::WriteMeshData(wstring InSaveFile)
{
    CPath::CreateFolder(CPath::GetDirectoryName(InSaveFile));
    
    CBinaryWriter* w = new CBinaryWriter(InSaveFile);
    
    w->ToUINT(Meshes.size());
    for (FMeshData* data : Meshes)
    {
        w->ToString(data->Name);
        
        w->ToVector(data->MinPoint);
        w->ToVector(data->MaxPoint);
        
        w->ToUINT(data->Vertices.size());
        w->ToByte(&data->Vertices[0], sizeof(FVertexModel) * data->Vertices.size());
        
        w->ToUINT(data->Indices.size());
        w->ToByte(&data->Indices[0], sizeof(UINT) * data->Indices.size());
        
        Delete(data);
    }
    w->Close();
    Delete(w);
    
}


























