#pragma once

class CGui
{
private:
    friend class CWindow;
    
public:
    static CGui* Get();
    
private:
    static void Create();
    static void Destroy();
    
private:
    static CGui* Instance;
    
private:
    CGui();
    ~CGui();
    
    void Tick();
    void Render();
    
private:
    LRESULT WndProc(HWND InHandle, UINT InMessage, WPARAM InwParam, LPARAM InlParam);
    
    
};
