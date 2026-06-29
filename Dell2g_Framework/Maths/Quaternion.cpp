#include "Framework.h"
#include "Quaternion.h"

const FQuaternion FQuaternion::Identity = FQuaternion(0.0f, 0.0f, 0.0f, 1.0f);

FQuaternion::FQuaternion(void)
{
	X = 0.0f;
	Y = 0.0f;
	Z = 0.0f;
	W = 0.0f;
}

FQuaternion::FQuaternion(float InX, float InY, float InZ, float InW)
{
	X = InX;
	Y = InY;
	Z = InZ;
	W = InW;
}

FQuaternion::FQuaternion(FVector InValue, float InValue2)
{
	X = InValue.X;
	Y = InValue.Y;
	Z = InValue.Z;
	W = InValue2;
}

FQuaternion::operator float* ()
{
	return Q;
}

FQuaternion::operator const float* ()
{
	return Q;
}

FQuaternion FQuaternion::operator-(void)
{
	FQuaternion InValue;
	InValue.X = -X;
	InValue.Y = -Y;
	InValue.Z = -Z;
	InValue.W = -W;

	return InValue;
}

bool FQuaternion::operator==(const FQuaternion& InValue) const
{
	if (X == InValue.X && Y == InValue.Y && Z == InValue.Z)
		return W == InValue.W;
	else
		return false;
}

bool FQuaternion::operator!=(const FQuaternion& InValue) const
{
	if (X == InValue.X && Y == InValue.Y && Z == InValue.Z)
		return W != InValue.W;
	else
		return true;
}

FQuaternion FQuaternion::operator+(const FQuaternion& InValue) const
{
	FQuaternion quaternion;
	quaternion.X = X + InValue.X;
	quaternion.Y = Y + InValue.Y;
	quaternion.Z = Z + InValue.Z;
	quaternion.W = W + InValue.W;

	return quaternion;
}

FQuaternion FQuaternion::operator-(const FQuaternion& InValue) const
{
	FQuaternion quaternion;
	quaternion.X = X - InValue.X;
	quaternion.Y = Y - InValue.Y;
	quaternion.Z = Z - InValue.Z;
	quaternion.W = W - InValue.W;
	return quaternion;
}

FQuaternion FQuaternion::operator*(const FQuaternion& InValue) const
{
	float value1 = Y * InValue.Z - Z * InValue.Y;
	float value2 = Z * InValue.X - X * InValue.Z;
	float value3 = X * InValue.Y - Y * InValue.X;
	float value4 = X * InValue.X + Y * InValue.Y + Z * InValue.Z;

	FQuaternion quaternion;
	quaternion.X = X * InValue.W + InValue.X * W + value1;
	quaternion.Y = Y * InValue.W + InValue.Y * W + value2;
	quaternion.Z = Z * InValue.W + InValue.Z * W + value3;
	quaternion.W = W * InValue.W - value4;

	return quaternion;
}

FQuaternion FQuaternion::operator*(const float& InValue) const
{
	FQuaternion quaternion;
	quaternion.X = X * InValue;
	quaternion.Y = Y * InValue;
	quaternion.Z = Z * InValue;
	quaternion.W = W * InValue;

	return quaternion;
}

FQuaternion FQuaternion::operator/(const FQuaternion& InValue) const
{
	float value1 = 1.0f / InValue.X * InValue.X + InValue.Y * InValue.Y + InValue.Z * InValue.Z + InValue.W * InValue.W;
	float value2 = -InValue.X * value1;
	float value3 = -InValue.Y * value1;
	float value4 = -InValue.Z * value1;
	float value5 = InValue.W * value1;

	float multiple1 = Y * value4 - Z * value3;
	float multiple2 = Z * value2 - X * value4;
	float multiple3 = X * value3 - Y * value2;
	float multiple4 = X * value2 + Y * value3 + Z * value4;

	FQuaternion quaternion;
	quaternion.X = X * value5 + value2 * W + multiple1;
	quaternion.Y = Y * value5 + value3 * W + multiple2;
	quaternion.Z = Z * value5 + value4 * W + multiple3;
	quaternion.W = W * value5 - multiple4;

	return quaternion;
}

void FQuaternion::operator+=(const FQuaternion& InValue)
{
	*this = *this + InValue;
}

