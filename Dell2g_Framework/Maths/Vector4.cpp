#include "Framework.h"
#include "Vector4.h"

const FVector4 FVector4::Zero = FVector4(0.0f, 0.0f, 0.0f, 0.0f);
const FVector4 FVector4::One = FVector4(1.0f, 1.0f, 1.0f, 1.0f);

const FVector4 FVector4::UnitX = FVector4(1.0f, 0.0f, 0.0f, 0.0f);
const FVector4 FVector4::UnitY = FVector4(0.0f, 1.0f, 0.0f, 0.0f);
const FVector4 FVector4::UnitZ = FVector4(0.0f, 0.0f, 1.0f, 0.0f);
const FVector4 FVector4::UnitW = FVector4(0.0f, 0.0f, 0.0f, 1.0f);

FVector4::FVector4(void)
{
	X = 0.0f;
	Y = 0.0f;
	Z = 0.0f;
	W = 0.0f;
}

FVector4::FVector4(float InX, float InY, float InZ, float InW)
{
	X = InX;
	Y = InY;
	Z = InZ;
	W = InW;
}

FVector4::FVector4(FVector2D InValue, float InZ, float InW)
{
	X = InValue.X;
	Y = InValue.Y;
	Z = InZ;
	W = InW;
}

FVector4::FVector4(FVector InValue, float InW)
{
	X = InValue.X;
	Y = InValue.Y;
	Z = InValue.Z;
	W = InW;
}

FVector4::FVector4(float InValue)
{
	X = Y = Z = W = InValue;
}

FVector4::operator float* ()
{
	return V;
}

FVector4::operator const float* ()
{
	return V;
}

FVector4 FVector4::operator-(void)
{
	FVector4 vector4;
	vector4.X = -X;
	vector4.Y = -Y;
	vector4.Z = -Z;
	vector4.W = -W;

	return vector4;
}

bool FVector4::operator==(const FVector4& InValue) const
{
	if (X == InValue.X && Y == InValue.Y && Z == InValue.Z)
		return W == InValue.W;
	else
		return false;
}

bool FVector4::operator!=(const FVector4& InValue) const
{
	if (X == InValue.X && Y == InValue.Y && Z == InValue.Z)
		return W != InValue.W;
	else
		return true;
}

FVector4 FVector4::operator+(const FVector4& InValue) const
{
	FVector4 vector4;
	vector4.X = X + InValue.X;
	vector4.Y = Y + InValue.Y;
	vector4.Z = Z + InValue.Z;
	vector4.W = W + InValue.W;

	return vector4;
}

FVector4 FVector4::operator-(const FVector4& InValue) const
{
	FVector4 vector4;
	vector4.X = X - InValue.X;
	vector4.Y = Y - InValue.Y;
	vector4.Z = Z - InValue.Z;
	vector4.W = W - InValue.W;

	return vector4;
}

FVector4 FVector4::operator*(const FVector4& InValue) const
{
	FVector4 vector4;
	vector4.X = X * InValue.X;
	vector4.Y = Y * InValue.Y;
	vector4.Z = Z * InValue.Z;
	vector4.W = W * InValue.W;

	return vector4;
}

FVector4 FVector4::operator*(const float& InValue) const
{
	FVector4 vector4;
	vector4.X = X * InValue;
	vector4.Y = Y * InValue;
	vector4.Z = Z * InValue;
	vector4.W = W * InValue;

	return vector4;
}

FVector4 FVector4::operator/(const FVector4& InValue) const
{
	FVector4 vector4;
	vector4.X = X / InValue.X;
	vector4.Y = Y / InValue.Y;
	vector4.Z = Z / InValue.Z;
	vector4.W = W / InValue.W;

	return vector4;
}

FVector4 FVector4::operator/(const float& InValue) const
{
	float num = 1.0f / InValue;

	FVector4 vector4;
	vector4.X = X * num;
	vector4.Y = Y * num;
	vector4.Z = Z * num;
	vector4.W = W * num;

	return vector4;
}

void FVector4::operator+=(const FVector4& InValue)
{
	*this = *this + InValue;
}

void FVector4::operator-=(const FVector4& InValue)
{
	*this = *this - InValue;
}

void FVector4::operator*=(const FVector4& InValue)
{
	*this = *this * InValue;
}

void FVector4::operator*=(const float& InValue)
{
	*this = *this * InValue;
}

void FVector4::operator/=(const FVector4& InValue)
{
	*this = *this / InValue;
}

void FVector4::operator/=(const float& InValue)
{
	*this = *this / InValue;
}

