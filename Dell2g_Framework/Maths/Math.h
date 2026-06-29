#pragma once

class FMath
{
public:
	static float Distance(float InValue1, float InValue2);
	static float Hermite(float InValue1, float InTangent1, float InValue2, float InTangent2, float InAmount);
	static float Lerp(float InValue1, float InValue2, float InAmount);
	static float Max(float InValue1, float InValue2);
	static float Min(float InValue1, float InValue2);
	static float Round(float InValue);
	static float Round(float InValue, int InPosition);
	static float SmoothStep(float InValue);
	static float SmoothStep(float InValue1, float InValue2, float InAmount);
	static float SmootherStep(float InAmount);
	static float ToDegrees(float InRadians);
	static float ToRadians(float InDegrees);
	static float WrapAngle(float InAngle);
	
	static bool IsZero(float InValue);
	static bool IsOne(float InValue);

	static bool NearEqual(float InValue1, float InValue2);
	static bool WithinEpsilon(float InValue1, float InValue2);
	static bool WithinEpsilon(float InValue1, float InValue2, float InEpsilon);

	static float Gauss(float InAmplitude, float InX, float InY, float InCenterX, float InCenterY, float InSigmaX, float InSigmaY);


	template<typename T>
	static T Clamp(T value, T min, T max)
	{
		value = (value > max ? max : value);
		value = (value < min ? min : value);

		return value;
	}

	static int Random(int InMin, int InMax);
	static float Random(float InMin, float InMax);

public:
	const static float E;
	const static float Log2E;
	const static float Log10E;
	const static float Pi;
	const static float TwoPi;
	const static float PiOver2;
	const static float PiOver4;
	const static float Epsilon;

	const static int IntMinValue;
	const static int IntMaxValue;
	const static float FloatMinValue;
	const static float FloatMaxValue;
};