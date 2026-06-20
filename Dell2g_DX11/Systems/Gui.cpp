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
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

LRESULT CGui::WndProc(HWND InHandle, UINT InMessage, WPARAM InwParam, LPARAM InlParam)
{
    if (ImGui::GetCurrentContext() == nullptr)
        return 0;
    return ImGui_ImplWin32_WndProcHandler(InHandle, InMessage, InwParam, InlParam);
}
