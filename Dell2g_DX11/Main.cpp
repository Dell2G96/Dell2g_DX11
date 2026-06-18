#include "Framework.h"
#include "Systems/Window.h"

int WINAPI WinMain(HINSTANCE InInstance, HINSTANCE InPreInstance, LPSTR InParam, int InCommand)
{
    CWindow* window = new CWindow(L"Dell2g_Game", 1024 , 768 , InInstance);
    
    WPARAM result = window->Run();
    
    // delete window;
    // window = nullptr;
    
    Delete(window);

    
    return 0;
}