std::string FVector4::ToString()
{
	std::string temp;

	temp += std::to_string(X);
	temp += "," + std::to_string(Y);
	temp += "," + std::to_string(Z);
	temp += "," + std::to_string(W);

	return temp;
}

float FVector4::Length()
{
	float x = X * X + Y * Y + Z * Z + W * W;

	return sqrtf(x);
}

float FVector4::LengthSquared()
{
	return X * X + Y * Y + Z * Z + W * W;
}
void FVector4::Normalize()
{
	float x = X * X + Y * Y + Z * Z + W * W;
	float single = 1.0f / sqrtf(x);

	X *= single;
	Y *= single;
	Z *= single;
	W *= single;
}

FVector4 FVector4::Add(FVector4 InValue, FVector4 InValue2)
{
	FVector4 vector4;
	vector4.X = InValue.X + InValue2.X;
	vector4.Y = InValue.Y + InValue2.Y;
	vector4.Z = InValue.Z + InValue2.Z;
	vector4.W = InValue.W + InValue2.W;

	return vector4;
}

FVector4 FVector4::Divide(FVector4 InValue, FVector4 InValue2)
{
	FVector4 vector4;
	vector4.X = InValue.X / InValue2.X;
	vector4.Y = InValue.Y / InValue2.Y;
	vector4.Z = InValue.Z / InValue2.Z;
	vector4.W = InValue.W / InValue2.W;

	return vector4;
}

FVector4 FVector4::Divide(FVector4 InValue, float InValue2)
{
	float single = 1.0f / InValue2;

	FVector4 vector4;
	vector4.X = InValue.X * single;
	vector4.Y = InValue.Y * single;
	vector4.Z = InValue.Z * single;
	vector4.W = InValue.W * single;

	return vector4;
}

FVector4 FVector4::Multiply(FVector4 InValue, FVector4 InValue2)
{
	FVector4 vector4;
	vector4.X = InValue.X * InValue2.X;
	vector4.Y = InValue.Y * InValue2.Y;
	vector4.Z = InValue.Z * InValue2.Z;
	vector4.W = InValue.W * InValue2.W;

	return vector4;
}

FVector4 FVector4::Multiply(FVector4 InValue, float InValue2)
{
	FVector4 vector4;
	vector4.X = InValue.X * InValue2;
	vector4.Y = InValue.Y * InValue2;
	vector4.Z = InValue.Z * InValue2;
	vector4.W = InValue.W * InValue2;
	return vector4;
}

FVector4 FVector4::Subtract(FVector4 InValue, FVector4 InValue2)
{
	FVector4 vector4;
	vector4.X = InValue.X - InValue2.X;
	vector4.Y = InValue.Y - InValue2.Y;
	vector4.Z = InValue.Z - InValue2.Z;
	vector4.W = InValue.W - InValue2.W;

	return vector4;
}

FVector4 FVector4::Negative(FVector4 InValue)
{
	FVector4 vector4;
	vector4.X = -InValue.X;
	vector4.Y = -InValue.Y;
	vector4.Z = -InValue.Z;
	vector4.W = -InValue.W;

	return vector4;
}

float FVector4::Distance(FVector4 InValue, FVector4 InValue2)
{
	float x = InValue.X - InValue2.X;
	float y = InValue.Y - InValue2.Y;
	float z = InValue.Z - InValue2.Z;
	float w = InValue.W - InValue2.W;

	float single = x * x + y * y + z * z + w * w;

	return sqrtf(single);
}

float FVector4::DistanceSquared(FVector4 InValue, FVector4 InValue2)
{
	float x = InValue.X - InValue2.X;
	float y = InValue.Y - InValue2.Y;
	float z = InValue.Z - InValue2.Z;
	float w = InValue.W - InValue2.W;

	return x * x + y * y + z * z + w * w;
}

float FVector4::Dot(FVector4 InValue, FVector4 InValue2)
{
	return InValue.X * InValue2.X + InValue.Y * InValue2.Y + InValue.Z * InValue2.Z + InValue.W * InValue2.W;
}

FVector4 FVector4::Normalize(FVector4 InValue)
{
	float num = 1.0f / sqrtf(InValue.X * InValue.X + InValue.Y * InValue.Y + InValue.Z * InValue.Z + InValue.W * InValue.W);

	FVector4 vector4;
	vector4.X = InValue.X * num;
	vector4.Y = InValue.Y * num;
	vector4.Z = InValue.Z * num;
	vector4.W = InValue.W * num;

	return vector4;
}

