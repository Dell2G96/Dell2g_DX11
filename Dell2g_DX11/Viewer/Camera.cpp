#include "Framework.h"
#include "Camera.h"

CCamera::CCamera()
{
    ViewMatrix = FMatrix::Identity;
    RotationMatrix = FMatrix::Identity;
    
    CalcRotationMatrix();
    CalcViewMatrix();
}

CCamera::~CCamera()
{
}

void CCamera::CalcRotationMatrix()
{
    FMatrix x, y, z;
    x = FMatrix::CreateRotationX(Rotation.X);
    y = FMatrix::CreateRotationY(Rotation.Y);
    z = FMatrix::CreateRotationZ(Rotation.Z);
    
    RotationMatrix = x * y * z;
    
    Forward = FVector::TransformNormal(FVector::Forward, RotationMatrix);
    Up = FVector::TransformNormal(FVector::Up, RotationMatrix);
    Right = FVector::TransformNormal(FVector::Right, RotationMatrix);
}

void CCamera::CalcViewMatrix()
{
    ViewMatrix = FMatrix::CreateLookAt(Position, Position + Forward, Up);
}

const FVector& CCamera::GetPosition()
{
    return Position;
}

void CCamera::SetPosition(float InX, float InY, float InZ)
{
    SetPosition(FVector(InX, InY, InZ));
}

void CCamera::SetPosition(const FVector& InValue)
{
    Position = InValue;
    
    CalcViewMatrix();
}

FVector CCamera::GetRotation()
{
    FVector r;
    r.X = FMath::ToDegrees(Rotation.X);
    r.Y = FMath::ToDegrees(Rotation.Y);
    r.Z = FMath::ToDegrees(Rotation.Z);
    
    return r;
}

void CCamera::SetRotation(float InX, float InY, float InZ)
{
    SetPosition(FVector(InX,InY,InZ));
}

void CCamera::SetRotation(const FVector& InValue)
{
    Rotation.X = FMath::ToRadians(FMath::WrapAngle(InValue.X));
    Rotation.Y = FMath::ToRadians(FMath::WrapAngle(InValue.Y));
    Rotation.Z = FMath::ToRadians(FMath::WrapAngle(InValue.Z));
    
    CalcRotationMatrix();
    CalcViewMatrix();
}
