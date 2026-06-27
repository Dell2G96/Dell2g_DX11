#pragma once

class CVertexBuffer
{
public:
    CVertexBuffer(void* InData, UINT InCount, UINT InStride, bool InToVRAM = false, bool InFromVRAM = false);
    ~CVertexBuffer();
    
    operator ID3D11Buffer* ();
    
    void Update();
    void Map();
    void Render();
    
private:
    bool bToVRAM;
    bool bFromVRAM;
    
    ID3D11Buffer* Buffer;
    
    void* Data;
    UINT Count;
    UINT Stride;
    
};
