#pragma once

class CWindow
{
public:
    CWindow(wstring InAppName, float InWitdh, float InHeight, HINSTANCE InInstance);
    ~CWindow();
    
    WPARAM Run(class IExecutable* InExecutable);
    
private:
    void MainRender(class IExecutable* InExecutable);
    
private:
    void CreateHandle();


private:
    static LRESULT CALLBACK WNDPROC (HWND InHandle, UINT InMessage, WPARAM InwParam, LPARAM InlParam);
private:
    HINSTANCE Instance;
    HWND Handle;
    
    wstring AppName;
    float Width;
    float Height;
    
};
