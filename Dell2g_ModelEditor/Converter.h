#pragma once

class CConverter
{
public:
    CConverter();
    ~CConverter();

public:
    void ReadFile(wstring InFile, float InGlobalScale = 1.0f);
    
public:
    void ExportMesh(wstring InSaveFile);
    
private:
    void ReadMeshData();
    void WriteMeshData(wstring InSaveFile);
    
private:
    Assimp::Importer* Loader;
    
private:
    wstring File;
    
private:
    const aiScene* Scene;
    
private:
    vector<struct FMeshData*> Meshes;
    
};
