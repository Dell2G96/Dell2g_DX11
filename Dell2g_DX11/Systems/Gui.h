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

    // 월드 좌표 버전: 3D 도형 위에 텍스트를 띄울 때 사용한다.
    // 내부에서 화면 좌표로 변환하며, 카메라 뒤에 있으면 자동으로 그리지 않는다.
    void RenderText(const FVector& InWorld, float r, float g, float b, const string& InText);
    
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