FVector4 FVector4::Min(FVector4 InValue, FVector4 InValue2)
{
	FVector4 vector4;
	vector4.X = InValue.X < InValue2.X ? InValue.X : InValue2.X;
	vector4.Y = InValue.Y < InValue2.Y ? InValue.Y : InValue2.Y;
	vector4.Z = InValue.Z < InValue2.Z ? InValue.Z : InValue2.Z;
	vector4.W = InValue.W < InValue2.W ? InValue.W : InValue2.W;

	return vector4;
}

FVector4 FVector4::Max(FVector4 InValue, FVector4 InValue2)
{
	FVector4 vector4;
	vector4.X = InValue.X > InValue2.X ? InValue.X : InValue2.X;
	vector4.Y = InValue.Y > InValue2.Y ? InValue.Y : InValue2.Y;
	vector4.Z = InValue.Z > InValue2.Z ? InValue.Z : InValue2.Z;
	vector4.W = InValue.W > InValue2.W ? InValue.W : InValue2.W;

	return vector4;
}

FVector4 FVector4::Clamp(FVector4 InValue, FVector4 InMin, FVector4 InMax)
{
	float x = InValue.X;
	x = (x > InMax.X ? InMax.X : x);
	x = (x < InMin.X ? InMin.X : x);

	float y = InValue.Y;
	y = (y > InMax.Y ? InMax.Y : y);
	y = (y < InMin.Y ? InMin.Y : y);

	float z = InValue.Z;
	z = (z > InMax.Z ? InMax.Z : z);
	z = (z < InMin.Z ? InMin.Z : z);

	float w = InValue.W;
	w = (w > InMax.W ? InMax.W : w);
	w = (w < InMin.W ? InMin.W : w);

	FVector4 vector4;
	vector4.X = x;
	vector4.Y = y;
	vector4.Z = z;
	vector4.W = w;
	return vector4;
}

FVector4 FVector4::Lerp(FVector4 InValue, FVector4 InValue2, float InAmount)
{
	FVector4 vector4;
	vector4.X = InValue.X + (InValue2.X - InValue.X) * InAmount;
	vector4.Y = InValue.Y + (InValue2.Y - InValue.Y) * InAmount;
	vector4.Z = InValue.Z + (InValue2.Z - InValue.Z) * InAmount;
	vector4.W = InValue.W + (InValue2.W - InValue.W) * InAmount;

	return vector4;
}

FVector4 FVector4::SmoothStep(FVector4 InValue, FVector4 InValue2, float InAmount)
{
	float single;
	if (InAmount > 1.0f)
		single = 1.0f;
	else
		single = (InAmount < 0.0f ? 0.0f : InAmount);

	InAmount = single;
	InAmount = InAmount * InAmount * (3.0f - 2.0f * InAmount);

	FVector4 vector4;
	vector4.X = InValue.X + (InValue2.X - InValue.X) * InAmount;
	vector4.Y = InValue.Y + (InValue2.Y - InValue.Y) * InAmount;
	vector4.Z = InValue.Z + (InValue2.Z - InValue.Z) * InAmount;
	vector4.W = InValue.W + (InValue2.W - InValue.W) * InAmount;

	return vector4;
}

FVector4 FVector4::Transform(FVector2D InValue, FMatrix InMatrix)
{
	float num1 = (InValue.X * InMatrix.M11 + InValue.Y * InMatrix.M21) + InMatrix.M41;
	float num2 = (InValue.X * InMatrix.M12 + InValue.Y * InMatrix.M22) + InMatrix.M42;
	float num3 = (InValue.X * InMatrix.M13 + InValue.Y * InMatrix.M23) + InMatrix.M43;
	float num4 = (InValue.X * InMatrix.M14 + InValue.Y * InMatrix.M24) + InMatrix.M44;

	FVector4 vector4;
	vector4.X = num1;
	vector4.Y = num2;
	vector4.Z = num3;
	vector4.W = num4;

	return vector4;
}

FVector4 FVector4::Transform(FVector InValue, FMatrix InMatrix)
{
	float num1 = (InValue.X * InMatrix.M11 + InValue.Y * InMatrix.M21 + InValue.Z * InMatrix.M31) + InMatrix.M41;
	float num2 = (InValue.X * InMatrix.M12 + InValue.Y * InMatrix.M22 + InValue.Z * InMatrix.M32) + InMatrix.M42;
	float num3 = (InValue.X * InMatrix.M13 + InValue.Y * InMatrix.M23 + InValue.Z * InMatrix.M33) + InMatrix.M43;
	float num4 = (InValue.X * InMatrix.M14 + InValue.Y * InMatrix.M24 + InValue.Z * InMatrix.M34) + InMatrix.M44;

	FVector4 vector4;
	vector4.X = num1;
	vector4.Y = num2;
	vector4.Z = num3;
	vector4.W = num4;

	return vector4;
}

