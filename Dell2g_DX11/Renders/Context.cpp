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
    Camera = new CCamera();
    
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
    Delete(Camera);
    Delete(Viewport);

}

void CContext::Tick()
{
    if (CMouse::Get()->Press(EMouseButton::Right))
    {
        FVector position = Camera->GetPosition();
    
        // 카메라 앞, 뒤 
        if (CKeyboard::Get()->Press('W'))
            position = position + Camera->GetForward() * CameraMoveSpeed * CTimer::Get()->GetDeltaTime();
        else if(CKeyboard::Get()->Press('S'))
            position = position - Camera->GetForward() * CameraMoveSpeed * CTimer::Get()->GetDeltaTime();
    
        // 카메라 좌,우
        if (CKeyboard::Get()->Press('D'))
            position = position + Camera->GetRight() * CameraMoveSpeed * CTimer::Get()->GetDeltaTime();
        else if(CKeyboard::Get()->Press('A'))
            position = position - Camera->GetRight() * CameraMoveSpeed * CTimer::Get()->GetDeltaTime();
    
        // 카메라 업, 다운
        if (CKeyboard::Get()->Press('E'))
            position = position + Camera->GetUp() * CameraMoveSpeed * CTimer::Get()->GetDeltaTime();
        else if (CKeyboard::Get()->Press('Q'))
            position = position - Camera->GetUp() * CameraMoveSpeed * CTimer::Get()->GetDeltaTime();
        
        Camera->SetPosition(position);
    
        FVector delta = CMouse::Get()->GetDelta();
    
        FVector rotation = Camera->GetRotation();
        rotation.X = rotation.X + delta.Y * CameraRotationSpeed * CTimer::Get()->GetDeltaTime();
        rotation.Y = rotation.Y + delta.X * CameraRotationSpeed * CTimer::Get()->GetDeltaTime();
        rotation.Z = 0.0f;
    
        Camera->SetRotation(rotation);
    }
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
    const FVector& rotation = Camera->GetRotation();
    sprintf_s(value, 256, "VIew Rotation : %3.2f, %3.2f, %3.2f", Camera->GetRotation().X, Camera->GetRotation().Y, Camera->GetRotation().Z);
    CGui::Get()->RenderText(x,y+lineHeight * 3.0f,1,1,1, value);
    
    sprintf_s(value, 256, "VIew Position : %3.2f, %3.2f, %3.2f", Camera->GetPosition().X, Camera->GetPosition().Y, Camera->GetPosition().Z);
    CGui::Get()->RenderText(x,y+lineHeight * 4.0f,1,1,1, value);
    
#pragma endregion 
    
}

FVector2D CContext::WorldToScreen(const FVector& InWorld, bool& OutBehind)
{
    OutBehind = false;

    // View * Projection (호출측이 이미 월드 좌표를 넘기므로 World 는 곱하지 않음)
    FMatrix vp = GetView() * GetProjection();

    // 동차 좌표의 w 성분을 직접 계산해서 카메라 뒤 여부를 판정한다.
    // (TransformCoord 는 w 로 나눈 뒤 w 부호를 버리므로 뒤 판정에 쓸 수 없음)
    float w = (vp.M14 * InWorld.X) + (vp.M24 * InWorld.Y) + (vp.M34 * InWorld.Z) + vp.M44;
    if (w <= 0.0f)
    {
        OutBehind = true;
        return FVector2D(0.0f, 0.0f);
    }

    // TransformCoord = 변환 + 원근분할(w 나누기) → NDC(-1 ~ +1)
    FVector ndc = FVector::TransformCoord(InWorld, vp);

    float width = CD3D::Get()->GetWidth();
    float height = CD3D::Get()->GetHeight();

    // NDC(-1~+1) → 화면 픽셀. Y 는 위아래가 뒤집힌다.
    float screenX = (ndc.X * 0.5f + 0.5f) * width;
    float screenY = (1.0f - (ndc.Y * 0.5f + 0.5f)) * height;

    return FVector2D(screenX, screenY);
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
