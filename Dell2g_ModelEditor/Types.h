#pragma once
#include "PCH.h"

struct FMeshData
{
    string Name;
    string MaterialName;
    
    FVector MinPoint;
    FVector MaxPoint;
    
    vector<FVertexModel> Vertices;
    vector<UINT> Indices;
};

struct FMaterialData
{
    string Name;
    
    FColor Diffuse;
    string DiffuseFile;
};