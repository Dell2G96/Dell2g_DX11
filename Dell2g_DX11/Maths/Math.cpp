#include "Framework.h"
#include "Math.h"

const float FMath::E = 2.71828175f;
const float FMath::Log2E = 1.442695f;
const float FMath::Log10E = 0.4342945f;
const float FMath::Pi = 3.14159274f;
const float FMath::TwoPi = 6.28318548f;
const float FMath::PiOver2 = 1.57079637f;
const float FMath::PiOver4 = 0.7853982f;

#pragma warning( disable : 4146)
const int FMath::IntMinValue = -2147483648;
const int FMath::IntMaxValue = 2147483647;
const float FMath::FloatMinValue = -3.402823E+38f;
const float FMath::FloatMaxValue = 3.402823E+38f;
#pragma warning( default : 4146)

const float FMath::Epsilon = 1e-6f;


float FMath::Distance(float InValue1, float InValue2)
{
	return fabsf(InValue1 - InValue2);
}

float FMath::Hermite(float InValue1, float InTangent1, float InValue2, float InTangent2, float InAmount)
{
	float single = InAmount;

	float single1 = single * single;
	float single2 = single * single1;
	float single3 = 2.0f * single2 - 3.0f * single1 + 1.0f;
	float single4 = -2.0f * single2 + 3.0f * single1;
	float single5 = single2 - 2.0f * single1 + single;
	float single6 = single2 - single1;

	return InValue1 * single3 + InValue2 * single4 + InTangent1 * single5 + InTangent2 * single6;
}

float FMath::Lerp(float InValue1, float InValue2, float InAmount)
{
	return InValue1 + (InValue2 - InValue1) * InAmount;
}

float FMath::Max(float InValue1, float InValue2)
{
	return max(InValue1, InValue2);
}

float FMath::Min(float InValue1, float InValue2)
{
	return min(InValue1, InValue2);
}

float FMath::Round(float InValue)
{
	return Round(InValue, 0);
}

float FMath::Round(float InValue, int InPosition)
{
	float temp;
	temp = InValue * powf(10.0f, (float)InPosition);
	temp = floorf(temp + 0.5f);
	temp *= powf(10.0f, -(float)InPosition);

	return temp;
}

float FMath::SmoothStep(float InValue)
{
	return (InValue <= 0) ? 0
		: (InValue >= 1) ? 1
		: InValue * InValue * (3 - (2 * InValue));
}

float FMath::SmoothStep(float InValue1, float InValue2, float InAmount)
{
	float single = Clamp(InAmount, 0.0f, 1.0f);

	return Lerp(InValue1, InValue2, single * single * (3.0f - 2.0f * single));
}

float FMath::SmootherStep(float InAmount)
{
	return (InAmount <= 0) ? 0
		: (InAmount >= 1) ? 1
		: InAmount * InAmount * InAmount * (InAmount * ((InAmount * 6) - 15) + 10);
}

float FMath::ToDegrees(float InRadians)
{
	return InRadians * 57.2957764f; //180 / pi
}

float FMath::ToRadians(float InDegrees)
{
	return InDegrees * 0.0174532924f; //pi / 180
}

float FMath::WrapAngle(float InAngle)
{
	InAngle = fmodf(InAngle, 360.0f);

	if (InAngle <= -180.0f)
	{
		InAngle += 360.0f;
	}
	else if (InAngle > 180.0f)
	{
		InAngle -= 360.0f;
	}

	return InAngle;
}

bool FMath::IsZero(float InValue)
{
	return fabs(InValue) < Epsilon;
}

bool FMath::IsOne(float InValue)
{
	return IsZero(InValue - 1.0f);
}

bool FMath::NearEqual(float InValue1, float InValue2)
{
	if (IsZero(InValue1 - InValue2))
		return true;

	int aInt = *(int*)&InValue1;
	int bInt = *(int*)&InValue2;

	if ((aInt < 0) != (bInt < 0))
		return false;

	int ulp = abs(aInt - bInt);
	const int maxUlp = 4;

	return (ulp <= maxUlp);
}

bool FMath::WithinEpsilon(float InValue1, float InValue2)
{
	float num = InValue1 - InValue2;

	return ((-Epsilon <= num) && (num <= Epsilon));
}

bool FMath::WithinEpsilon(float InValue1, float InValue2, float InEpsilon)
{
	float num = InValue1 - InValue2;

	return ((-InEpsilon <= num) && (num <= InEpsilon));
}

float FMath::Gauss(float InAmplitude, float InX, float InY, float InCenterX, float InCenterY, float InSigmaX, float InSigmaY)
{
	float cx = InX - InCenterX;
	float cy = InY - InCenterY;

	float componentX = (cx * cx) / (2 * InSigmaX * InSigmaX);
	float componentY = (cy * cy) / (2 * InSigmaY * InSigmaY);

	return InAmplitude * expf(-(componentX + componentY));
}

int FMath::Random(int InMin, int InMax)
{
	return (int)(rand() % (InMax - InMin + 1)) + InMin;
}

float FMath::Random(float InMin, float InMax)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = InMax - InMin;
	float val = random * diff;

	return InMin + val;
}

