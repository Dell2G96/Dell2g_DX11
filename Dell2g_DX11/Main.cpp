#include "Framework.h"
#include "Main.h"

#include "Systems/Window.h"

#include "Demo.h"
#include "Demo2.h"
#include "Demo3.h"
#include "DemoHLSL.h"



void CMain::Initialize()
{
    // 순수 HLSL 파이프라인 예제. 기존 Effects11 Demo와 화면이 겹치지 않도록
    // 아래 두 줄을 잠시 주석 처리했다. (원복하려면 주석만 풀면 됨)
//    Push(new Demo);
//    Push(new CDemo2);
    Push(new CDemo3);
    Push(new CDemoHLSL);
}

void CMain::Destroy()
{
    for (IExecutable* executable : Executables)
    {
        executable->Destroy();
        Delete(executable);
    }
    
}

void CMain::Tick()
{
    for (IExecutable* executable : Executables)
        executable->Tick();
}

void CMain::Render()
{
    for (IExecutable* executable : Executables)
    {
        executable->Render();
    }
    
}

void CMain::Push(IExecutable* Inexecutable)
{
    Executables.push_back(Inexecutable);

    Inexecutable->Initialize();
}


///////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE InInstance, HINSTANCE InPreInstance, LPSTR InParam, int InCommand)
{
    CWindow* window = new CWindow(L"Dell2g_Game", 1024 , 768 , InInstance);
    
    CMain* main = new CMain();
    WPARAM result = window->Run(main);
    
    Delete(main);    
    Delete(window);
    
    return result;
}
