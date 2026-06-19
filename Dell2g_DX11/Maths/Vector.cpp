#include "Framework.h"
#include "Vector.h"

const FVector FVector::Zero = FVector(0.0f, 0.0f, 0.0f);
const FVector FVector::One = FVector(1.0f, 1.0f, 1.0f);

const FVector FVector::UnitX = FVector(1.0f, 0.0f, 0.0f);
const FVector FVector::UnitY = FVector(0.0f, 1.0f, 0.0f);
const FVector FVector::UnitZ = FVector(0.0f, 0.0f, 1.0f);

const FVector FVector::Up = FVector(0.0f, 1.0f, 0.0f);
const FVector FVector::Down = FVector(0.0f, -1.0f, 0.0f);
const FVector FVector::Right = FVector(1.0f, 0.0f, 0.0f);
const FVector FVector::Left = FVector(-1.0f, 0.0f, 0.0f);
const FVector FVector::Forward = FVector(0.0f, 0.0f, 1.0f);
const FVector FVector::Backward = FVector(0.0f, 0.0f, -1.0f);

FVector::FVector(void)
{
	X = 0.0f;
	Y = 0.0f;
	Z = 0.0f;
}

FVector::FVector(float InValue)
{
	X = Y = Z = InValue;
}

FVector::FVector(float InX, float InY, float InZ)
{
	X = InX;
	Y = InY;
	Z = InZ;
}

FVector::operator float* ()
{
	return V;
}

FVector::operator const float* ()
{
	return V;
}

FVector FVector::operator-(void)
{
	FVector vector3;
	vector3.X = -X;
	vector3.Y = -Y;
	vector3.Z = -Z;

	return vector3;
}

bool FVector::operator==(const FVector& InValue) const
{
	if (X == InValue.X && Y == InValue.Y)
		return Z == InValue.Z;
	else
		return false;
}

bool FVector::operator!=(const FVector& InValue) const
{
	if (X == InValue.X && Y == InValue.Y)
		return Z != InValue.Z;
	else
		return true;
}

FVector FVector::operator+(const FVector& InValue) const
{
	FVector vector3;
	vector3.X = X + InValue.X;
	vector3.Y = Y + InValue.Y;
	vector3.Z = Z + InValue.Z;

	return vector3;
}

FVector FVector::operator-(const FVector& InValue) const
{
	FVector vector3;
	vector3.X = X - InValue.X;
	vector3.Y = Y - InValue.Y;
	vector3.Z = Z - InValue.Z;

	return vector3;
}

FVector FVector::operator*(const FVector& InValue) const
{
	FVector vector3;
	vector3.X = X * InValue.X;
	vector3.Y = Y * InValue.Y;
	vector3.Z = Z * InValue.Z;

	return vector3;
}

FVector FVector::operator*(const float& InValue) const
{
	FVector vector3;
	vector3.X = X * InValue;
	vector3.Y = Y * InValue;
	vector3.Z = Z * InValue;

	return vector3;
}

FVector FVector::operator/(const FVector& InValue) const
{
	FVector vector3;
	vector3.X = X / InValue.X;
	vector3.Y = Y / InValue.Y;
	vector3.Z = Z / InValue.Z;

	return vector3;
}

FVector FVector::operator/(const float& InValue) const
{
	float num = 1.0f / InValue;

	FVector vector3;
	vector3.X = X * num;
	vector3.Y = Y * num;
	vector3.Z = Z * num;

	return vector3;
}

void FVector::operator+=(const FVector& InValue)
{
	*this = *this + InValue;
}

void FVector::operator-=(const FVector& InValue)
{
	*this = *this - InValue;
}

void FVector::operator*=(const FVector& InValue)
{
	*this = *this * InValue;
}

void FVector::operator*=(const float& InValue)
{
	*this = *this * InValue;
}

void FVector::operator/=(const FVector& InValue)
{
	*this = *this / InValue;
}

void FVector::operator/=(const float& InValue)
{
	*this = *this / InValue;
}

std::string FVector::ToString()
{
	std::string temp = "";
	temp += std::to_string(X);
	temp += "," + std::to_string(Y);
	temp += "," + std::to_string(Z);

	return temp;
}

float FVector::Length()
{
	float x = X * X + Y * Y + Z * Z;

	return sqrtf(x);
}

float FVector::LengthSquared()
{
	return X * X + Y * Y + Z * Z;
}

