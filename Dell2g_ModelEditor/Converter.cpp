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
        // printf("--%s,%d,%d\n", mesh->mName.C_Str(), mesh->mNumVertices, mesh->mNumFaces);
        // printf("Min : %+f,%+f,%+f\n", mesh->mAABB.mMin.x, mesh->mAABB.mMin.y, mesh->mAABB.mMin.z);
        // printf("Max : %+f,%+f,%+f\n", mesh->mAABB.mMax.x, mesh->mAABB.mMax.y, mesh->mAABB.mMax.z);
        
        FMeshData* data = new FMeshData();
        data->Name = mesh->mName.C_Str();
        
        UINT materialIndex = mesh->mMaterialIndex;
        aiMaterial* material = Scene->mMaterials[materialIndex];
        data->MaterialName = material->GetName().C_Str();
        
        memcpy_s(&data->MinPoint, sizeof(FVector), &mesh->mAABB.mMin, sizeof(aiVector3D));
        
        memcpy_s(&data->MaxPoint, sizeof(FVector), &mesh->mAABB.mMax, sizeof(aiVector3D));
        
        for (UINT v = 0; v < mesh->mNumVertices; v++)
        {
            // printf("0%2d : %+f, %+f, %+f\n" ,v, mesh->mVertices[v].x,mesh->mVertices[v].y, mesh->mVertices[v].z);
            
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
        w->ToString(data->MaterialName);
        
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

void CConverter::ExportMaterial(wstring InSaveFile, bool bOverwrite)
{
    InSaveFile = L"../_Materials/" + InSaveFile + L".material";
    
    if (bOverwrite)
    {
        if (CPath::ExistFile(InSaveFile))
            return;
    }
    ReadMaterialData();
    WriteMaterialData(InSaveFile);
}

void CConverter::ReadMaterialData()
{
    for (UINT i = 0; i < Scene->mNumMaterials; i++)
    {
        aiMaterial* material = Scene->mMaterials[i];
        FMaterialData* data = new FMaterialData();
        
        data->Name = material->GetName().C_Str();
        printf(" -- Material : %s\n" , data->Name.c_str());
        
        aiColor4D color;
        
        material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
        memcpy_s(&data->Diffuse, sizeof(FColor), &color, sizeof(aiColor4D));
        printf("DiffuseColor : %s\n", data->Diffuse.ToString().c_str());
        
        aiString textureFile;
        
        material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFile);
        data->DiffuseFile = textureFile.C_Str();
        if (data->DiffuseFile.empty())
            data->DiffuseFile = FindBlackPantherDiffuseTexture(data->Name);
        printf("DiffuseFile : %s\n", data->DiffuseFile.c_str());
        
        Materials.push_back(data);
    }
}

void CConverter::WriteMaterialData(wstring InSaveFile)
{
    string folderName = CString::ToString(CPath::GetDirectoryName(InSaveFile));
    CPath::CreateFolders(folderName);
    
    string modelName = CString::ToString(CPath::GetFileNameWithoutExtension(InSaveFile));
    string saveTextureFolder = "../_Models/" + modelName + "/";
    
    Json::Value root;
    for (FMaterialData* data : Materials)
    {
        Json::Value value;
        value["00_Draw"] = true;
        value["11_Diffuse"] = data->Diffuse.ToString();
        value["20_DiffuseMap"] = SaveTexture(saveTextureFolder, data->DiffuseFile);
        value["30_Tiling"] = FVector2D(1,1).ToString();
        
        root[data->Name.c_str()] = value;
        Delete(data);
    }
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "\t";
    
    ofstream stream;
    stream.open(InSaveFile);
    stream << Json::writeString(builder, root);
    stream.close();
}

string CConverter::SaveTexture(string InSaveFolder, string InFileName)
{
    if (InSaveFolder.length() > 0 == false)
        return "";
    if (InFileName.length() > 0 == false)
        return "";
    
    string fileName = CPath::GetFileName(InFileName);
    const aiTexture* texture = Scene->GetEmbeddedTexture(InFileName.c_str());
    
    if (texture != nullptr)
    {
        CPath::CreateFolders(InSaveFolder);
        
        wstring saveFile = CString::ToWString(InSaveFolder + fileName);
        CBinaryWriter* w = new CBinaryWriter(saveFile);
        w->ToByte(texture->pcData, texture->mWidth);
        w->Close();
        
        return InSaveFolder + fileName;
    }
    string directory = CPath::GetDirectoryName(CString::ToString(File));
    string origin = directory + InFileName;
    CString::Replace(&origin, "\\", "/");
    
    if (CPath::ExistFile(origin) == false)
        return "";
    
    string path = InSaveFolder + fileName;
    
    CPath::CreateFolders(InSaveFolder);
    CopyFileA(origin.c_str(), path.c_str(), FALSE);
    
    return path;
    
}

string CConverter::FindBlackPantherDiffuseTexture(string InMaterialName)
{
    string modelName = CPath::GetFileNameWithoutExtension(CString::ToString(File));
    if (modelName != "BlackPanther")
        return "";
    
    string fileName = "";
    
    if (InMaterialName == "MI_1026300_Body")
        fileName = "T_1026300_Boby_D.png";
    else if (InMaterialName == "MI_1026300_Equip_01")
        fileName = "T_1026300_Equip_01_D.png";
    else if (InMaterialName == "MI_1026300_Equip_02")
        fileName = "T_1026300_Equip_02_D.png";
    else if (InMaterialName == "MI_1026300_Eyes")
        fileName = "T_1026300_Eyeball_D.png";
    else if (InMaterialName == "MI_1026300_Head")
        fileName = "T_1026300_Head_D.png";
    
    if (fileName.empty())
        return "";
    
    string directory = CPath::GetDirectoryName(CString::ToString(File));
    string origin = directory + fileName;
    if (CPath::ExistFile(origin) == false)
        return "";
    
    return fileName;
}


























