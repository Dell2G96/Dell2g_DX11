#pragma once

class CContext
{
private:
    friend class CWindow;
    
public:
    static CContext* Get();
    
private:
    static void Create();
    static void Destroy();
    
private:
    static CContext* Instance;
    
private:
    CContext();
    ~CContext();
    
    void Tick();
    void Render();
    
    void ResizeScreen(float InWidth, float InHeight);
    
public:
    const FMatrix& GetView(){return Camera->GetViewMatrix();}
    const FMatrix& GetProjection() {return Projection;}

public:
    // 월드 좌표 한 점을 화면 픽셀 좌표(ImGui RenderText용)로 변환한다.
    // OutBehind 가 true 면 카메라 뒤에 있는 점이므로 그리지 말 것.
    FVector2D WorldToScreen(const FVector& InWorld, bool& OutBehind);
    
public:
    CCamera* GetCamera() {return Camera;}

public:
    void SetCameraMoveSpeed(float InValue) { CameraMoveSpeed = InValue;}
    void SetCameraRotaionSpeed(float InValue) { CameraRotationSpeed = InValue;}
private:
    float CameraMoveSpeed = 5.f;
    float CameraRotationSpeed = 200.f;
    
private:
    CCamera* Camera;
    
    FMatrix Projection;
    D3D11_VIEWPORT* Viewport;
    
    
    
    
};
