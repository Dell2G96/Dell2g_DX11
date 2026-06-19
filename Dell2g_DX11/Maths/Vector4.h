#pragma once

class FVector2D;
class FVector;
class FMatrix;
class FQuaternion;

class FVector4
{
public:
	FVector4(void);
	FVector4(float InX, float InY, float InZ, float InW);
	FVector4(FVector2D InValue, float InZ, float InW);
	FVector4(FVector InValue, float InW);
	FVector4(float InValue);

	
	operator float* ();
	operator const float* ();

	FVector4 operator -(void);

	bool operator ==(const FVector4& InValue) const;
	bool operator !=(const FVector4& InValue) const;

	FVector4 operator +(const FVector4& InValue) const;
	FVector4 operator -(const FVector4& InValue) const;
	FVector4 operator *(const FVector4& InValue) const;
	FVector4 operator *(const float& InValue) const;
	FVector4 operator /(const FVector4& InValue) const;
	FVector4 operator /(const float& InValue) const;

	void operator +=(const FVector4& InValue);
	void operator -=(const FVector4& InValue);
	void operator *=(const FVector4& InValue);
	void operator *=(const float& InValue);
	void operator /=(const FVector4& InValue);
	void operator /=(const float& InValue);

	friend FVector4 operator *(const float InValue, const FVector4& InValue2)
	{
		return InValue * InValue2;
	}


	std::string ToString();

	float Length();
	float LengthSquared();

	void Normalize();

	static FVector4 Add(FVector4 InValue, FVector4 InValue2);
	static FVector4 Divide(FVector4 InValue, FVector4 InValue2);
	static FVector4 Divide(FVector4 InValue, float InValue2);
	static FVector4 Multiply(FVector4 InValue, FVector4 InValue2);
	static FVector4 Multiply(FVector4 InValue, float InValue2);
	static FVector4 Subtract(FVector4 InValue, FVector4 InValue2);

	static FVector4 Negative(FVector4 InValue);

	static float Distance(FVector4 InValue, FVector4 InValue2);
	static float DistanceSquared(FVector4 InValue, FVector4 InValue2);

	static float Dot(FVector4 InValue, FVector4 InValue2);
	static FVector4 Normalize(FVector4 InValue);

	static FVector4 Min(FVector4 InValue, FVector4 InValue2);
	static FVector4 Max(FVector4 InValue, FVector4 InValue2);
	static FVector4 Clamp(FVector4 InValue, FVector4 InMin, FVector4 InMax);

	static FVector4 Lerp(FVector4 InValue, FVector4 InValue2, float InAmount);
	static FVector4 SmoothStep(FVector4 InValue, FVector4 InValue2, float InAmount);

	static FVector4 Transform(FVector2D InValue, FMatrix InMatrix);
	static FVector4 Transform(FVector InValue, FMatrix InMatrix);
	static FVector4 Transform(FVector4 InValue, FMatrix InMatrix);

	static FVector4 Transform(FVector2D value, FQuaternion InRotation);
	static FVector4 Transform(FVector value, FQuaternion InRotation);
	static FVector4 Transform(FVector4 value, FQuaternion InRotation);

public:
	const static FVector4 Zero;///< 0.0f, 0.0f, 0.0f, 0.0f
	const static FVector4 One;///< 1.0f, 1.0f, 1.0f, 1.0f

	const static FVector4 UnitX;///< 1.0f, 0.0f, 0.0f, 0.0f
	const static FVector4 UnitY;///< 0.0f, 1.0f, 0.0f, 0.0f
	const static FVector4 UnitZ;///< 0.0f, 0.0f, 1.0f, 0.0f
	const static FVector4 UnitW;///< 0.0f, 0.0f, 1.0f, 1.0f

	union
	{
		struct
		{
			float X;///< X
			float Y;///< Y
			float Z;///< Z
			float W;///< W
		};

		float V[4];
	};
};