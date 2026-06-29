#pragma once

// =============================================================================
// CConstantBuffer
//  - Effects11의 AsMatrix(...)->SetMatrix(...) / AsScalar(...)->SetInt(...) 같은
//    "전역 변수 자동 관리"를 대체하는 순수 HLSL용 상수 버퍼 래퍼.
//  - CPU 쪽 구조체(Data)를 GPU의 cbuffer로 복사(Update)하고,
//    원하는 셰이더 단계/슬롯에 바인딩(BindToVS / BindToPS)한다.
//  - 자세한 설명: HLSL_Pipeline_Guide.md 참고.
// =============================================================================
class CConstantBuffer
{
public:
    
    
    CConstantBuffer(
        void* InData,       // InData     : CPU 측 데이터 구조체의 주소 (예: &WorldData)
        UINT InDataSize);   // InDataSize : 그 구조체의 바이트 크기 (반드시 16의 배수여야 함)
    CConstantBuffer(CShader* InShader, string InParamName, void* InData, UINT InDataSize);
    ~CConstantBuffer();

public:
    // CPU의 Data 내용을 GPU 버퍼로 복사한다. (값이 바뀔 때마다 호출)
    void Update();
    void Render();

    // 이 상수 버퍼를 정점 셰이더 / 픽셀 셰이더의 bN 슬롯에 연결한다.
    void BindToVS(UINT InSlot);
    void BindToPS(UINT InSlot);

private:
    ID3D11Buffer* Buffer = nullptr;
    ID3DX11EffectConstantBuffer* sBuffer;
    
    CShader* Shader;
    void* Data;     // CPU 측 원본 데이터 주소 (소유하지 않음)
    UINT  DataSize; // 바이트 크기
};
