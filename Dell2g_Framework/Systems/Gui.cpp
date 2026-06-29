#include "Framework.h"
#include "Gui.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND InHandle, UINT InMessage, WPARAM InwParam, LPARAM InlParam);

CGui* CGui::Instance = nullptr;

CGui* CGui::Get()
{
    return Instance;
}

void CGui::Create()
{
    assert(Instance == nullptr);
    Instance = new CGui();
}

void CGui::Destroy()
{
    assert(Instance != nullptr);
    Delete(Instance);
}

CGui::CGui()
{
    IMGUI_CHECKVERSION();
    
    ImGui::CreateContext();
    // 한글 폰트 추가
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF(
        "C:\\Windows\\Fonts\\malgun.ttf",
        16.f,
        nullptr,
        io.Fonts->GetGlyphRangesKorean());
    
    
    ImGui_ImplWin32_Init(CD3D::Get()->GetHandle());
    ImGui_ImplDX11_Init(CD3D::Get()->GetDevice(), CD3D::Get()->GetDeviceContext());
}

CGui::~CGui()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void CGui::Tick()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void CGui::Render()
{
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowBgAlpha(0.0f);
    
    ImGuiWindowFlags flags = 0;
    flags |= ImGuiWindowFlags_NoTitleBar;
    flags |= ImGuiWindowFlags_NoResize;
    flags |= ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoScrollbar;
    flags |= ImGuiWindowFlags_NoScrollWithMouse;
    flags |= ImGuiWindowFlags_NoCollapse;
    flags |= ImGuiWindowFlags_NoSavedSettings;
    flags |= ImGuiWindowFlags_NoInputs;
    flags |= ImGuiWindowFlags_NoFocusOnAppearing;
    flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    flags |= ImGuiWindowFlags_NoNavFocus;
    
    ImGui::Begin("TextWindow", nullptr, flags);
    {
        for (FGuiText& content :Contents)
            ImGui::GetWindowDrawList()->AddText(content.Position, content.Color, content.Content.c_str());
        
        Contents.clear();
    }
    ImGui::End();
    
    
    
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

LRESULT CGui::WndProc(HWND InHandle, UINT InMessage, WPARAM InwParam, LPARAM InlParam)
{
    if (ImGui::GetCurrentContext() == nullptr)
        return 0;
    return ImGui_ImplWin32_WndProcHandler(InHandle, InMessage, InwParam, InlParam);
}

void CGui::RenderText(float x, float y, float r, float g, float b, const string& content)
{
    RenderText(x, y, r, g, b, 1.f, content);
}

void CGui::RenderText(float x, float y, float r, float g, float b, float a, const string& content)
{
    FGuiText text;
    text.Position = ImVec2(x, y);
    text.Color = ImColor(r,g,b,a);
    text.Content = content;

    Contents.push_back(text);
}

void CGui::RenderText(const FVector& InWorld, float r, float g, float b, const string& InText)
{
    bool behind = false;
    FVector2D screen = CContext::Get()->WorldToScreen(InWorld, behind);
    if (behind) return;                 // 카메라 뒤면 그리지 않음

    RenderText(screen.X, screen.Y, r, g, b, InText);
}
