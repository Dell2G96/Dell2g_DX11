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
    CGui::Create();
}

CWindow::~CWindow()
{
    CGui::Destroy();
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
    return msg.wParam;
}

void CWindow::MainRender(class IExecutable* InExecutable)
{
    CGui::Get()->Tick();
    InExecutable->Tick();
    
    // 게임 렌더링 처리
    CD3D::Get()->ClearRenderTargetView();      //렌더 타겟을 지울 색상입니다. 
    {
        InExecutable->Render();
    }
    CGui::Get()->Render();
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
        AppName.c_str(),                        // 클래스 네임
        AppName.c_str(),            
        WS_OVERLAPPEDWINDOW,            
        CW_USEDEFAULT,                        // 윈도우 기본 설정          
        CW_USEDEFAULT,                      
        (int)Width,                           // 창 넓이  
        (int)Height,                          // 창 높이     
        nullptr,                              // 부모 창
        nullptr,                              //
        Instance,                             // 프로그램 식별자  
        nullptr                               // 추가 옵션 
        );
        
        assert(Handle != nullptr);
        
        // 윈도우 보여주기
        {
            RECT rect = {0, 0, (LONG)Width, (LONG)Height};
            
            UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)Width) / 2;
            UINT centerY = (GetSystemMetrics(SM_CXSCREEN) - (UINT)Height) / 2;
            
            AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
            MoveWindow(Handle, centerX, centerY, rect.right - rect.left, rect.bottom - rect.top, TRUE);
        }
    }
    
    {
        ShowWindow(Handle, SW_SHOWNORMAL);
        SetForegroundWindow(Handle);                // 맨 앞에 뜰 수 있도록
        SetFocus(Handle);                           // 입력이 될 수 있도록

        ShowCursor(true);                           // 커서가 보이도록
        
    }
    
   
}

LRESULT CWindow::WNDPROC(HWND InHandle, UINT InMessage, WPARAM InwParam, LPARAM InlParam)
{
    if (CGui::Get()->WndProc(InHandle, InMessage, InwParam, InlParam))
        return true;
    
    if (InMessage == WM_SIZE)
    {
        float width = (float)LOWORD(InlParam);
        float height = (float)HIWORD(InlParam);
        
        if (CD3D::Get() != nullptr)
            CD3D::Get()->ResizeScreen(width, height);
    }
    
    
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
