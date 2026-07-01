#pragma once

class CConverter
{
public:
    CConverter();
    ~CConverter();
    
/////////////////////////////////////////////////////////////////////////
/// Mesh
/////////////////////////////////////////////////////////////////////////
public:
    void ReadFile(wstring InFile, float InGlobalScale = 1.0f);
    
public:
    void ExportMesh(wstring InSaveFile);
    
private:
    void ReadMeshData();
    void WriteMeshData(wstring InSaveFile);

/////////////////////////////////////////////////////////////////////////
///Material
/////////////////////////////////////////////////////////////////////////
public:
    void ExportMaterial(wstring InSaveFile, bool bOverwrite = false); 
private:
    void ReadMaterialData();
    void WriteMaterialData(wstring InSaveFile);
    string SaveTexture(string InSaveFolder, string InFileName);
    string FindBlackPantherDiffuseTexture(string InMaterialName);
    
private:
    Assimp::Importer* Loader;
    
private:
    wstring File;
    
private:
    const aiScene* Scene;
    
private:
    vector<struct FMaterialData*> Materials;
    vector<struct FMeshData*> Meshes;
    
};