FVector4 FVector4::Transform(FVector4 InValue, FMatrix InMatrix)
{
	float num1 = (InValue.X * InMatrix.M11 + InValue.Y * InMatrix.M21 + InValue.Z * InMatrix.M31 + InValue.W * InMatrix.M41);
	float num2 = (InValue.X * InMatrix.M12 + InValue.Y * InMatrix.M22 + InValue.Z * InMatrix.M32 + InValue.W * InMatrix.M42);
	float num3 = (InValue.X * InMatrix.M13 + InValue.Y * InMatrix.M23 + InValue.Z * InMatrix.M33 + InValue.W * InMatrix.M43);
	float num4 = (InValue.X * InMatrix.M14 + InValue.Y * InMatrix.M24 + InValue.Z * InMatrix.M34 + InValue.W * InMatrix.M44);

	FVector4 vector4;
	vector4.X = num1;
	vector4.Y = num2;
	vector4.Z = num3;
	vector4.W = num4;

	return vector4;
}

FVector4 FVector4::Transform(FVector2D InValue, FQuaternion InRotation)
{
	float x = InRotation.X + InRotation.X;
	float y = InRotation.Y + InRotation.Y;
	float z = InRotation.Z + InRotation.Z;
	float w = InRotation.W * x;
	float single = InRotation.W * y;

	float w1 = InRotation.W * z;
	float x1 = InRotation.X * x;
	float single1 = InRotation.X * y;

	float x2 = InRotation.X * z;
	float y1 = InRotation.Y * y;
	float y2 = InRotation.Y * z;
	float z1 = InRotation.Z * z;
	float single2 = InValue.X * (1.0f - y1 - z1) + InValue.Y * (single1 - w1);

	float x3 = InValue.X * (single1 + w1) + InValue.Y * (1.0f - x1 - z1);
	float single3 = InValue.X * (x2 - single) + InValue.Y * (y2 + w);

	
	FVector4 vector4;
	vector4.X = single2;
	vector4.Y = x3;
	vector4.Z = single3;
	vector4.W = 1.0f;

	return vector4;
}

FVector4 FVector4::Transform(FVector InValue, FQuaternion InRotation)
{
	float x = InRotation.X + InRotation.X;
	float y = InRotation.Y + InRotation.Y;
	float z = InRotation.Z + InRotation.Z;
	float w = InRotation.W * x;
	float single = InRotation.W * y;

	float w1 = InRotation.W * z;
	float x1 = InRotation.X * x;
	float single1 = InRotation.X * y;

	float x2 = InRotation.X * z;
	float y1 = InRotation.Y * y;
	float y2 = InRotation.Y * z;
	float z1 = InRotation.Z * z;
	float single2 = InValue.X * (1.0f - y1 - z1) + InValue.Y * (single1 - w1) + InValue.Z * (x2 + single);

	float x3 = InValue.X * (single1 + w1) + InValue.Y * (1.0f - x1 - z1) + InValue.Z * (y2 - w);
	float single3 = InValue.X * (x2 - single) + InValue.Y * (y2 + w) + InValue.Z * (1.0f - x1 - y1);

	
	FVector4 vector4;
	vector4.X = single2;
	vector4.Y = x3;
	vector4.Z = single3;
	vector4.W = 1.0f;

	return vector4;
}

FVector4 FVector4::Transform(FVector4 InValue, FQuaternion InRotation)
{
	float x = InRotation.X + InRotation.X;
	float y = InRotation.Y + InRotation.Y;
	float z = InRotation.Z + InRotation.Z;
	float w = InRotation.W * x;
	float single = InRotation.W * y;

	float w1 = InRotation.W * z;
	float x1 = InRotation.X * x;
	float single1 = InRotation.X * y;

	float x2 = InRotation.X * z;
	float y1 = InRotation.Y * y;
	float y2 = InRotation.Y * z;
	float z1 = InRotation.Z * z;
	float single2 = InValue.X * (1.0f - y1 - z1) + InValue.Y * (single1 - w1) + InValue.Z * (x2 + single);

	float x3 = InValue.X * (single1 + w1) + InValue.Y * (1.0f - x1 - z1) + InValue.Z * (y2 - w);
	float single3 = InValue.X * (x2 - single) + InValue.Y * (y2 + w) + InValue.Z * (1.0f - x1 - y1);

	
	FVector4 vector4;
	vector4.X = single2;
	vector4.Y = x3;
	vector4.Z = single3;
	vector4.W = InValue.W;

	return vector4;
}
