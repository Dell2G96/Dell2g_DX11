#pragma once

class FMatrix;
class FQuaternion;
class FMath;

class FVector
{
public:
	FVector(void);
	FVector(float InValue);
	FVector(float InX, float InY, float InZ);

	operator float* ();
	operator const float* ();
	
	
	FVector operator -(void);

	bool operator ==(const FVector& InValue) const;
	bool operator !=(const FVector& InValue) const;

	FVector operator +(const FVector& InValue) const;
	FVector operator -(const FVector& InValue) const;
	FVector operator *(const FVector& InValue) const;
	FVector operator *(const float& InValue) const;
	FVector operator /(const FVector& InValue) const;
	FVector operator /(const float& InValue) const;

	void operator +=(const FVector& InValue);
	void operator -=(const FVector& InValue);
	void operator *=(const FVector& InValue);
	void operator *=(const float& InValue);
	void operator /=(const FVector& InValue);
	void operator /=(const float& InValue);

	friend FVector operator *(const float InValue, const FVector& InValue2)
	{
		return InValue * InValue2;
	}


	std::string ToString();

	float Length();
	float LengthSquared();

	void Normalize();

	static FVector Add(FVector InValue, FVector InValue2);
	static FVector Divide(FVector InValue, FVector InValue2);
	static FVector Divide(FVector InValue, float InValue2);
	static FVector Multiply(FVector InValue, FVector InValue2);
	static FVector Multiply(FVector InValue, float InValue2);
	static FVector Subtract(FVector InValue, FVector InValue2);

	static FVector Negative(FVector InValue);

	static float Distance(FVector InValue, FVector InValue2);
	static float DistanceSquared(FVector InValue, FVector InValue2);

	static float Dot(FVector InValue, FVector InValue2);
	static FVector Normalize(FVector InValue);

	static FVector Cross(FVector InValue, FVector InValue2);
	static FVector Reflect(FVector InValue, FVector InValue2);

	static FVector Min(FVector InValue, FVector InValue2);
	static FVector Max(FVector InValue, FVector InValue2);
	static FVector Clamp(FVector InValue, FVector InMin, FVector InMax);

	static FVector Lerp(FVector InValue, FVector InValue2, float InAmount);
	static FVector SmoothStep(FVector InValue, FVector InValue2, float InAmount);

	static FVector Transform(FVector InValue, FMatrix InMatrix);
	static FVector Transform(FVector InValue, FQuaternion InRotation);
	static FVector TransformNormal(FVector InValue, FMatrix InMatrix);
	static FVector TransformCoord(FVector InValue, FMatrix InMatrix);

public:
	const static FVector Zero;///< 0.0f, 0.0f, 0.0f
	const static FVector One;///< 1.0f, 1.0f, 1.0f

	const static FVector UnitX;///< 1.0f, 0.0f, 0.0f
	const static FVector UnitY;///< 0.0f, 1.0f, 0.0f
	const static FVector UnitZ;///< 0.0f, 0.0f, 1.0f

	const static FVector Up;///< 0.0f, 1.0f, 0.0f
	const static FVector Down;///< 0.0f, -1.0f, 0.0f
	const static FVector Right;///< 1.0f, 0.0f, 0.0f
	const static FVector Left;///< -1.0f, 0.0f, 0.0f
	const static FVector Forward;///< 0.0f, 0.0f, 1.0f
	const static FVector Backward;///< 0.0f, 0.0f, -1.0f

	union
	{
		struct
		{
			float X;
			float Y;
			float Z;
		};

		float V[3];
	};
	
};