#pragma once

class CTimer
{
private:
    friend class CWindow;
public:
    static CTimer* Get();
    
private:
    static void Create();
    static void Destroy();
    
private:
    static CTimer* Instance;
    
private:
    CTimer();
    ~CTimer();
    
    void Tick();
    
public:
    float GetRunningTime() { return RunningTime;}
    UINT GetFPS() {return FPS;}
    string GetCurrentTimeText();
public:
    float GetDeltaTime() { return DeltaTime;}
    
private:
    steady_clock::time_point StartTime;
    steady_clock::time_point FpsTime;
    steady_clock::time_point PrevFrameTime;
    
    float RunningTime;
    UINT FrameCount = 0;
    UINT FPS = 0;
    
    float DeltaTime = 0.f;
};
