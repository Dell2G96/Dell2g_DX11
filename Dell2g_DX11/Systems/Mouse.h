#pragma once

enum class EMouseButton
{
    Left = 0, Right, Middle, Max,
    
};

class CMouse
{
private:
    friend class CWindow;

public:
    static CMouse* Get();

private:
    static void Create();
    static void Destroy();

private:
    static CMouse* Instance;

private:
    CMouse();
    ~CMouse();

public:
    void Tick();

public:
    bool Down(int InType);
    bool Down(EMouseButton InType);
    
    bool Up(int InType);
    bool Up(EMouseButton InType);
    
    bool Press(int InType);
    bool Press(EMouseButton InType);
private:
    enum class EMouseButtonState
    {
        None = 0, Down, Up, Press, Max,
    };
private:
    bitset<(UINT)EMouseButton::Max> ButtonState;
    
    FVector Position = FVector::Zero;
    
    FVector Current = FVector::Zero;
    FVector Previous = FVector::Zero;
    FVector Delta = FVector::Zero;

private:
    bool GetButtonState(int InValue);
    
public:
    void WndProc(UINT InMessage, WPARAM InwParam, LPARAM InlParma);
    
public:
    FVector GetPosition() {return Position;}
    FVector GetDelta() {return Delta;}
    
};











