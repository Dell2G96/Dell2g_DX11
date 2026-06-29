#pragma once

class FMatrix;
class FQuaternion;

//////////////////////////////////////////////////////////////////////////
///@brief 2D บคลอ
//////////////////////////////////////////////////////////////////////////
class FVector2D
{
public:
	FVector2D(void);
	FVector2D(float InValue);
	FVector2D(float InX, float InY);

	operator float* ();
	operator const float* ();

	FVector2D operator -(void);

	bool operator ==(const FVector2D& InValue) const;
	bool operator !=(const FVector2D& InValue) const;

	FVector2D operator +(const FVector2D& InValue) const;
	FVector2D operator -(const FVector2D& InValue) const;
	FVector2D operator *(const FVector2D& InValue) const;
	FVector2D operator *(const float& InValue) const;
	FVector2D operator /(const FVector2D& InValue) const;
	FVector2D operator /(const float& InValue) const;

	void operator +=(const FVector2D& InValue);
	void operator -=(const FVector2D& InValue);
	void operator *=(const FVector2D& InValue);
	void operator *=(const float& InValue);
	void operator /=(const FVector2D& InValue);
	void operator /=(const float& InValue);


	friend FVector2D operator *(const float InValue, const FVector2D& InValue2)
	{
		return InValue * InValue2;
	}
	//////////////////////////////////////////////////////////////////////////


	std::string ToString();

	float Length();
	float LengthSquared();

	void Normalize();

	static FVector2D Add(FVector2D InValue1, FVector2D InValue2);
	static FVector2D Divide(FVector2D InValue1, FVector2D InValue2);
	static FVector2D Divide(FVector2D InValue1, float InValue2);
	static FVector2D Multiply(FVector2D InValue1, FVector2D InValue2);
	static FVector2D Multiply(FVector2D InValue1, float InValue2);
	static FVector2D Subtract(FVector2D InValue1, FVector2D InValue2);

	static FVector2D Negative(FVector2D InValue);

	static float Distance(FVector2D InValue1, FVector2D InValue2);
	static float DistanceSquared(FVector2D InValue1, FVector2D InValue2);

	static float Dot(FVector2D InValue1, FVector2D InValue2);
	static FVector2D Normalize(FVector2D InValue);

	static FVector2D Reflect(FVector2D InValue, FVector2D InNormal);

	static FVector2D Min(FVector2D InValue1, FVector2D InValue2);
	static FVector2D Max(FVector2D InValue1, FVector2D InValue2);
	static FVector2D Clamp(FVector2D InValue1, FVector2D InMin, FVector2D InMax);

	static FVector2D Lerp(FVector2D InValue1, FVector2D InValue2, float InAmount);
	static FVector2D SmoothStep(FVector2D InValue1, FVector2D InValue2, float InAmount);

	static FVector2D Transform(FVector2D InValue, FMatrix InMatrix);
	static FVector2D Transform(FVector2D InValue, FQuaternion InRotation);
	static FVector2D TransformNormal(FVector2D InValue, FMatrix InMatrix);

public:
	const static FVector2D Zero;///< 0.0f, 0.0f
	const static FVector2D One;///< 1.0f, 1.0f

	const static FVector2D UnitX;///< 1.0f, 0.0f
	const static FVector2D UnitY;///< 0.0f, 1.0f

	union
	{
		struct
		{
			float X;
			float Y;
		};

		float V[2];
	};
};