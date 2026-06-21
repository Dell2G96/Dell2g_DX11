#pragma once

class CIndexBuffer
{
public:
    CIndexBuffer(UINT* InData, UINT InCount);
    ~CIndexBuffer();
    
    operator ID3D11Buffer* ();
    
    void Render();
    
private:
    ID3D11Buffer* Buffer;
    
    UINT* Data;
    UINT Count;
    
};