void FQuaternion::operator-=(const FQuaternion& InValue)
{
	*this = *this - InValue;
}

void FQuaternion::operator*=(const FQuaternion& InValue)
{
	*this = *this * InValue;
}

void FQuaternion::operator*=(const float& InValue)
{
	*this = *this * InValue;
}

void FQuaternion::operator/=(const FQuaternion& InValue)
{
	*this = *this / InValue;
}

std::string FQuaternion::ToString()
{
	std::string temp = "";

	temp += std::to_string(X);
	temp += ",:" + std::to_string(Y);
	temp += ",:" + std::to_string(Z);
	temp += ",:" + std::to_string(W);

	return temp;
}

float FQuaternion::Length()
{
	float x = X * X + Y * Y + Z * Z + W * W;

	return sqrtf(x);
}

float FQuaternion::LengthSquared()
{
	return X * X + Y * Y + Z * Z + W * W;
}

void FQuaternion::Normalize()
{
	float x = X * X + Y * Y + Z * Z + W * W;
	float value = 1.0f / sqrtf(x);

	X *= value;
	Y *= value;
	Z *= value;
	W *= value;
}

FQuaternion FQuaternion::Normalize(FQuaternion InValue)
{
	float value = InValue.X * InValue.X + InValue.Y * InValue.Y + InValue.Z * InValue.Z + InValue.W * InValue.W;
	float value1 = 1.0f / sqrtf(value);


	FQuaternion q;
	q.X = InValue.X * value1;
	q.Y = InValue.Y * value1;
	q.Z = InValue.Z * value1;
	q.W = InValue.W * value1;

	return q;
}

void FQuaternion::Conjugate()
{
	X = -X;
	Y = -Y;
	Z = -Z;
}

FQuaternion FQuaternion::Conjugate(FQuaternion InValue)
{
	FQuaternion quaternion;
	quaternion.X = -InValue.X;
	quaternion.Y = -InValue.Y;
	quaternion.Z = -InValue.Z;
	quaternion.W = InValue.W;

	return quaternion;
}

FQuaternion FQuaternion::Inverse(FQuaternion InValue)
{
	float value = InValue.X * InValue.X + InValue.Y * InValue.Y + InValue.Z * InValue.Z + InValue.W * InValue.W;
	float value1 = 1.0f / value;

	FQuaternion q;
	q.X = -InValue.X * value1;
	q.Y = -InValue.Y * value1;
	q.Z = -InValue.Z * value1;
	q.W = InValue.W * value1;

	return q;
}

FQuaternion FQuaternion::Add(FQuaternion InValue, FQuaternion InValue2)
{
	FQuaternion quaternion;
	quaternion.X = InValue.X + InValue2.X;
	quaternion.Y = InValue.Y + InValue2.Y;
	quaternion.Z = InValue.Z + InValue2.Z;
	quaternion.W = InValue.W + InValue2.W;

	return quaternion;
}

FQuaternion FQuaternion::Divide(FQuaternion InValue, FQuaternion InValue2)
{
	float x = InValue.X;
	float y = InValue.Y;
	float z = InValue.Z;
	float w = InValue.W;

	float value = InValue2.X * InValue2.X + InValue2.Y * InValue2.Y + InValue2.Z * InValue2.Z + InValue2.W * InValue2.W;
	float value1 = 1.0f / value;

	float x1 = -InValue2.X * value1;
	float y1 = -InValue2.Y * value1;
	float z1 = -InValue2.Z * value1;
	float w1 = InValue2.W * value1;

	float value2 = y * z1 - z * y1;
	float value3 = z * x1 - x * z1;
	float value4 = x * y1 - y * x1;
	float value5 = x * x1 + y * y1 + z * z1;

	FQuaternion quaternion;
	quaternion.X = x * w1 + x1 * w + value2;
	quaternion.Y = y * w1 + y1 * w + value3;
	quaternion.Z = z * w1 + z1 * w + value4;
	quaternion.W = w * w1 - value5;

	return quaternion;
}

