#include "Framework.h"
#include "VertexBuffer.h"


CVertexBuffer::CVertexBuffer(void* InData, UINT InCount, UINT InStride, bool InToVRAM, bool InFromVRAM )
    :Data(InData), Count(InCount), Stride(InStride), bToVRAM(InToVRAM), bFromVRAM(InFromVRAM)
{
    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
    desc.ByteWidth = Stride * Count;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    
    if (bToVRAM == false && bFromVRAM ==false)
    {
        desc.Usage = D3D11_USAGE_IMMUTABLE;
    }
    else if (bToVRAM == true && bFromVRAM ==false)
    {
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    }
    else if (bToVRAM == false && bFromVRAM ==true)
    {
        desc.Usage = D3D11_USAGE_DYNAMIC;
    }
    else //(bToVRAM == true && bFromVRAM == true)
    {
        desc.Usage = D3D11_USAGE_STAGING;
        
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    }
    
    D3D11_SUBRESOURCE_DATA subResource;
    ZeroMemory(&subResource, sizeof(D3D11_SUBRESOURCE_DATA));
    subResource.pSysMem = InData;
    
    HRESULT hr = CD3D::Get()->GetDevice()->CreateBuffer(&desc, &subResource, &Buffer);
    Check(hr);
}

CVertexBuffer::~CVertexBuffer()
{
    Release(Buffer);
}

CVertexBuffer::operator ID3D11Buffer*()
{
    return Buffer;
}

void CVertexBuffer::Update()
{
    // default
    assert(bToVRAM == false&& bFromVRAM == true);
    
    CD3D::Get()->GetDeviceContext()->UpdateSubresource(Buffer, 0, nullptr, Data, 0, 0);
}

void CVertexBuffer::Map()
{
    // Dynamic
    assert(bToVRAM == true && bFromVRAM == false);
    D3D11_MAPPED_SUBRESOURCE subResource;
    
    HRESULT hr = CD3D::Get()->GetDeviceContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
    Check(hr);
    {
        memcpy_s(subResource.pData, Stride * Count, Data, Stride* Count);
    }
    CD3D::Get()->GetDeviceContext()->Unmap(Buffer, 0);
}

void CVertexBuffer::Render()
{
    UINT offset = 0;
    CD3D::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1 , &Buffer, &Stride, &offset);
}
