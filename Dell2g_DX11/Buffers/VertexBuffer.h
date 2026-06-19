#pragma once

class CVertexBuffer
{
public:
    CVertexBuffer(void* InData, UINT InCount, UINT InStride);
    ~CVertexBuffer();
    
    void Render();
    
private:
    ID3D11Buffer* Buffer;
    
    void* Data;
    UINT Count;
    UINT Stride;
    
};
