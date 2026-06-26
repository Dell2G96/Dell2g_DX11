#pragma once

#include "Systems/IExecutable.h"

class Demo_hlsl : public IExecutable
{
public:
    void Initialize() override;
    void Destroy() override;
    void Tick() override;
    void Render() override;

private:
    CLandscapeHLSL* Landscape = nullptr;
};
