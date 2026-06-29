#include "Framework.h"
#include "Keyboard.h"

CKeyboard* CKeyboard::Instance = nullptr;

CKeyboard* CKeyboard::Get()
{
    return Instance;
}

void CKeyboard::Create()
{
    assert(Instance == nullptr);
    Instance = new CKeyboard();
}

void CKeyboard::Destroy()
{
    assert(Instance != nullptr);
    Delete(Instance);
}

CKeyboard::CKeyboard()
{
    KeyState.reset();
}

CKeyboard::~CKeyboard()
{
    
}

bool CKeyboard::Press(int InKey)
{
    if (GetAsyncKeyState(InKey) & 0x8000)
        return true;
    
    return false;
}

bool CKeyboard::Down(int InKey)
{
    bool bCheck = true;
    bCheck &= (GetAsyncKeyState(InKey) & 0x8000) !=0;
    bCheck &= KeyState[InKey] == false;
    
    if (bCheck)
    {
        KeyState.set(InKey,true);
        return true;
    }
    KeyState.set(InKey, false);
    return false;
}

bool CKeyboard::Up(int InKey)
{
    if (GetAsyncKeyState(InKey) & 0x8000)
    {
        KeyState.set(InKey, true);

        return false;
    }

    if (KeyState[InKey] == true)
    {
        KeyState.set(InKey, false);

        return true;
    }

    return false;
}








