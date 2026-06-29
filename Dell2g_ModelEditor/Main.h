#pragma once
#include "Systems/IExecutable.h"

class CMain : public IExecutable
{
public:
    virtual void Initialize() override;
private:
    void Cube();
};


