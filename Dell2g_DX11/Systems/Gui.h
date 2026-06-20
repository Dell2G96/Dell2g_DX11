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
    
public:
    void RenderText(float x, float y , float r , float g , float b, const string& content);
    void RenderText(float x, float y , float r , float g , float b, float a, const string& content);
    
private:
    struct FGuiText
    {
        ImVec2 Position;
        ImColor Color;
        string Content;
    };
private:
    vector<FGuiText> Contents;
    
    
};
