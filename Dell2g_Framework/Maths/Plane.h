#pragma once

class FVector4;
class FMatrix;
class FQuaternion;

class FPlane
{
public:
	FPlane(void);
	FPlane(float InA, float InB, float InC, float InD);
	FPlane(FVector& InNormal, float InD);
	FPlane(FVector4& InValue);
	FPlane(FVector& InPoint1, FVector& InPoint2, FVector& InPoint3);


	operator float* ();
	operator const float* ();

	bool operator ==(const FPlane& InValue) const;
	bool operator !=(const FPlane& InValue) const;

	std::string ToString();
	

	float Dot(FVector4& InValue);
	float DotCoordinate(FVector& InValue);
	float DotNormal(FVector& InValue);

	void Normalize();
	static FPlane Normalize(FPlane& InValue);

	static FPlane Transform(FPlane& InPlane, FMatrix& InMatrix);
	static FPlane Transform(FPlane& InPlane, FQuaternion& InRotation);

public:
	union
	{
		struct
		{
			FVector Normal;
			float D;
		};

		float P[4];
	};
	
};