FQuaternion FQuaternion::Multiply(FQuaternion InValue, FQuaternion InValue2)
{
	float x = InValue.X;
	float y = InValue.Y;
	float z = InValue.Z;
	float w = InValue.W;
	float value = InValue2.X;
	float y1 = InValue2.Y;
	float z1 = InValue2.Z;
	float w1 = InValue2.W;
	float value1 = y * z1 - z * y1;
	float value2 = z * value - x * z1;
	float value3 = x * y1 - y * value;
	float value4 = x * value + y * y1 + z * z1;

	FQuaternion quaternion;
	quaternion.X = x * w1 + value * w + value1;
	quaternion.Y = y * w1 + y1 * w + value2;
	quaternion.Z = z * w1 + z1 * w + value3;
	quaternion.W = w * w1 - value4;

	return quaternion;
}

FQuaternion FQuaternion::Multiply(FQuaternion InValue, float InValue2)
{
	FQuaternion quaternion;
	quaternion.X = InValue.X * InValue2;
	quaternion.Y = InValue.Y * InValue2;
	quaternion.Z = InValue.Z * InValue2;
	quaternion.W = InValue.W * InValue2;

	return quaternion;
}

FQuaternion FQuaternion::Subtract(FQuaternion InValue, FQuaternion InValue2)
{
	FQuaternion quaternion;
	quaternion.X = InValue.X - InValue2.X;
	quaternion.Y = InValue.Y - InValue2.Y;
	quaternion.Z = InValue.Z - InValue2.Z;
	quaternion.W = InValue.W - InValue2.W;

	return quaternion;
}

FQuaternion FQuaternion::Negative(FQuaternion InValue)
{
	FQuaternion x;
	x.X = -InValue.X;
	x.Y = -InValue.Y;
	x.Z = -InValue.Z;
	x.W = -InValue.W;

	return x;
}

FQuaternion FQuaternion::CreateFromAxisAngle(FVector InAxis, float InAngle)
{
	float value = InAngle * 0.5f;
	float value1 = sinf(value);
	float value2 = cosf(value);

	FQuaternion quaternion;
	quaternion.X = -InAxis.X * value1;
	quaternion.Y = -InAxis.Y * value1;
	quaternion.Z = -InAxis.Z * value1;
	quaternion.W = value2;

	return quaternion;
}

FQuaternion FQuaternion::CreateFromYawPitchRoll(float InYaw, float InPitch, float InRoll)
{
	float value = InRoll * 0.5f;
	float value1 = sinf(value);
	float value2 = cosf(value);

	float value3 = InPitch * 0.5f;
	float value4 = sinf(value3);
	float value5 = cosf(value3);

	float value6 = InYaw * 0.5f;
	float value7 = sinf(value6);
	float value8 = cosf(value6);

	FQuaternion quaternion;
	quaternion.X = value8 * value4 * value2 + value7 * value5 * value1;
	quaternion.Y = value7 * value5 * value2 - value8 * value4 * value1;
	quaternion.Z = value8 * value5 * value1 - value7 * value4 * value2;
	quaternion.W = value8 * value5 * value2 + value7 * value4 * value1;

	return quaternion;
}

FQuaternion FQuaternion::CreateFromRotationMatrix(FMatrix InMatrix)
{
	float m11 = InMatrix.M11 + InMatrix.M22 + InMatrix.M33;

	FQuaternion q;
	if (m11 > 0.0f)
	{
		float value = sqrtf((m11 + 1.0f));
		q.W = value * 0.5f;
		value = 0.5f / value;

		q.X = (InMatrix.M23 - InMatrix.M32) * value;
		q.Y = (InMatrix.M31 - InMatrix.M13) * value;
		q.Z = (InMatrix.M12 - InMatrix.M21) * value;
	}
	else if (InMatrix.M11 >= InMatrix.M22 && InMatrix.M11 >= InMatrix.M33)
	{
		float value1 = sqrtf((1.0f + InMatrix.M11 - InMatrix.M22 - InMatrix.M33));
		float value2 = 0.5f / value1;

		q.X = 0.5f * value1;
		q.Y = (InMatrix.M12 + InMatrix.M21) * value2;
		q.Z = (InMatrix.M13 + InMatrix.M31) * value2;
		q.W = (InMatrix.M23 - InMatrix.M32) * value2;
	}
	else if (InMatrix.M22 <= InMatrix.M33)
	{
		float value3 = sqrtf((1.0f + InMatrix.M33 - InMatrix.M11 - InMatrix.M22));
		float value4 = 0.5f / value3;

		q.X = (InMatrix.M31 + InMatrix.M13) * value4;
		q.Y = (InMatrix.M32 + InMatrix.M23) * value4;
		q.Z = 0.5f * value3;
		q.W = (InMatrix.M12 - InMatrix.M21) * value4;
	}
	else
	{
		float value5 = sqrtf((1.0f + InMatrix.M22 - InMatrix.M11 - InMatrix.M33));
		float value6 = 0.5f / value5;

		q.X = (InMatrix.M21 + InMatrix.M12) * value6;
		q.Y = 0.5f * value5;
		q.Z = (InMatrix.M32 + InMatrix.M23) * value6;
		q.W = (InMatrix.M31 - InMatrix.M13) * value6;
	}

	return q;
}

