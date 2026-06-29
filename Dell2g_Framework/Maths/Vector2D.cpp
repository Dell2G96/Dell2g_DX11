#include "Framework.h"
#include "Vector2D.h"

const FVector2D FVector2D::Zero = FVector2D(0.0f, 0.0f);
const FVector2D FVector2D::One = FVector2D(1.0f, 1.0f);
const FVector2D FVector2D::UnitX = FVector2D(1.0f, 0.0f);
const FVector2D FVector2D::UnitY = FVector2D(0.0f, 1.0f);

FVector2D::FVector2D(void)
{
	X = 0.0f;
	Y = 0.0f;
}

FVector2D::FVector2D(float InValue)
{
	X = Y = InValue;
}

FVector2D::FVector2D(float InX, float InY)
{
	X = InX;
	Y = InY;
}

FVector2D::operator float* ()
{
	return V;
}

FVector2D::operator const float* ()
{
	return V;
}

FVector2D FVector2D::operator-(void)
{
	FVector2D vector2;
	vector2.X = -X;
	vector2.Y = -Y;

	return vector2;
}

bool FVector2D::operator==(const FVector2D& InValue) const
{
	if (X == InValue.X)
		return Y == InValue.Y;
	else
		return false;
}

bool FVector2D::operator!=(const FVector2D& InValue) const
{
	if (X == InValue.X)
		return Y != InValue.Y;
	else
		return true;
}

FVector2D FVector2D::operator+(const FVector2D& InValue) const
{
	FVector2D vector2;
	vector2.X = X + InValue.X;
	vector2.Y = Y + InValue.Y;

	return vector2;
}

FVector2D FVector2D::operator-(const FVector2D& InValue) const
{
	FVector2D vector2;
	vector2.X = X - InValue.X;
	vector2.Y = Y - InValue.Y;

	return vector2;
}

FVector2D FVector2D::operator*(const FVector2D& InValue) const
{
	FVector2D vector2;
	vector2.X = X * InValue.X;
	vector2.Y = Y * InValue.Y;

	return vector2;
}

FVector2D FVector2D::operator*(const float& InValue) const
{
	FVector2D vector2;
	vector2.X = X * InValue;
	vector2.Y = Y * InValue;

	return vector2;
}

FVector2D FVector2D::operator/(const FVector2D& InValue) const
{
	FVector2D vector2;
	vector2.X = X / InValue.X;
	vector2.Y = Y / InValue.Y;

	return vector2;
}

FVector2D FVector2D::operator/(const float& InValue) const
{
	float num = 1.0f / InValue;

	FVector2D vector2;
	vector2.X = X * num;
	vector2.Y = Y * num;

	return vector2;
}

void FVector2D::operator+=(const FVector2D& InValue)
{
	*this = *this + InValue;
}

void FVector2D::operator-=(const FVector2D& InValue)
{
	*this = *this - InValue;
}

void FVector2D::operator*=(const FVector2D& InValue)
{
	*this = *this * InValue;
}

void FVector2D::operator*=(const float& InValue)
{
	*this = *this * InValue;
}

void FVector2D::operator/=(const FVector2D& InValue)
{
	*this = *this / InValue;
}

void FVector2D::operator/=(const float& InValue)
{
	*this = *this / InValue;
}

std::string FVector2D::ToString()
{
	std::string temp;

	temp += std::to_string(X);
	temp += "," + std::to_string(Y);

	return temp;
}

float FVector2D::Length()
{
	float x = X * X + Y * Y;

	return sqrtf(x);
}

float FVector2D::LengthSquared()
{
	return X * X + Y * Y;
}

void FVector2D::Normalize()
{
	float x = X * X + Y * Y;
	float single = 1.0f / sqrtf(x);

	X *= single;
	Y *= single;
}

FVector2D FVector2D::Add(FVector2D InValue1, FVector2D InValue2)
{
	FVector2D vector2;
	vector2.X = InValue1.X + InValue2.X;
	vector2.Y = InValue1.Y + InValue2.Y;

	return vector2;
}

FVector2D FVector2D::Divide(FVector2D InValue1, FVector2D InValue2)
{
	FVector2D vector2;
	vector2.X = InValue1.X / InValue2.X;
	vector2.Y = InValue1.Y / InValue2.Y;

	return vector2;
}

FVector2D FVector2D::Divide(FVector2D InValue1, float InValue2)
{
	float single = 1.0f / InValue2;

	FVector2D vector2;
	vector2.X = InValue1.X * single;
	vector2.Y = InValue1.Y * single;

	return vector2;
}

FVector2D FVector2D::Multiply(FVector2D InValue1, FVector2D InValue2)
{
	FVector2D vector2;
	vector2.X = InValue1.X * InValue2.X;
	vector2.Y = InValue1.Y * InValue2.Y;

	return vector2;
}

FVector2D FVector2D::Multiply(FVector2D InValue1, float InValue2)
{
	FVector2D vector2;
	vector2.X = InValue1.X * InValue2;
	vector2.Y = InValue1.Y * InValue2;

	return vector2;
}

FVector2D FVector2D::Subtract(FVector2D InValue1, FVector2D InValue2)
{
	FVector2D vector2;
	vector2.X = InValue1.X - InValue2.X;
	vector2.Y = InValue1.Y - InValue2.Y;

	return vector2;
}