void FVector::Normalize()
{
	float x = X * X + Y * Y + Z * Z;
	float single = 1.0f / sqrtf(x);

	X *= single;
	Y *= single;
	Z *= single;
}

FVector FVector::Add(FVector InValue, FVector InValue2)
{
	FVector vector3;
	vector3.X = InValue.X + InValue2.X;
	vector3.Y = InValue.Y + InValue2.Y;
	vector3.Z = InValue.Z + InValue2.Z;

	return vector3;
}

FVector FVector::Divide(FVector InValue, FVector InValue2)
{
	FVector vector3;
	vector3.X = InValue.X / InValue2.X;
	vector3.Y = InValue.Y / InValue2.Y;
	vector3.Z = InValue.Z / InValue2.Z;

	return vector3;
}

FVector FVector::Divide(FVector InValue, float InValue2)
{
	float single = 1.0f / InValue2;

	FVector vector3;
	vector3.X = InValue.X * single;
	vector3.Y = InValue.Y * single;
	vector3.Z = InValue.Z * single;

	return vector3;
}

FVector FVector::Multiply(FVector InValue, FVector InValue2)
{
	FVector vector3;
	vector3.X = InValue.X * InValue2.X;
	vector3.Y = InValue.Y * InValue2.Y;
	vector3.Z = InValue.Z * InValue2.Z;

	return vector3;
}

FVector FVector::Multiply(FVector InValue, float InValue2)
{
	FVector vector3;
	vector3.X = InValue.X * InValue2;
	vector3.Y = InValue.Y * InValue2;
	vector3.Z = InValue.Z * InValue2;

	return vector3;
}

FVector FVector::Subtract(FVector InValue, FVector InValue2)
{
	FVector vector3;
	vector3.X = InValue.X - InValue2.X;
	vector3.Y = InValue.Y - InValue2.Y;
	vector3.Z = InValue.Z - InValue2.Z;

	return vector3;
}

FVector FVector::Negative(FVector InValue)
{
	FVector vector3;
	vector3.X = -InValue.X;
	vector3.Y = -InValue.Y;
	vector3.Z = -InValue.Z;

	return vector3;
}

float FVector::Distance(FVector InValue, FVector InValue2)
{
	float x = InValue.X - InValue2.X;
	float y = InValue.Y - InValue2.Y;
	float z = InValue.Z - InValue2.Z;
	float single = x * x + y * y + z * z;

	return sqrtf(single);
}

float FVector::DistanceSquared(FVector InValue, FVector InValue2)
{
	float x = InValue.X - InValue2.X;
	float y = InValue.Y - InValue2.Y;
	float z = InValue.Z - InValue2.Z;

	return x * x + y * y + z * z;
}

float FVector::Dot(FVector InValue, FVector InValue2)
{
	return InValue.X * InValue2.X + InValue.Y * InValue2.Y + InValue.Z * InValue2.Z;
}

FVector FVector::Normalize(FVector InValue)
{
	float x = InValue.X * InValue.X + InValue.Y * InValue.Y + InValue.Z * InValue.Z;
	float single = 1.0f / sqrtf(x);

	FVector vector3;
	vector3.X = InValue.X * single;
	vector3.Y = InValue.Y * single;
	vector3.Z = InValue.Z * single;

	return vector3;
}

FVector FVector::Cross(FVector InValue, FVector InValue2)
{
	FVector vector3;
	vector3.X = InValue.Y * InValue2.Z - InValue.Z * InValue2.Y;
	vector3.Y = InValue.Z * InValue2.X - InValue.X * InValue2.Z;
	vector3.Z = InValue.X * InValue2.Y - InValue.Y * InValue2.X;

	return vector3;
}

FVector FVector::Reflect(FVector InValue, FVector InNormal)
{
	float x = InValue.X * InNormal.X + InValue.Y * InNormal.Y + InValue.Z * InNormal.Z;

	FVector vector3;
	vector3.X = InValue.X - 2.0f * x * InNormal.X;
	vector3.Y = InValue.Y - 2.0f * x * InNormal.Y;
	vector3.Z = InValue.Z - 2.0f * x * InNormal.Z;
	return vector3;
}

FVector FVector::Min(FVector InValue, FVector InValue2)
{
	FVector vector3;
	vector3.X = InValue.X < InValue2.X ? InValue.X : InValue2.X;
	vector3.Y = InValue.Y < InValue2.Y ? InValue.Y : InValue2.Y;
	vector3.Z = InValue.Z < InValue2.Z ? InValue.Z : InValue2.Z;

	return vector3;
}

