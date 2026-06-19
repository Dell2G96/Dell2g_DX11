#pragma once

class FVector;
class FQuaternion;
class FPlane;

class FMatrix
{
public:
	FMatrix(void);
	FMatrix(float InValue11, float InValue12, float InValue13, float InValue14, float InValue21, float InValue22, float InValue23, float InValue24, float InValue31, float InValue32, float InValue33, float InValue34, float InValue41, float InValue42, float InValue43, float InValue44);

	FVector Up();			void Up(FVector InValue);
	FVector Down();			void Down(FVector InValue);
	FVector Right();		void Right(FVector InValue);
	FVector Left();			void Left(FVector InValue);
	FVector Forward();		void Forward(FVector InValue);
	FVector Backward();		void Backward(FVector InValue);
	FVector Translate();	void Translate(FVector InValue);


	operator float* ();
	operator const float* ();

	FMatrix operator -();

	bool operator ==(const FMatrix& InValue) const;
	bool operator !=(const FMatrix& InValue) const;

	FMatrix operator +(const FMatrix& InValue) const;
	FMatrix operator -(const FMatrix& InValue) const;
	FMatrix operator *(const FMatrix& InValue) const;
	FMatrix operator *(const float& InValue) const;
	FMatrix operator /(const FMatrix& InValue) const;
	FMatrix operator /(const float& InValue) const;

	void operator +=(const FMatrix& InValue);
	void operator -=(const FMatrix& InValue);
	void operator *=(const FMatrix& InValue);
	void operator *=(const float& InValue);
	void operator /=(const FMatrix& InValue);
	void operator /=(const float& divider);

	friend FMatrix operator *(const float InValue, const FMatrix& InValue2)
	{
		return InValue * InValue2;
	}
	
	std::string ToString();
	std::string ToStringRow1();
	std::string ToStringRow2();
	std::string ToStringRow3();
	std::string ToStringRow4();

	
	float Determinant();

	static FMatrix Add(FMatrix InValue, FMatrix InValue2);
	static FMatrix Divide(FMatrix InValue, FMatrix InValue2);
	static FMatrix Divide(FMatrix InValue, float InValue2);
	static FMatrix Multiply(FMatrix InValue, FMatrix InValue2);
	static FMatrix Multiply(FMatrix InValue, float InValue2);

	static FMatrix Negative(FMatrix InValue);

	static FMatrix CreateTranslation(FVector InValue);

	static FMatrix CreateScale(FVector InValue);
	static FMatrix CreateScale(float InValue);

	static FMatrix CreateRotationX(float InValue);
	static FMatrix CreateRotationY(float InValue);
	static FMatrix CreateRotationZ(float InValue);
	static FMatrix CreateFromAxisAngle(FVector InAxis, float InAngle);

	static FMatrix CreatePerspective(float InWidth, float InHeight, float InNear, float InFar);
	static FMatrix CreatePerspectiveFieldOfView(float InFOV, float InAspectRatio, float InNear, float InFar);
	static FMatrix CreatePerspectiveOffCenter(float InLeft, float InRight, float InBottom, float InTop, float InNear, float InFar);

	static FMatrix CreateLookAt(FVector InPosition, FVector InTarget, FVector InUp);
	static FMatrix CreateFromQuaternion(FQuaternion InValue);
	static FMatrix CreateFromYawPitchRoll(float InYaw, float InPitch, float InRoll);

	static FMatrix CreateOrthographic(float InWidth, float InHeight, float InNear, float InFar);
	static FMatrix CreateOrthographicOffCenter(float InLeft, float InRight, float InBottom, float InTop, float InNear, float InFar);

	static FMatrix Transform(FMatrix InValue, FQuaternion InRotation);
	static FMatrix Transpose(FMatrix InValue);
	static FMatrix Invert(FMatrix InValue);
	static FMatrix Lerp(FMatrix InValue, FMatrix InValue2, float InAmount);

	const static FMatrix Identity;

public:
	union
	{
		struct
		{
			float M11; float M12; float M13; float M14;
			float M21; float M22; float M23; float M24;
			float M31; float M32; float M33; float M34;
			float M41; float M42; float M43; float M44;
		};

		float M[16];
		float M2[4][4];
	};
};