FVector2D FVector2D::Negative(FVector2D InValue)
{
	FVector2D vector2;
	vector2.X = -InValue.X;
	vector2.Y = -InValue.Y;

	return vector2;
}

float FVector2D::Distance(FVector2D InValue1, FVector2D InValue2)
{
	float x = InValue1.X - InValue2.X;
	float y = InValue1.Y - InValue2.Y;
	float single = x * x + y * y;

	return sqrtf(single);
}

float FVector2D::DistanceSquared(FVector2D InValue1, FVector2D InValue2)
{
	float x = InValue1.X - InValue2.X;
	float y = InValue1.Y - InValue2.Y;

	return x * x + y * y;
}

float FVector2D::Dot(FVector2D InValue1, FVector2D InValue2)
{
	return InValue1.X * InValue2.X + InValue1.Y * InValue2.Y;
}

FVector2D FVector2D::Normalize(FVector2D InValue)
{
	float x = InValue.X * InValue.X + InValue.Y * InValue.Y;
	float single = 1.0f / sqrtf(x);

	FVector2D vector2;
	vector2.X = InValue.X * single;
	vector2.Y = InValue.Y * single;

	return vector2;
}

FVector2D FVector2D::Reflect(FVector2D InValue, FVector2D InNormal)
{
	float x = InValue.X * InNormal.X + InValue.Y * InNormal.Y;

	FVector2D vector2;
	vector2.X = InValue.X - 2.0f * x * InNormal.X;
	vector2.Y = InValue.Y - 2.0f * x * InNormal.Y;

	return vector2;
}

FVector2D FVector2D::Min(FVector2D InValue1, FVector2D InValue2)
{
	FVector2D vector2;
	vector2.X = (InValue1.X < InValue2.X ? InValue1.X : InValue2.X);
	vector2.Y = (InValue1.Y < InValue2.Y ? InValue1.Y : InValue2.Y);

	return vector2;
}

FVector2D FVector2D::Max(FVector2D InValue1, FVector2D InValue2)
{
	FVector2D vector2;
	vector2.X = (InValue1.X > InValue2.X ? InValue1.X : InValue2.X);
	vector2.Y = (InValue1.Y > InValue2.Y ? InValue1.Y : InValue2.Y);

	return vector2;
}

FVector2D FVector2D::Clamp(FVector2D InValue1, FVector2D InMin, FVector2D InMax)
{
	float x = InValue1.X;
	x = (x > InMax.X ? InMax.X : x);
	x = (x < InMin.X ? InMin.X : x);

	float y = InValue1.Y;
	y = (y > InMax.Y ? InMax.Y : y);
	y = (y < InMin.Y ? InMin.Y : y);

	FVector2D vector2;
	vector2.X = x;
	vector2.Y = y;

	return vector2;
}

FVector2D FVector2D::Lerp(FVector2D InValue1, FVector2D InValue2, float InAmount)
{
	FVector2D vector2;
	vector2.X = InValue1.X + (InValue2.X - InValue1.X) * InAmount;
	vector2.Y = InValue1.Y + (InValue2.Y - InValue1.Y) * InAmount;

	return vector2;
}

FVector2D FVector2D::SmoothStep(FVector2D InValue1, FVector2D InValue2, float InAmount)
{
	float single;
	if (InAmount > 1.0f)
		single = 1.0f;
	else
		single = (InAmount < 0.0f ? 0.0f : InAmount);

	InAmount = single;
	InAmount = InAmount * InAmount * (3.0f - 2.0f * InAmount);

	FVector2D vector2;
	vector2.X = InValue1.X + (InValue2.X - InValue1.X) * InAmount;
	vector2.Y = InValue1.Y + (InValue2.Y - InValue1.Y) * InAmount;

	return vector2;
}

FVector2D FVector2D::Transform(FVector2D InValue, FMatrix InMatrix)
{
	float x = InValue.X * InMatrix.M11 + InValue.Y * InMatrix.M21 + InMatrix.M41;
	float single = InValue.X * InMatrix.M12 + InValue.Y * InMatrix.M22 + InMatrix.M42;

	FVector2D vector2;
	vector2.X = x;
	vector2.Y = single;

	return vector2;
}

FVector2D FVector2D::Transform(FVector2D InValue, FQuaternion InRotation)
{
	float x = InRotation.X + InRotation.X;
	float y = InRotation.Y + InRotation.Y;
	float z = InRotation.Z + InRotation.Z;
	float w = InRotation.W * z;

	float single = InRotation.X * x;
	float x1 = InRotation.X * y;
	float y1 = InRotation.Y * y;
	float z1 = InRotation.Z * z;

	float single1 = InValue.X * (1.0f - y1 - z1) + InValue.Y * (x1 - w);
	float x2 = InValue.X * (x1 + w) + InValue.Y * (1.0f - single - z1);

	FVector2D vector2;
	vector2.X = single1;
	vector2.Y = x2;

	return vector2;
}

FVector2D FVector2D::TransformNormal(FVector2D InNormal, FMatrix InMatrix)
{
	float x = InNormal.X * InMatrix.M11 + InNormal.Y * InMatrix.M21;
	float single = InNormal.X * InMatrix.M12 + InNormal.Y * InMatrix.M22;

	FVector2D vector2;
	vector2.X = x;
	vector2.Y = single;

	return vector2;
}
