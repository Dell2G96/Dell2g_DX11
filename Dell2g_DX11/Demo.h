#pragma once

#include "Systems/IExecutable.h"

class Demo : public IExecutable
{
public:
    void Initialize() override;
    void Destroy() override;
    void Tick() override; 
    void Render() override;
    
private:
    void Tick_Cross();
    void Tick_Cross2();
    void Tick_Cross3();
    


private:
    CLine3D* Line3D;
    CLandscape* Landscape;
    
private:
    float Rotation;
    float LineLength = 1.0f;
    
private:
    FVector Position = FVector(1,0,0);
    
    
};
