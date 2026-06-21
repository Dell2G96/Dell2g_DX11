#pragma once

#include "Systems/IExecutable.h"

class Demo : public IExecutable
{
public:
    void Initialize() override;
    void Destroy() override;
    void Tick() override; 
    void Render() override;
    
#pragma region Keyboard UI
// private:
//     string Text = "";
#pragma endregion 

private:
    UINT Technique = 0;
    UINT Pass = 0;
    FColor Color = FColor::Red;
    
private:
    CShader* Shader;
    
    FVector Vertices[6];
    CVertexBuffer* VBuffer;
private:
    FMatrix World;
    FMatrix View;
    FMatrix Projection;
    
};
