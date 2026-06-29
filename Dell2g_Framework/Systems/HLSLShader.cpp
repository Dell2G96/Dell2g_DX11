#include "Framework.h"
#include "HLSLShader.h"

#include <vector>
#include <d3d11shader.h>   // ID3D11ShaderReflection (입력 레이아웃 자동 생성용)

CHLSLShader::CHLSLShader(wstring InFile, string InVSEntry, string InPSEntry)
    : File(L"../_Shaders/" + InFile), VSEntry(InVSEntry), PSEntry(InPSEntry)
{
    // 1) 정점/픽셀 셰이더를 각각 따로 컴파일한다. (technique/pass 대신)
    CompileShader(VSEntry, "vs_5_0", &VsBlob);
    CompileShader(PSEntry, "ps_5_0", &PsBlob);

    // 2) 컴파일된 바이트코드로 셰이더 객체 생성
    ID3D11Device* device = CD3D::Get()->GetDevice();

    HRESULT hr = device->CreateVertexShader(
        VsBlob->GetBufferPointer(), VsBlob->GetBufferSize(), nullptr, &VertexShader);
    Check(hr);

    hr = device->CreatePixelShader(
        PsBlob->GetBufferPointer(), PsBlob->GetBufferSize(), nullptr, &PixelShader);
    Check(hr);

    // 3) 정점 셰이더의 입력 시그니처를 분석해 입력 레이아웃 자동 생성
    CreateInputLayout();
}

CHLSLShader::~CHLSLShader()
{
    Release(InputLayout);
    Release(VertexShader);
    Release(PixelShader);
    Release(VsBlob);
    Release(PsBlob);
}

void CHLSLShader::CompileShader(string InEntry, string InTarget, ID3DBlob** OutBlob)
{
    ID3DBlob* error = nullptr;

    // ROW_MAJOR: 엔진의 FMatrix가 행 우선(row-major) 메모리 배치이므로,
    // 셰이더도 같은 규칙으로 컴파일해야 행렬을 그대로 memcpy 해서 올릴 수 있다.
    UINT flag = D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
#ifdef _DEBUG
    flag |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    HRESULT hr = D3DCompileFromFile(
        File.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        InEntry.c_str(),     // 엔트리 함수 이름 (예: "VS", "PS_Address")
        InTarget.c_str(),    // 타겟 프로필 (예: "vs_5_0", "ps_5_0")
        flag, 0,
        OutBlob, &error);

    if (FAILED(hr))
    {
        if (error != nullptr)
        {
            string msg = (const char*)error->GetBufferPointer();
            MessageBoxA(nullptr, msg.c_str(), "HLSL Compile Error", MB_OK);
        }
        assert(false && "HLSL shader compile failed");
    }

    Release(error);
}

void CHLSLShader::CreateInputLayout()
{
    // 정점 셰이더 바이트코드를 "리플렉션(reflection)"으로 들여다보면
    // VS가 어떤 입력(Position, Uv ...)을 기대하는지 알 수 있다.
    // 그 정보를 그대로 D3D11_INPUT_ELEMENT_DESC 목록으로 옮겨 자동 생성한다.
    ID3D11ShaderReflection* reflection = nullptr;
    HRESULT hr = D3DReflect(
        VsBlob->GetBufferPointer(), VsBlob->GetBufferSize(),
        IID_ID3D11ShaderReflection, (void**)&reflection);
    Check(hr);

    D3D11_SHADER_DESC shaderDesc;
    reflection->GetDesc(&shaderDesc);

    std::vector<D3D11_INPUT_ELEMENT_DESC> elements;
    for (UINT i = 0; i < shaderDesc.InputParameters; i++)
    {
        D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
        reflection->GetInputParameterDesc(i, &paramDesc);

        string name = paramDesc.SemanticName;
        string upper = name;
        transform(upper.begin(), upper.end(), upper.begin(), ::toupper);

        // SV_ 로 시작하는 시스템 시맨틱(SV_Position 등)은 입력 레이아웃에서 제외
        if (upper.compare(0, 3, "SV_") == 0)
            continue;

        D3D11_INPUT_ELEMENT_DESC element;
        element.SemanticName = paramDesc.SemanticName;
        element.SemanticIndex = paramDesc.SemanticIndex;
        element.InputSlot = 0;
        element.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT; // 오프셋 자동 누적
        element.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        element.InstanceDataStepRate = 0;

        // 컴포넌트 개수(Mask)와 타입(ComponentType)으로 DXGI 포맷 결정
        // Mask: 1=1개(x), 3=2개(xy), 7=3개(xyz), 15=4개(xyzw)
        if (paramDesc.Mask == 1)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)       element.Format = DXGI_FORMAT_R32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  element.Format = DXGI_FORMAT_R32_SINT;
            else                                                                element.Format = DXGI_FORMAT_R32_FLOAT;
        }
        else if (paramDesc.Mask <= 3)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)       element.Format = DXGI_FORMAT_R32G32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  element.Format = DXGI_FORMAT_R32G32_SINT;
            else                                                                element.Format = DXGI_FORMAT_R32G32_FLOAT;
        }
        else if (paramDesc.Mask <= 7)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)       element.Format = DXGI_FORMAT_R32G32B32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  element.Format = DXGI_FORMAT_R32G32B32_SINT;
            else                                                                element.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        }
        else // Mask <= 15
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)       element.Format = DXGI_FORMAT_R32G32B32A32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  element.Format = DXGI_FORMAT_R32G32B32A32_SINT;
            else                                                                element.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        }

        // 셰이더는 Position을 float4로 받지만, 실제 정점 데이터(FVertexTexture)는
        // FVector(float3)이다. 그래서 POSITION만 강제로 RGB32F(float3)로 맞춘다.
        if (upper == "POSITION")
            element.Format = DXGI_FORMAT_R32G32B32_FLOAT;

        elements.push_back(element);
    }

    hr = CD3D::Get()->GetDevice()->CreateInputLayout(
        elements.data(), (UINT)elements.size(),
        VsBlob->GetBufferPointer(), VsBlob->GetBufferSize(),
        &InputLayout);
    Check(hr);

    Release(reflection);
}

void CHLSLShader::Render()
{
    ID3D11DeviceContext* deviceContext = CD3D::Get()->GetDeviceContext();

    deviceContext->IASetInputLayout(InputLayout);
    deviceContext->VSSetShader(VertexShader, nullptr, 0);
    deviceContext->PSSetShader(PixelShader, nullptr, 0);
}
