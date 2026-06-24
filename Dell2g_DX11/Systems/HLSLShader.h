#pragma once

// =============================================================================
// CHLSLShader
//  - Effects11 기반 CShader(technique/pass/Effect)를 대체하는 "순수 HLSL용" 셰이더.
//  - .hlsl 파일에서 정점 셰이더(VS)와 픽셀 셰이더(PS) 엔트리 포인트를 각각 컴파일하고,
//    ID3D11VertexShader / ID3D11PixelShader 와 입력 레이아웃(InputLayout)을 만든다.
//  - technique/pass 개념이 없으므로, "어떤 PS를 쓸지"는 생성 시 엔트리 이름으로 결정한다.
//    (예: PS_Address 용 셰이더 1개, PS_Filter 용 셰이더 1개를 따로 생성)
//  - 자세한 설명: HLSL_Pipeline_Guide.md 참고.
// =============================================================================
class CHLSLShader
{
public:
    // InFile : _Shaders 폴더 기준 파일명 (예: L"12_Sampling.hlsl")
    // InVSEntry / InPSEntry : 컴파일할 엔트리 함수 이름
    CHLSLShader(wstring InFile, string InVSEntry = "VS", string InPSEntry = "PS");
    ~CHLSLShader();

public:
    // 입력 레이아웃 + 정점 셰이더 + 픽셀 셰이더를 파이프라인에 바인딩한다.
    // (Draw 직전에 호출 — Effects11의 pass->Apply() 역할)
    void Render();

private:
    void CompileShader(string InEntry, string InTarget, ID3DBlob** OutBlob);
    void CreateInputLayout();   // 정점 셰이더 바이트코드를 분석(reflection)해 자동 생성

private:
    wstring File;
    string  VSEntry;
    string  PSEntry;

private:
    ID3DBlob* VsBlob = nullptr; // 컴파일된 VS 바이트코드 (InputLayout 생성에 필요해 보관)
    ID3DBlob* PsBlob = nullptr;

    ID3D11VertexShader* VertexShader = nullptr;
    ID3D11PixelShader*  PixelShader = nullptr;
    ID3D11InputLayout*  InputLayout = nullptr;
};
