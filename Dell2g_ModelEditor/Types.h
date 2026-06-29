#pragma once
#include "PCH.h"

struct FMeshData
{
    string Name;
    
    FVector MinPoint;
    FVector MaxPoint;
    
    vector<FVertexModel> Vertices;
    vector<UINT> Indices;
};