#pragma once

class CLine3D
{
public:
    CLine3D(UINT InMaxCount = 10);
    ~CLine3D();
    
    void Tick();
    void Render();
    
public:
    void SetWorld(const FMatrix& InMatrix);
    
public:
    void Add(const FVector& InStart, const FVector& InEnd, const FColor& InColor);
    void Add(const FVector& InStart, const FColor& InStartColor ,const FVector& InEnd, const FColor& InEndColor);
    
private:
    CShader* Shader;
    
    FVertexColor* Vertices;
    CVertexBuffer* VBuffer;
    
private:
    FMatrix World;
    
private:
    UINT MaxCount;
    UINT DrawCount = 0;
    
};
