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
    PrevFrameTime = steady_clock::now();
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
    duration<float> temp2 = current - PrevFrameTime;
    DeltaTime = temp2.count();
    PrevFrameTime = current;
}

string CTimer::GetCurrentTimeText()
{
    time_t now = time(nullptr);
    tm localTime ={};
    localtime_s(&localTime, &now);
    
    stringstream currentTime;
    currentTime << put_time(&localTime, "%y-%m-%d : %H:%M:%S");
    
    return currentTime.str();
}
