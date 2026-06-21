#include "Framework.h"
#include "Context.h"

CContext* CContext::Instance =nullptr;

CContext* CContext::Get()
{
    return Instance;
}

void CContext::Create()
{
    assert(Instance == nullptr);

    Instance = new CContext();
}

void CContext::Destroy()
{
    assert(Instance != nullptr);

    Delete(Instance);
}


CContext::CContext()
{
    View = FMatrix::Identity;
    
    float width = CD3D::Get()->GetWidth();
    float height = CD3D::Get()->GetHeight();
    float aspect = width / height;
    
    float fov = FMath::Pi * 0.25f;
    Projection = FMatrix::CreatePerspectiveFieldOfView(fov, aspect, 0.1f, 1000.f);
    
    Viewport = new D3D11_VIEWPORT();    // 뷰포트 설정을 담을 구조체를 만듦
    Viewport->TopLeftX = 0;             // 화면을 그리기 시작할 X 위치. 0이면 백 버퍼의 왼쪽 끝에서 시작
    Viewport->TopLeftY = 0;             // 화면을 그리기 시작할 Y 위치. 0이면 백 버퍼의 위쪽 끝에서 시작.
    Viewport->Width = width;            // 뷰포트 가로 크기. 보통 백 버퍼 가로 크기랑 맞춤
    Viewport->Height = height;          // 뷰포트 세로 크기. 보통 백 버퍼 세로 크기랑 맞춤.
    Viewport->MinDepth = 0;             // 깊이 값의 최소 범위. 보통 0.0f를 사용
    Viewport->MaxDepth = 1;             // 깊이 값의 최대 범위. 일반적으로는 1.0f 사용.

    
}

CContext::~CContext()
{
    Delete(Viewport);

}

void CContext::Tick()
{
    if (CKeyboard::Get()->Press('E'))
        CameraPosition.Y += CameraMoveSpeed * CTimer::Get()->GetDeltaTime();
    else if (CKeyboard::Get()->Press('Q'))
        CameraPosition.Y -= CameraMoveSpeed * CTimer::Get()->GetDeltaTime();

    if (CKeyboard::Get()->Press('D'))
        CameraPosition.X += CameraMoveSpeed * CTimer::Get()->GetDeltaTime();
    else if (CKeyboard::Get()->Press('A'))
        CameraPosition.X -= CameraMoveSpeed * CTimer::Get()->GetDeltaTime();

    if (CKeyboard::Get()->Press('W'))
        CameraPosition.Z += CameraMoveSpeed * CTimer::Get()->GetDeltaTime();
    else if (CKeyboard::Get()->Press('S'))
        CameraPosition.Z -= CameraMoveSpeed * CTimer::Get()->GetDeltaTime();
    
    View = FMatrix::CreateLookAt(CameraPosition, CameraPosition + FVector::Forward, FVector::Up);
}

void CContext::Render()
{
    CD3D::Get()->GetDeviceContext()->RSSetViewports(1, Viewport);
    
#pragma region 시간 , FPS
    const float x = 5.0f;
    const float y = 5.0f;
    const float lineHeight = 20.f;
    
    // 오늘 날짜 현재 시간 출력
    CGui::Get()->RenderText(x,y,1,1,1,CTimer::Get()->GetCurrentTimeText());
    
    // FPS 출력
    string fps = "";
    fps += "FPS : ";
    fps += to_string(CTimer::Get()->GetFPS());
    CGui::Get()->RenderText(x,y+lineHeight,1,1,1,fps);
    
    // 경과 시간 출력
    string time = "";
    time += "경과시간 : ";
    time += to_string(CTimer::Get()->GetRunningTime());
    CGui::Get()->RenderText(x,y+lineHeight * 2.0f,1,1,1,time);
    
    char value[256];
    sprintf_s(value, 256, "VIew Position : %3.2f, %3.2f, %3.2f", CameraPosition.X, CameraPosition.Y, CameraPosition.Z);
    CGui::Get()->RenderText(5,y+lineHeight * 3.0f,1,1,1, value);
    
#pragma endregion 
    
}

void CContext::ResizeScreen(float InWidth, float InHeight)
{
    float aspect = InWidth / InHeight;
    
    float fov = FMath:: Pi * 0.25f;
    Projection = FMatrix::CreatePerspectiveFieldOfView(fov, aspect, 0.1f, 1000.f);
    
    Viewport = new D3D11_VIEWPORT();
    Viewport->TopLeftX = 0;
    Viewport->TopLeftY = 0;
    Viewport->Width = InWidth;
    Viewport->Height = InHeight;
    Viewport->MinDepth = 0;
    Viewport->MaxDepth = 0;
    
}
