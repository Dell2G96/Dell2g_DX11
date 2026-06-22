#pragma once

class CCamera
{
public:
    CCamera();
    ~CCamera();

private:
    void CalcRotationMatrix();
    void CalcViewMatrix();
    
public:
    const FVector& GetPosition();
    void SetPosition(float InX, float InY, float InZ);
    void SetPosition(const FVector& InValue);
    
public:
    FVector GetRotation();
    void SetRotation(float InX, float InY, float InZ);
    void SetRotation(const FVector& InValue);
    
public:
    const FVector& GetForward() {return Forward;}
    const FVector& GetUp(){return Up;}
    const FVector& GetRight(){return Right; }
    
public:
    const FMatrix& GetViewMatrix() {return ViewMatrix;}
    
private:
    FVector Position = FVector::Zero;
    FVector Rotation = FVector::Zero;
    
private:
    FVector Forward = FVector::Forward;
    FVector Up = FVector::Up;
    FVector Right = FVector::Right;
    
private:
    FMatrix ViewMatrix;
    FMatrix RotationMatrix;
    
};
