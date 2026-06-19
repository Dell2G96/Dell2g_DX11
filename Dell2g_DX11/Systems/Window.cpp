#include "Framework.h"
#include "Window.h"

#include "IExecutable.h"

CWindow::CWindow(wstring InAppName, float InWitdh, float InHeight, HINSTANCE InInstance)
    :AppName(InAppName) , Width(InWitdh), Height(InHeight), Instance(InInstance)
{
    CreateHandle();
 
    CD3D::Create
    (
        Handle, 
        //DirectX 11이 렌더링 결과를 출력할 Win32 창 핸들(HWND)입니다. 
        //스왑 체인의 OutputWindow로 사용되며, 반드시 유효한 창 핸들이어야 합니다.
        Width,  
        //백 버퍼와 뷰포트의 가로 크기입니다. 
        //현재 창의 가로 크기를 넘기며, 전체 화면이나 리사이즈를 지원할 때는 변경된 크기를 다시 반영
        Height  
        //백 버퍼와 뷰포트의 세로 크기.
        //현재 창의 세로 크기를 넘기며, 전체 화면이나 리사이즈를 지원할 때는 변경된 크기를 다시 반영해야 합니다.
    );
}

CWindow::~CWindow()
{
    CD3D::Destroy();
    
    DestroyWindow(Handle);
    UnregisterClass(AppName.c_str(), Instance);
}

WPARAM CWindow::Run(class IExecutable* InExecutable)
{
    InExecutable->Initialize();
    
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
           MainRender(InExecutable);
        }
    }
    InExecutable->Destroy();
    return WPARAM();
}

void CWindow::MainRender(class IExecutable* InExecutable)
{
    InExecutable->Tick();
    
    // 게임 렌더링 처리
   
    CD3D::Get()->ClearRenderTargetView();      //렌더 타겟을 지울 색상입니다. 
    {
        InExecutable->Render();
    }
    CD3D::Get()->Present();                         
    // Present(): Window.cpp에서는 매개변수가 없는 CD3D 래퍼 함수입니다.
    
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
