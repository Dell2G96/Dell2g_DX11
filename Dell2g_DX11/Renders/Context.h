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
