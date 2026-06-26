#include "Framework.h"
#include "Main.h"

#include "Systems/Window.h"

#include "Demo.h"
#include "Demo2.h"
#include "Demo-HLSL.h"
#include "Demo2-HLSL.h"



void CMain::Initialize()
{
    
    //Push(new Demo);
    //Push(new CDemo2);
    Push(new Demo_hlsl);
    //Push(new Demo2_hlsl);
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
