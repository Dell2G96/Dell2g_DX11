#include "Framework.h"
#include "VertexBuffer.h"


CVertexBuffer::CVertexBuffer(void* InData, UINT InCount, UINT InStride)
    :Data(InData), Count(InCount), Stride(InStride)
{
    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
    desc.ByteWidth = Stride * Count;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    
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

void CVertexBuffer::Render()
{
    UINT offset = 0;
    CD3D::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1 , &Buffer, &Stride, &offset);
}
