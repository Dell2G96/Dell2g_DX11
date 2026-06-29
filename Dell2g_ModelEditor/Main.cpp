#include "PCH.h"
#include "Main.h"

#include "Systems/Window.h"
#include "Converter.h"


void CMain::Initialize()
{
    Cube();
    MessageBox(CD3D::Get()->GetHandle(), L"변환 완료", L"Message", MB_OK);       
}

void CMain::Cube()
{
    CConverter* converter = new CConverter();
    converter->ReadFile(L"Cube.fbx");
    converter->ExportMesh(L"Cube");
    Delete(converter);
}


///////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE InInstance, HINSTANCE InPreInstance, LPSTR InParam, int InCommand)
{
    CWindow* window = new CWindow(L"Dell2g_Game", 1620 , 800 , InInstance);
    
    CMain* main = new CMain();
    WPARAM result = window->Run(main, false);
    
    Delete(main);    
    Delete(window);
    
    return result;
}
