#include "Framework.h"
#include "Timer.h"

CTimer* CTimer::Instance = nullptr;

CTimer* CTimer::Get()
{
    return Instance;
}

void CTimer::Create()
{
    assert(Instance == nullptr);
    Instance = new CTimer();
}

void CTimer::Destroy()
{
    assert(Instance != nullptr);
    Delete(Instance);
}

CTimer::CTimer()
{
    StartTime = steady_clock::now();
    FpsTime = steady_clock::now();
}

CTimer::~CTimer()
{
}

void CTimer::Tick()
{
    steady_clock::time_point current = steady_clock::now();
    duration<float> temp = current - StartTime;
    RunningTime = temp.count();
    
    FrameCount++;
    
    seconds sec = duration_cast<seconds>(current - FpsTime);
    if (sec.count() >= 1)
    {
        FPS = FrameCount;
        FrameCount = 0;
        FpsTime = current;
    }
}
