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
    const FMatrix& GetProjection(){return Projection;}
    
private:
    float CameraMoveSpeed = 5.f;
    float CameraRotaionSpeed = 200.f;
    //FVector CameraPosition = FVector(0, 2, -10);
    
private:
    CCamera* Camera;
    
    FMatrix Projection;
    D3D11_VIEWPORT* Viewport;
    
    
    
    
};
