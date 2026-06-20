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
    
private:
    steady_clock::time_point StartTime;
    steady_clock::time_point FpsTime;
    
    float RunningTime;
    UINT FrameCount = 0;
    UINT FPS = 0;
    
    
};
