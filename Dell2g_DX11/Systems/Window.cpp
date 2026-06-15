#include "Framework.h"
#include "Window.h"

CWindow::CWindow(wstring InAppName, float InWitdh, float InHeight, HINSTANCE InInstance)
    :AppName(InAppName) , Width(InWitdh), Height(InHeight), Instance(InInstance)
{
    CreateHandle();
}

CWindow::~CWindow()
{
    DestroyWindow(Handle);
    UnregisterClass(AppName.c_str(), Instance);
}

WPARAM CWindow::Run()
{
    MSG msg;
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0 , 0 , PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;
            
            DispatchMessage(&msg); 
        }
        else
        {
            // 게임 렌더링 처리
        }
    }
    return WPARAM();
}

void CWindow::CreateHandle()
{
    // 윈도우 클래스 등록
    {
        WNDCLASSEX wndClass;
        ZeroMemory(&wndClass, sizeof(WNDCLASSEX));
        
        wndClass.cbSize = sizeof(WNDCLASSEX);
        wndClass.style = CS_HREDRAW | CS_VREDRAW;
        wndClass.hCursor = LoadCursor(Instance, IDC_ARROW);
        wndClass.hbrBackground = (HBRUSH)(COLOR_GRAYTEXT + 1);
        wndClass.lpszClassName = AppName.c_str();
        wndClass.hInstance = Instance;
        wndClass.lpfnWndProc = WNDPROC;
        ATOM check = RegisterClassEx(&wndClass);
        assert(check != 0);
    }
    
    // 윈도우 핸들 생성
    {
        Handle = CreateWindowEx
        (0,
        AppName.c_str(),
        AppName.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        (int)Width,
        (int)Height,
        nullptr,
        nullptr,
        Instance,
        nullptr
        );
        assert(Handle != nullptr);
    }
    
    // 윈도우 보여주기
    {
        ShowWindow(Handle, SW_SHOWNORMAL);
        SetForegroundWindow(Handle);
        SetFocus(Handle);
        
        ShowCursor(true);
    }
}

LRESULT CWindow::WNDPROC(HWND InHandle, UINT InMessage, WPARAM InwParam, LPARAM InlParam)
{
    if (InMessage == WM_KEYDOWN)
    {
        if (InwParam == VK_ESCAPE)
        {
            MessageBox(InHandle , L"이 프로그램은 종료된다",  L"경고", MB_OK);   
            
            PostQuitMessage(0);
            return 0;
        }
    }
    
    if (InMessage == WM_CLOSE || InMessage == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(InHandle, InMessage, InwParam, InlParam);        
}
