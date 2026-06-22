#include "Framework.h"
#include "Mouse.h"

CMouse* CMouse::Instance = nullptr;

CMouse* CMouse::Get()
{
    return Instance;
}

void CMouse::Create()
{
    assert(Instance == nullptr);

    Instance = new CMouse();
}

void CMouse::Destroy()
{
    assert(Instance != nullptr);

    Delete(Instance);
}

CMouse::CMouse()
{
	
}

CMouse::~CMouse()
{

}

void CMouse::Tick()
{
    Previous.X = Current.X;
    Previous.Y = Current.Y;
    
    Current.X = Position.X;
    Current.Y = Position.Y;
    
    Delta = Current - Previous;
    Current.Z = Previous.Z;
}

bool CMouse::Down(int InType)
{
    bool bCheck = true;
    bCheck &= GetButtonState(InType);
    bCheck &= ButtonState[InType] == false;
    
    if (bCheck)
    {
        ButtonState.set(InType, true);
        
        return true;
    }
    ButtonState.set(InType, false);
    return false;
}

bool CMouse::Down(EMouseButton InType)
{
    return Down((int)InType);
}

bool CMouse::Up(int InType)
{
    if (GetButtonState(InType))
    {
        ButtonState.set(InType, true);
        return false;
    }
    if (ButtonState[InType] == true)
    {
        ButtonState.set(InType, false);
        return true;
    }
    return false;
}

bool CMouse::Up(EMouseButton InType)
{
    return Up((int)InType);
}

bool CMouse::Press(int InType)
{
    return GetButtonState(InType);
}

bool CMouse::Press(EMouseButton InType)
{
    return Press((int)InType);
}

bool CMouse::GetButtonState(int InValue)
{
    EMouseButton button =(EMouseButton)InValue;
    
    int value = 0;
    switch (button)
    {
    case EMouseButton::Left: value = VK_LBUTTON; break;      //0x01
    case EMouseButton::Right: value = VK_RBUTTON; break;     //0x02
    case EMouseButton::Middle: value = VK_MBUTTON; break;    //0x04
    }
    return GetAsyncKeyState(value) & 0x8000;
}

void CMouse::WndProc(UINT InMessage, WPARAM InwParam, LPARAM InlParma)
{
    if (InMessage == WM_MOUSEMOVE)
    {
        Position.X = (float)LOWORD(InlParma);
        Position.Y = (float)HIWORD(InlParma);
    }
    if (InMessage == WM_MOUSEWHEEL)
    {
        Previous.Z = Current.Z;
        Current.Z = (float)((short)HIWORD(InlParma));
    }
    
}
