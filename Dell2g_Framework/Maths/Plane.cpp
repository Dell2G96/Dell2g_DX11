#include "Framework.h"
#include "Plane.h"

FPlane::FPlane(void)
{
	Normal = FVector::Zero;

	D = 0.0f;
}

FPlane::FPlane(float InA, float InB, float InC, float InD)
{
	Normal.X = InA;
	Normal.Y = InB;
	Normal.Z = InC;

	D = InD;
}

FPlane::FPlane(FVector& InNormal, float InD)
{
	Normal = InNormal;

	D = InD;
}

FPlane::FPlane(FVector4& InValue)
{
	Normal.X = InValue.X;
	Normal.Y = InValue.Y;
	Normal.Z = InValue.Z;

	D = InValue.W;
}

FPlane::FPlane(FVector& InPoint1, FVector& InPoint2, FVector& InPoint3)
{
	float x = InPoint2.X - InPoint1.X;
	float y = InPoint2.Y - InPoint1.Y;
	float z = InPoint2.Z - InPoint1.Z;
	float y1 = InPoint3.Y - InPoint1.Y;
	float z1 = InPoint3.Z - InPoint1.Z;

	float value = InPoint3.X - InPoint1.X;
	float value1 = y * z1 - z * y1;
	float value2 = z * value - x * z1;
	float value3 = x * y1 - y * value;
	float value4 = value1 * value1 + value2 * value2 + value3 * value3;
	float value5 = 1.0f / sqrtf(value4);

	Normal.X = value1 * value5;
	Normal.Y = value2 * value5;
	Normal.Z = value3 * value5;

	D = -(Normal.X * InPoint1.X + Normal.Y * InPoint1.Y + Normal.Z * InPoint1.Z);
}

FPlane::operator float* ()
{
	return P;
}

FPlane::operator const float* ()
{
	return P;
}

bool FPlane::operator==(const FPlane& InValue)const
{
	if (Normal.X == InValue.Normal.X && Normal.Y == InValue.Normal.Y && Normal.Z == InValue.Normal.Z)
		return D == InValue.D;
	else
		return false;
}

bool FPlane::operator!=(const FPlane& InValue)const
{
	if (Normal.X == InValue.Normal.X && Normal.Y == InValue.Normal.Y && Normal.Z == InValue.Normal.Z)
		return D != InValue.D;
	else
		return true;
}

std::string FPlane::ToString()
{
	std::string temp = "";

	temp += Normal.ToString();
	temp += "," + std::to_string(D);

	return temp;
}

float FPlane::Dot(FVector4& InValue)
{
	return Normal.X * InValue.X + Normal.Y * InValue.Y + Normal.Z * InValue.Z + D * InValue.W;
}

float FPlane::DotCoordinate(FVector& InValue)
{
	return Normal.X * InValue.X + Normal.Y * InValue.Y + Normal.Z * InValue.Z + D;
}

float FPlane::DotNormal(FVector& InValue)
{
	return Normal.X * InValue.X + Normal.Y * InValue.Y + Normal.Z * InValue.Z;
}

void FPlane::Normalize()
{
	float x = Normal.X * Normal.X + Normal.Y * Normal.Y + Normal.Z * Normal.Z;

	if (fabsf(x - 1.0f) < 1.1920929E-07f)
		return;

	float single = 1.0f / sqrtf(x);
	Normal.X *= single;
	Normal.Y *= single;
	Normal.Z *= single;

	D *= single;
}

FPlane FPlane::Normalize(FPlane& InValue)
{
	FPlane normal;
	float x = InValue.Normal.X * InValue.Normal.X + InValue.Normal.Y * InValue.Normal.Y + InValue.Normal.Z * InValue.Normal.Z;

	if (fabsf(x - 1.0f) < 1.1920929E-07f)
	{
		normal.Normal = InValue.Normal;
		normal.D = InValue.D;

		return normal;
	}

	float value2 = 1.0f / sqrtf(x);
	normal.Normal.X = InValue.Normal.X * value2;
	normal.Normal.Y = InValue.Normal.Y * value2;
	normal.Normal.Z = InValue.Normal.Z * value2;
	normal.D = InValue.D * value2;

	return normal;
}

FPlane FPlane::Transform(FPlane& InPlane, FMatrix& InMatrix)
{
	FMatrix matrix1 = FMatrix::Invert(InMatrix);

	float x = InPlane.Normal.X;
	float y = InPlane.Normal.Y;
	float z = InPlane.Normal.Z;
	float d = InPlane.D;

	FPlane p;
	p.Normal.X = x * matrix1.M11 + y * matrix1.M12 + z * matrix1.M13 + d * matrix1.M14;
	p.Normal.Y = x * matrix1.M21 + y * matrix1.M22 + z * matrix1.M23 + d * matrix1.M24;
	p.Normal.Z = x * matrix1.M31 + y * matrix1.M32 + z * matrix1.M33 + d * matrix1.M34;
	p.D = x * matrix1.M41 + y * matrix1.M42 + z * matrix1.M43 + d * matrix1.M44;

	return p;
}

FPlane FPlane::Transform(FPlane& InPlane, FQuaternion& InRotation)
{
	float x = InRotation.X + InRotation.X;
	float y = InRotation.Y + InRotation.Y;
	float z = InRotation.Z + InRotation.Z;
	float w = InRotation.W * x;
	float value = InRotation.W * y;

	float w1 = InRotation.W * z;
	float x1 = InRotation.X * x;
	float value1 = InRotation.X * y;

	float x2 = InRotation.X * z;
	float y1 = InRotation.Y * y;
	float y2 = InRotation.Y * z;
	float z1 = InRotation.Z * z;

	float value2 = 1.0f - y1 - z1;
	float value3 = value1 - w1;
	float value4 = x2 + value;
	float value5 = value1 + w1;
	float value6 = 1.0f - x1 - z1;

	float value7 = y2 - w;
	float value8 = x2 - value;
	float value9 = y2 + w;
	float value10 = 1.0f - x1 - y1;

	float x3 = InPlane.Normal.X;
	float y3 = InPlane.Normal.Y;
	float z2 = InPlane.Normal.Z;

	FPlane p;
	p.Normal.X = x3 * value2 + y3 * value3 + z2 * value4;
	p.Normal.Y = x3 * value5 + y3 * value6 + z2 * value7;
	p.Normal.Z = x3 * value8 + y3 * value9 + z2 * value10;
	p.D = InPlane.D;

	return p;
}
