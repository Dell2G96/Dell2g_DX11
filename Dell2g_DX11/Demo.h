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
    CLine3D* Line3D;
    CLandscape* Landscape;
    
private:
    float Rotation;
    float LineLength = 1.0f;
    
    
};