float FQuaternion::Dot(FQuaternion InValue, FQuaternion InValue2)
{
	return InValue.X * InValue2.X + InValue.Y * InValue2.Y + InValue.Z * InValue2.Z + InValue.W * InValue2.W;
}

FQuaternion FQuaternion::Slerp(FQuaternion InValue, FQuaternion InValue2, float InAmount)
{
	float value;
	float value1;
	float value2 = InAmount;

	bool flag = false;
	float x = InValue.X * InValue2.X + InValue.Y * InValue2.Y + InValue.Z * InValue2.Z + InValue.W * InValue2.W;
	if (x < 0.0f)
	{
		flag = true;
		x = -x;
	}
	if (x <= 0.999999f)
	{
		float value3 = acosf(x);
		float value4 = 1.0f / sinf(value3);
		value1 = sinf((1.0f - value2) * value3) * value4;
		value = flag ? -sinf(value2 * value3) * value4 : sinf(value2 * value3) * value4;
	}
	else
	{
		value1 = 1.0f - value2;
		value = (flag ? -value2 : value2);
	}

	FQuaternion quaternion;
	quaternion.X = value1 * InValue.X + value * InValue2.X;
	quaternion.Y = value1 * InValue.Y + value * InValue2.Y;
	quaternion.Z = value1 * InValue.Z + value * InValue2.Z;
	quaternion.W = value1 * InValue.W + value * InValue2.W;

	return quaternion;
}

FQuaternion FQuaternion::Lerp(FQuaternion InValue, FQuaternion InValue2, float InAmount)
{
	float value = InAmount;
	float value1 = 1.0f - value;

	FQuaternion q;
	if (InValue.X * InValue2.X + InValue.Y * InValue2.Y + InValue.Z * InValue2.Z + InValue.W * InValue2.W < 0.0f)
	{
		q.X = value1 * InValue.X - value * InValue2.X;
		q.Y = value1 * InValue.Y - value * InValue2.Y;
		q.Z = value1 * InValue.Z - value * InValue2.Z;
		q.W = value1 * InValue.W - value * InValue2.W;
	}
	else
	{
		q.X = value1 * InValue.X + value * InValue2.X;
		q.Y = value1 * InValue.Y + value * InValue2.Y;
		q.Z = value1 * InValue.Z + value * InValue2.Z;
		q.W = value1 * InValue.W + value * InValue2.W;
	}


	float q1 = q.X * q.X + q.Y * q.Y + q.Z * q.Z + q.W * q.W;
	float value2 = 1.0f / sqrtf(q1);

	q.X *= value2;
	q.Y *= value2;
	q.Z *= value2;
	q.W *= value2;

	return q;
}

FQuaternion FQuaternion::Concatenate(FQuaternion InValue, FQuaternion InValue2)
{
	float x1 = InValue.X;
	float y1 = InValue.Y;
	float z1 = InValue.Z;
	float w1 = InValue.W;

	float x2 = InValue2.X;
	float y2 = InValue2.Y;
	float z2 = InValue2.Z;
	float w2 = InValue2.W;

	FQuaternion quaternion;
	quaternion.X = w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2;
	quaternion.Y = w1 * y2 - x1 * z2 + y1 * w2 + z1 * x2;
	quaternion.Z = w1 * z2 + x1 * y2 - y1 * x2 + z1 * w2;
	quaternion.W = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2;

	return quaternion;
}
