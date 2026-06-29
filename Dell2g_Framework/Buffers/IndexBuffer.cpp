#include "Framework.h"
#include "IndexBuffer.h"

CIndexBuffer::CIndexBuffer(UINT* InData, UINT InCount)
    :Data(InData), Count(InCount)
{
    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
    desc.ByteWidth = sizeof(UINT) * Count;
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    desc.Usage = D3D11_USAGE_IMMUTABLE;
    
    D3D11_SUBRESOURCE_DATA subResource;
    ZeroMemory(&subResource, sizeof(D3D11_SUBRESOURCE_DATA));
    subResource.pSysMem = InData;
    
    HRESULT hr = CD3D::Get()->GetDevice()->CreateBuffer(&desc, &subResource, &Buffer);
    Check(hr);
}

CIndexBuffer::~CIndexBuffer()
{
    Release(Buffer);
}

CIndexBuffer::operator ID3D11Buffer*()
{
    return Buffer;
}

void CIndexBuffer::Render()
{
    CD3D::Get()->GetDeviceContext()->IASetIndexBuffer(Buffer, DXGI_FORMAT_R32_UINT, 0);
}