FVector FVector::Max(FVector InValue, FVector InValue2)
{
	FVector vector3;
	vector3.X = InValue.X > InValue2.X ? InValue.X : InValue2.X;
	vector3.Y = InValue.Y > InValue2.Y ? InValue.Y : InValue2.Y;
	vector3.Z = InValue.Z > InValue2.Z ? InValue.Z : InValue2.Z;

	return vector3;
}

FVector FVector::Clamp(FVector InValue, FVector InMin, FVector InMax)
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

	FVector vector3;
	vector3.X = x;
	vector3.Y = y;
	vector3.Z = z;

	return vector3;
}

FVector FVector::Lerp(FVector InValue, FVector InValue2, float InAmount)
{
	FVector vector3;
	vector3.X = InValue.X + (InValue2.X - InValue.X) * InAmount;
	vector3.Y = InValue.Y + (InValue2.Y - InValue.Y) * InAmount;
	vector3.Z = InValue.Z + (InValue2.Z - InValue.Z) * InAmount;

	return vector3;
}

FVector FVector::SmoothStep(FVector InValue, FVector InValue2, float InAmount)
{
	float single;

	if (InAmount > 1.0f)
		single = 1.0f;
	else
		single = (InAmount < 0.0f ? 0.0f : InAmount);


	InAmount = single;
	InAmount = InAmount * InAmount * (3.0f - 2.0f * InAmount);


	FVector vector3;
	vector3.X = InValue.X + (InValue2.X - InValue.X) * InAmount;
	vector3.Y = InValue.Y + (InValue2.Y - InValue.Y) * InAmount;
	vector3.Z = InValue.Z + (InValue2.Z - InValue.Z) * InAmount;

	return vector3;
}

FVector FVector::Transform(FVector Invalue, FMatrix InMatrix)
{
	float x = Invalue.X * InMatrix.M11 + Invalue.Y * InMatrix.M21 + Invalue.Z * InMatrix.M31 + InMatrix.M41;
	float single = Invalue.X * InMatrix.M12 + Invalue.Y * InMatrix.M22 + Invalue.Z * InMatrix.M32 + InMatrix.M42;
	float x1 = Invalue.X * InMatrix.M13 + Invalue.Y * InMatrix.M23 + Invalue.Z * InMatrix.M33 + InMatrix.M43;

	FVector vector3;
	vector3.X = x;
	vector3.Y = single;
	vector3.Z = x1;

	return vector3;
}

FVector FVector::Transform(FVector InValue, FQuaternion InRotation)
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

	FVector vector3;
	vector3.X = single2;
	vector3.Y = x3;
	vector3.Z = single3;

	return vector3;
}

FVector FVector::TransformNormal(FVector InValue, FMatrix InMatrix)
{
	float x = InValue.X * InMatrix.M11 + InValue.Y * InMatrix.M21 + InValue.Z * InMatrix.M31;
	float single = InValue.X * InMatrix.M12 + InValue.Y * InMatrix.M22 + InValue.Z * InMatrix.M32;
	float x1 = InValue.X * InMatrix.M13 + InValue.Y * InMatrix.M23 + InValue.Z * InMatrix.M33;

	FVector vector3;
	vector3.X = x;
	vector3.Y = single;
	vector3.Z = x1;

	return vector3;
}

FVector FVector::TransformCoord(FVector InValue, FMatrix InMatrix)
{
	float single1 = (InMatrix.M11 * InValue.X) + (InMatrix.M21 * InValue.Y) + (InMatrix.M31 * InValue.Z) + InMatrix.M41;
	float single2 = (InMatrix.M12 * InValue.X) + (InMatrix.M22 * InValue.Y) + (InMatrix.M32 * InValue.Z) + InMatrix.M42;
	float single3 = (InMatrix.M13 * InValue.X) + (InMatrix.M23 * InValue.Y) + (InMatrix.M33 * InValue.Z) + InMatrix.M43;
	float single4 = (InMatrix.M14 * InValue.X) + (InMatrix.M24 * InValue.Y) + (InMatrix.M34 * InValue.Z) + InMatrix.M44;

	return FVector((single1 / single4), (single2 / single4), (single3 / single4));
}