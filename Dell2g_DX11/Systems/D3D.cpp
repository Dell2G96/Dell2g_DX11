#include "Framework.h"
#include "D3D.h"

CD3D* CD3D::Instance = nullptr;

CD3D* CD3D::Get()
{
    return Instance;
}

void CD3D::Create(HWND InHandle, float InWidth, float InHeight)
{
    assert(Instance == nullptr);
    Instance = new CD3D(InHandle, InWidth, InHeight);
}

void CD3D::Destroy()
{
    Delete(Instance);
}

CD3D::CD3D(HWND InHandle, float InWidth, float InHeight)
    :Handle(InHandle) , Width(InWidth), Height(InHeight)
{
    CreateDevice();
    CreateSwapChain();
    CreateRTV();
    CreateViewport();
}

CD3D::~CD3D()
{
    Release(Device);
    Release(DeviceContext);
    Release(SwapChain);
    Release(RenderTargetView);
    Delete(Viewport);
}

void CD3D::CreateDevice()
{
    HRESULT hr = D3D11CreateDevice
    (
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &Device,
        nullptr,
        &DeviceContext
    );
    Check(hr);
}

void CD3D::CreateSwapChain()
{
    DXGI_SWAP_CHAIN_DESC desc;
    ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
    desc.BufferCount = 1;                                       // 백 버퍼 개수 , 1은 더블 버퍼링이며, 2 이상은 플립 모델에서 더 자주 사용
    desc.BufferDesc.Width = (UINT)Width;                        // 백 버퍼 가로 크기. 0을 넣으면 출력 창의 클라이언트 영역 크기를 사용할 수 있다
    desc.BufferDesc.Height = (UINT)Height;                      // 백 버퍼 세로 크기. 0을 넣으면 출력 창의 클라이언트 영역 크기를 사용할 수 있다
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;        // 픽셀 포맷입니다. RGBA 각 8비트 정규화 포맷이며, 일반적인 렌더 타겟 기본값으로 있다
    desc.BufferDesc.RefreshRate.Numerator = 0;                  // 화면 주사율 분자. 창 모드에서는 0으로 두면 DXGI가 적절한 값을 선택
    desc.BufferDesc.RefreshRate.Denominator = 0;                // 화면 주사율 분모. 창 모드에서는 0으로 두면 DXGI가 적절한 값을 선택
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;         // 백 버퍼 사용 목적. 렌더 타겟 출력용이며, 셰이더 입력 등은 다른 DXGI_USAGE 옵션을 추가
    desc.OutputWindow = Handle;                                 // 렌더링 결과를 표시할 Win32 창 핸들. 유효한 HWND가 필요.
    desc.SampleDesc.Count = 1;                                  // 멀티샘플링 샘플 개수. 1은 MSAA 미사용, 2/4/8 등은 장치 지원 여부 확인이 필요
    desc.Windowed = true;                                       // 창 모드 여부. true는 창 모드, false는 전체 화면 모드
    desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;                 // Present 후 백 버퍼 내용을 보존하지 않는 방식. 옵션으로 SEQUENTIAL, FLIP_SEQUENTIAL, FLIP_DISCARD 등이 있다.
    
    HRESULT hr = 0;
    
    IDXGIDevice* dxgiDevice =nullptr;
    hr = Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
    Check(hr);
    
    IDXGIAdapter* adapter =nullptr;
    hr = dxgiDevice->GetAdapter(&adapter);
    Check(hr);
    
    IDXGIFactory* factory = nullptr;
    hr = adapter->GetParent(__uuidof(IDXGIFactory), (void**)&factory);
    Check(hr);
    
    hr = factory->CreateSwapChain(Device, &desc, &SwapChain);
    Check(hr);
    
    Release(factory);
    Release(adapter);
    Release(dxgiDevice);
}

void CD3D::CreateRTV()
{
    HRESULT hr;
    
    ID3D11Texture2D* backBuffer;
    hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    Check(hr);
    
    hr = Device->CreateRenderTargetView(backBuffer,nullptr, &RenderTargetView);
    Check(hr);
    
    Release(backBuffer);
    
    DeviceContext->OMSetRenderTargets(1, &RenderTargetView, nullptr);
}

void CD3D::CreateViewport()
{
    Viewport = new D3D11_VIEWPORT();            // 뷰포트 설정을 담을 구조체를 만듦
    Viewport->TopLeftX = 0;                     // 화면을 그리기 시작할 X 위치. 0이면 백 버퍼의 왼쪽 끝에서 시작
    Viewport->TopLeftY = 0;                     // 화면을 그리기 시작할 Y 위치. 0이면 백 버퍼의 위쪽 끝에서 시작.
    Viewport->Width = Width;                    // 뷰포트 가로 크기. 보통 백 버퍼 가로 크기랑 맞춤
    Viewport->Height = Height;                  // 뷰포트 세로 크기. 보통 백 버퍼 세로 크기랑 맞춤.
    Viewport->MinDepth = 0;                     // 깊이 값의 최소 범위. 보통 0.0f를 사용
    Viewport->MaxDepth = 1;                     // 깊이 값의 최대 범위. 일반적으로는 1.0f 사용.
    
    DeviceContext->RSSetViewports(1, Viewport); // 래스터라이저 단계에 뷰포트를 등록하는 함수야. 첫 번째 값은 등록할 뷰포트 개수야.
}

void CD3D::Present()
{
    SwapChain->Present(0,0);
    #pragma region Present 함수 설명
    // IDXGISwapChain::Present(SyncInterval, Flags)는 CD3D::Present() 내부에서 Present(0, 0)으로 호출됩니다.
    // SyncInterval 옵션: 0은 즉시 출력, 1 이상은 수직 동기화 대기 프레임 수입니다.
    // Flags 옵션: 0은 기본 출력, DXGI_PRESENT_TEST, DXGI_PRESENT_DO_NOT_WAIT 같은 DXGI_PRESENT 플래그를 사용할 수 있습니다.
#pragma endregion 
    
    
}

void CD3D::ClearRenderTargetView(FColor InColor)
{
    DeviceContext->ClearRenderTargetView(RenderTargetView, InColor);
}
