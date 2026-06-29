#pragma once
#include "Systems/IExecutable.h"

class CMain : public IExecutable
{
public:
    virtual void Initialize() override;
    virtual void Destroy() override;
    virtual void Tick() override;
    virtual void Render() override;
    
private:
    void Push(IExecutable* Inexecutable);
private:
    vector<IExecutable*> Executables;
};


