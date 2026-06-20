#include "Framework.h"
#include "Main.h"

#include "Buffers/VertexBuffer.h"
#include "Systems/Window.h"

void CMain::Initialize()
{
    Shader = new CShader(L"05_Rasterizer.fx");
    
    Vertices[0] = FVector(0, 0,0);
    Vertices[1] = FVector(1, 0,0);
    
    VBuffer = new CVertexBuffer(Vertices, 2, sizeof(FVector));
}

void CMain::Destroy()
{
    Delete(VBuffer);
    Delete(Shader);
    
}

void CMain::Tick()
{
    
}

void CMain::Render()
{
    VBuffer->Render();
    CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINELIST);
    Shader->Draw(2);
    
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
