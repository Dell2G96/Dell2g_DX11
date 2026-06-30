#pragma once
#include "Systems/IExecutable.h"

class CMain : public IExecutable
{
public:
    virtual void Initialize() override;
private:
    void ReadModel(wstring Name);
    void Arrow();
    void Capsule();
    void Cone();
    void Cube();
    void Cylinder();
    void Sphere();
    void Torus();
};


