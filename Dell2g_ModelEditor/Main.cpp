#include "PCH.h"
#include "Main.h"

#include "Systems/Window.h"
#include "Converter.h"


void CMain::Initialize()
{
    // Arrow();
    // Capsule();
    // Cone();
    // Cube();
    // Cylinder();
    // Sphere();
    // Torus(); 
    ReadModel(L"Ittan_momen");
    
    MessageBox(CD3D::Get()->GetHandle(), L"변환 완료", L"Message", MB_OK);       
}

void CMain::ReadModel(wstring InName)
{
    CConverter* converter = new CConverter();
    wstring s = InName + L"/";
    converter->ReadFile(s + InName +L".fbx");
    converter->ExportMaterial(InName);
    converter->ExportMesh(InName);
    Delete(converter);
}

#pragma region 기본 모델 불러오기
void CMain::Arrow()
{
    CConverter* converter = new CConverter();
    converter->ReadFile(L"Arrow.fbx");
    converter->ExportMesh(L"Arrow");
    Delete(converter);
}

void CMain::Capsule()
{
    CConverter* converter = new CConverter();
    converter->ReadFile(L"Capsule.fbx");
    converter->ExportMesh(L"Capsule");
    Delete(converter);
}

void CMain::Cone()
{
    CConverter* converter = new CConverter();
    converter->ReadFile(L"Cone.fbx");
    converter->ExportMesh(L"Cone");
    Delete(converter);
}

void CMain::Cube()
{
    CConverter* converter = new CConverter();
    converter->ReadFile(L"Cube.fbx");
    converter->ExportMesh(L"Cube");
    Delete(converter);
}

void CMain::Cylinder()
{
    CConverter* converter = new CConverter();
    converter->ReadFile(L"Cylinder.fbx");
    converter->ExportMesh(L"Cylinder");
    Delete(converter);
}

void CMain::Sphere()
{
    CConverter* converter = new CConverter();
    converter->ReadFile(L"Sphere.fbx");
    converter->ExportMesh(L"Sphere");
    Delete(converter);
}

void CMain::Torus()
{
    CConverter* converter = new CConverter();
    converter->ReadFile(L"Torus.fbx");
    converter->ExportMesh(L"Torus");
    Delete(converter);
}
#pragma endregion 

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
