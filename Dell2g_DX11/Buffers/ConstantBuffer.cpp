#include "Framework.h"
#include "ConstantBuffer.h"

CConstantBuffer::CConstantBuffer(void* InData, UINT InDataSize)
    : Data(InData), DataSize(InDataSize)
{
    // 상수 버퍼는 16바이트(float4) 단위로 정렬되어야 한다.
    // CPU 구조체 크기가 16의 배수가 아니면 GPU에 올라간 값이 어긋난다.
    assert(DataSize > 0 && DataSize % 16 == 0 && "Constant buffer size must be a multiple of 16 bytes");

    // buffer desc 설정
    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
    desc.ByteWidth = DataSize;
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    // 매 프레임 값이 바뀌므로 DYNAMIC + CPU 쓰기 허용 (Map/Unmap으로 갱신)
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CPU가 버퍼의 데이터를 수정 가능 

    // 초기 데이터 없이 빈 버퍼만 생성 (값은 Update()에서 채운다)
    HRESULT hr = CD3D::Get()->GetDevice()->CreateBuffer(&desc, nullptr, &Buffer);
    Check(hr);
}

CConstantBuffer::~CConstantBuffer()
{
    Release(Buffer);
}

void CConstantBuffer::Update()
{
    ID3D11DeviceContext* deviceContext = CD3D::Get()->GetDeviceContext();

    // GPU 버퍼를 잠그고(Map) CPU 데이터를 통째로 복사한 뒤 다시 푼다(Unmap).
    // WRITE_DISCARD: 이전 내용은 버리고 새로 덮어쓴다 (DYNAMIC 버퍼의 표준 갱신 방식).
    D3D11_MAPPED_SUBRESOURCE subResource;
    deviceContext->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
    {
        memcpy(subResource.pData, Data, DataSize);
    }
    deviceContext->Unmap(Buffer, 0);
}

void CConstantBuffer::BindToVS(UINT InSlot)
{
    CD3D::Get()->GetDeviceContext()->VSSetConstantBuffers(InSlot, 1, &Buffer);
}

void CConstantBuffer::BindToPS(UINT InSlot)
{
    CD3D::Get()->GetDeviceContext()->PSSetConstantBuffers(InSlot, 1, &Buffer);
}
