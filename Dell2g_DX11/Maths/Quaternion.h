#pragma once

class FVector;
class FMatrix;

class FQuaternion
{
public:
	FQuaternion(void);
	FQuaternion(float InX, float InY, float InZ, float InW);
	FQuaternion(FVector InValue, float InValue2);


	operator float* ();
	operator const float* ();

	FQuaternion operator -(void);

	bool operator ==(const FQuaternion& InValue) const;
	bool operator !=(const FQuaternion& InValue) const;

	FQuaternion operator +(const FQuaternion& InValue) const;
	FQuaternion operator -(const FQuaternion& InValue) const;
	FQuaternion operator *(const FQuaternion& InValue) const;
	FQuaternion operator *(const float& InValue) const;
	FQuaternion operator /(const FQuaternion& InValue) const;

	void operator +=(const FQuaternion& InValue);
	void operator -=(const FQuaternion& InValue);
	void operator *=(const FQuaternion& InValue);
	void operator *=(const float& InValue);
	void operator /=(const FQuaternion& InValue);

	friend FQuaternion operator *(const float InValue, const FQuaternion& InValue2)
	{
		return InValue * InValue2;
	}


	std::string ToString();

	float Length();
	float LengthSquared();

	void Normalize();
	static FQuaternion Normalize(FQuaternion InValue);

	void Conjugate();
	static FQuaternion Conjugate(FQuaternion InValue);
	static FQuaternion Inverse(FQuaternion InValue);

	static FQuaternion Add(FQuaternion InValue, FQuaternion InValue2);
	static FQuaternion Divide(FQuaternion InValue, FQuaternion InValue2);
	static FQuaternion Multiply(FQuaternion InValue, FQuaternion InValue2);
	static FQuaternion Multiply(FQuaternion InValue, float InValue2);
	static FQuaternion Subtract(FQuaternion InValue, FQuaternion InValue2);

	static FQuaternion Negative(FQuaternion InValue);

	static FQuaternion CreateFromAxisAngle(FVector InAxis, float InAngle);
	static FQuaternion CreateFromYawPitchRoll(float InYaw, float InPitch, float InRoll);
	static FQuaternion CreateFromRotationMatrix(FMatrix InMatrix);

	static float Dot(FQuaternion InValue, FQuaternion InValue2);

	static FQuaternion Slerp(FQuaternion InValue, FQuaternion InValue2, float InAmount);
	static FQuaternion Lerp(FQuaternion InValue, FQuaternion InValue2, float InAmount);

	static FQuaternion Concatenate(FQuaternion InValue, FQuaternion InValue2);

public:
	const static FQuaternion Identity;

	union
	{
		struct
		{
			float X;
			float Y;
			float Z;
			float W;
		};

		float Q[4];
	};
};