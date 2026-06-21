#pragma once

class CD3D
{
private:
    friend class CWindow;
public:
    static CD3D* Get();
    
private:
    static void Create(HWND InHandle, float InWidth, float InHeight);
    static void Destroy();
    
private:
    static CD3D* Instance;
    
private:
    CD3D(HWND InHandle, float InWidth, float InHeight);
    ~CD3D();
    
private:
    void CreateDevice(); 
    void CreateSwapChain(); 
    void CreateRTV(); 
    
    void ResizeScreen(float InWidth, float InHeight);

    void Present();
    
    
public:
    void ClearRenderTargetView(FColor InColor = FColor::Black);
    
public:
    HWND GetHandle() {return Handle;}
    ID3D11Device* GetDevice(){return Device;}
    ID3D11DeviceContext* GetDeviceContext(){return DeviceContext;}
    
    float GetWidth() {return Width;}
    float GetHeight() {return Height;}
public:
    HWND Handle;
    float Width, Height;
    
    ID3D11Device* Device;
    ID3D11DeviceContext* DeviceContext;
    
    IDXGISwapChain* SwapChain;
    
    ID3D11RenderTargetView* RenderTargetView;
    D3D11_VIEWPORT* Viewport;
    
    
};
