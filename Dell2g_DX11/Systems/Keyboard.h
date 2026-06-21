#pragma once

class CKeyboard
{
private:
    friend class CWindow;
    
public:
    static CKeyboard* Get();
    
private:
    static void Create();
    static void Destroy();
    
private:
    static CKeyboard* Instance;
    
private:
    CKeyboard();
    ~CKeyboard();
public:
    bool Press(int InKey);
    bool Down(int InKey);
    bool Up(int InKey);
    
private:
    bitset<MAX_KEY_COUNT> KeyState;
    
};
