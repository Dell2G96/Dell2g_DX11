#include "Framework.h"
#include "Matrix.h"

const FMatrix FMatrix::Identity = FMatrix
(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f, 
	0.0f, 0.0f, 1.0f, 0.0f, 
	0.0f, 0.0f, 0.0f, 1.0f
);


FMatrix::FMatrix(void)
{
	M11 = 0.0f; M12 = 0.0f; M13 = 0.0f; M14 = 0.0f;
	M21 = 0.0f; M22 = 0.0f; M23 = 0.0f; M24 = 0.0f;
	M31 = 0.0f; M32 = 0.0f; M33 = 0.0f; M34 = 0.0f;
	M41 = 0.0f; M42 = 0.0f; M43 = 0.0f; M44 = 0.0f;
}

FMatrix::FMatrix(float InValue11, float InValue12, float InValue13, float InValue14, float InValue21, float InValue22, float InValue23, float InValue24, float InValue31, float InValue32, float InValue33, float InValue34, float InValue41, float InValue42, float InValue43, float InValue44)
{
	M11 = InValue11; M12 = InValue12; M13 = InValue13; M14 = InValue14;
	M21 = InValue21; M22 = InValue22; M23 = InValue23; M24 = InValue24;
	M31 = InValue31; M32 = InValue32; M33 = InValue33; M34 = InValue34;
	M41 = InValue41; M42 = InValue42; M43 = InValue43; M44 = InValue44;
}

FVector FMatrix::Up()
{
	FVector vector;
	vector.X = M21; vector.Y = M22; vector.Z = M23;

	return vector;
}

void FMatrix::Up(FVector InValue)
{
	M21 = InValue.X; M22 = InValue.Y; M23 = InValue.Z;
}

FVector FMatrix::Down()
{
	FVector vector;
	vector.X = -M21; vector.Y = -M22; vector.Z = -M23;

	return vector;
}

void FMatrix::Down(FVector InValue)
{
	M21 = -InValue.X; M22 = -InValue.Y; M23 = -InValue.Z;
}

FVector FMatrix::Right()
{
	FVector vector;
	vector.X = M11; vector.Y = M12; vector.Z = M13;

	return vector;
}
//////////////////////////////////////////////////////////////////////////


void FMatrix::Right(FVector InValue)
{
	M11 = InValue.X; M12 = InValue.Y; M13 = InValue.Z;
}

FVector FMatrix::Left()
{
	FVector vector;
	vector.X = -M11; vector.Y = -M12; vector.Z = -M13;

	return vector;
}

void FMatrix::Left(FVector InValue)
{
	M11 = -InValue.X; M12 = -InValue.Y; M13 = -InValue.Z;
}

FVector FMatrix::Forward()
{
	FVector vector;
	vector.X = M31; vector.Y = M32; vector.Z = M33;

	return vector;
}

void FMatrix::Forward(FVector InValue)
{
	M31 = InValue.X; M32 = InValue.Y; M33 = InValue.Z;
}

FVector FMatrix::Backward()
{
	FVector vector;
	vector.X = -M31; vector.Y = -M32; vector.Z = -M33;

	return vector;
}

void FMatrix::Backward(FVector InValue)
{
	M31 = -InValue.X; M32 = -InValue.Y; M33 = -InValue.Z;
}

FVector FMatrix::Translate()
{
	FVector vector;
	vector.X = M41; vector.Y = M42; vector.Z = M43;

	return vector;
}

void FMatrix::Translate(FVector InValue)
{
	M41 = InValue.X; M42 = InValue.Y; M43 = InValue.Z;
}

FMatrix::operator float* ()
{
	return M;
}

FMatrix::operator const float* ()
{
	return M;
}

FMatrix FMatrix::operator-()
{
	FMatrix matrix;
	matrix.M11 = -M11; matrix.M12 = -M12; matrix.M13 = -M13; matrix.M14 = -M14;
	matrix.M21 = -M21; matrix.M22 = -M22; matrix.M23 = -M23; matrix.M24 = -M24;
	matrix.M31 = -M31; matrix.M32 = -M32; matrix.M33 = -M33; matrix.M34 = -M34;
	matrix.M41 = -M41; matrix.M42 = -M42; matrix.M43 = -M43; matrix.M44 = -M44;

	return matrix;
}

bool FMatrix::operator==(const FMatrix& InValue) const
{
	if (M11 == InValue.M11 && M22 == InValue.M22 && (M33 == InValue.M33 && M44 == InValue.M44) && (M12 == InValue.M12 && M13 == InValue.M13 && (M14 == InValue.M14 && M21 == InValue.M21)) && (M23 == InValue.M23 && M24 == InValue.M24 && (M31 == InValue.M31 && M32 == InValue.M32) && (M34 == InValue.M34 && M41 == InValue.M41 && M42 == InValue.M42)))
		return M43 == InValue.M43;
	else
		return false;
}

bool FMatrix::operator!=(const FMatrix& InValue) const
{
	if (M11 == InValue.M11 && M12 == InValue.M12 && (M13 == InValue.M13 && M14 == InValue.M14) && (M21 == InValue.M21 && M22 == InValue.M22 && (M23 == InValue.M23 && M24 == InValue.M24)) && (M31 == InValue.M31 && M32 == InValue.M32 && (M33 == InValue.M33 && M34 == InValue.M34) && (M41 == InValue.M41 && M42 == InValue.M42 && M43 == InValue.M43)))
		return M44 != InValue.M44;
	else
		return true;
}

FMatrix FMatrix::operator+(const FMatrix& InValue) const
{
	FMatrix matrix;
	matrix.M11 = M11 + InValue.M11; matrix.M12 = M12 + InValue.M12; matrix.M13 = M13 + InValue.M13; matrix.M14 = M14 + InValue.M14;
	matrix.M21 = M21 + InValue.M21; matrix.M22 = M22 + InValue.M22; matrix.M23 = M23 + InValue.M23; matrix.M24 = M24 + InValue.M24;
	matrix.M31 = M31 + InValue.M31; matrix.M32 = M32 + InValue.M32; matrix.M33 = M33 + InValue.M33; matrix.M34 = M34 + InValue.M34;
	matrix.M41 = M41 + InValue.M41; matrix.M42 = M42 + InValue.M42; matrix.M43 = M43 + InValue.M43; matrix.M44 = M44 + InValue.M44;

	return matrix;
}

FMatrix FMatrix::operator-(const FMatrix& InValue) const
{
	FMatrix matrix;
	matrix.M11 = M11 - InValue.M11; matrix.M12 = M12 - InValue.M12; matrix.M13 = M13 - InValue.M13; matrix.M14 = M14 - InValue.M14;
	matrix.M21 = M21 - InValue.M21; matrix.M22 = M22 - InValue.M22; matrix.M23 = M23 - InValue.M23; matrix.M24 = M24 - InValue.M24;
	matrix.M31 = M31 - InValue.M31; matrix.M32 = M32 - InValue.M32; matrix.M33 = M33 - InValue.M33; matrix.M34 = M34 - InValue.M34;
	matrix.M41 = M41 - InValue.M41; matrix.M42 = M42 - InValue.M42; matrix.M43 = M43 - InValue.M43; matrix.M44 = M44 - InValue.M44;

	return matrix;
}

FMatrix FMatrix::operator*(const FMatrix& InValue) const
{
	FMatrix matrix;
	matrix.M11 = (M11 * InValue.M11 + M12 * InValue.M21 + M13 * InValue.M31 + M14 * InValue.M41);
	matrix.M12 = (M11 * InValue.M12 + M12 * InValue.M22 + M13 * InValue.M32 + M14 * InValue.M42);
	matrix.M13 = (M11 * InValue.M13 + M12 * InValue.M23 + M13 * InValue.M33 + M14 * InValue.M43);
	matrix.M14 = (M11 * InValue.M14 + M12 * InValue.M24 + M13 * InValue.M34 + M14 * InValue.M44);
	matrix.M21 = (M21 * InValue.M11 + M22 * InValue.M21 + M23 * InValue.M31 + M24 * InValue.M41);
	matrix.M22 = (M21 * InValue.M12 + M22 * InValue.M22 + M23 * InValue.M32 + M24 * InValue.M42);
	matrix.M23 = (M21 * InValue.M13 + M22 * InValue.M23 + M23 * InValue.M33 + M24 * InValue.M43);
	matrix.M24 = (M21 * InValue.M14 + M22 * InValue.M24 + M23 * InValue.M34 + M24 * InValue.M44);
	matrix.M31 = (M31 * InValue.M11 + M32 * InValue.M21 + M33 * InValue.M31 + M34 * InValue.M41);
	matrix.M32 = (M31 * InValue.M12 + M32 * InValue.M22 + M33 * InValue.M32 + M34 * InValue.M42);
	matrix.M33 = (M31 * InValue.M13 + M32 * InValue.M23 + M33 * InValue.M33 + M34 * InValue.M43);
	matrix.M34 = (M31 * InValue.M14 + M32 * InValue.M24 + M33 * InValue.M34 + M34 * InValue.M44);
	matrix.M41 = (M41 * InValue.M11 + M42 * InValue.M21 + M43 * InValue.M31 + M44 * InValue.M41);
	matrix.M42 = (M41 * InValue.M12 + M42 * InValue.M22 + M43 * InValue.M32 + M44 * InValue.M42);
	matrix.M43 = (M41 * InValue.M13 + M42 * InValue.M23 + M43 * InValue.M33 + M44 * InValue.M43);
	matrix.M44 = (M41 * InValue.M14 + M42 * InValue.M24 + M43 * InValue.M34 + M44 * InValue.M44);

	return matrix;
}

FMatrix FMatrix::operator*(const float& InValue) const
{
	float num = InValue;
	FMatrix matrix1;

	matrix1.M11 = M11 * num; matrix1.M12 = M12 * num; matrix1.M13 = M13 * num; matrix1.M14 = M14 * num;
	matrix1.M21 = M21 * num; matrix1.M22 = M22 * num; matrix1.M23 = M23 * num; matrix1.M24 = M24 * num;
	matrix1.M31 = M31 * num; matrix1.M32 = M32 * num; matrix1.M33 = M33 * num; matrix1.M34 = M34 * num;
	matrix1.M41 = M41 * num; matrix1.M42 = M42 * num; matrix1.M43 = M43 * num; matrix1.M44 = M44 * num;

	return matrix1;
}

FMatrix FMatrix::operator/(const FMatrix& InValue) const
{
	FMatrix matrix;
	matrix.M11 = M11 / InValue.M11; matrix.M12 = M12 / InValue.M12; matrix.M13 = M13 / InValue.M13; matrix.M14 = M14 / InValue.M14;
	matrix.M21 = M21 / InValue.M21; matrix.M22 = M22 / InValue.M22; matrix.M23 = M23 / InValue.M23; matrix.M24 = M24 / InValue.M24;
	matrix.M31 = M31 / InValue.M31; matrix.M32 = M32 / InValue.M32; matrix.M33 = M33 / InValue.M33; matrix.M34 = M34 / InValue.M34;
	matrix.M41 = M41 / InValue.M41; matrix.M42 = M42 / InValue.M42; matrix.M43 = M43 / InValue.M43; matrix.M44 = M44 / InValue.M44;

	return matrix;
}

FMatrix FMatrix::operator/(const float& InValue) const
{
	float num = 1.0f / InValue;

	FMatrix matrix;
	matrix.M11 = M11 * num; matrix.M12 = M12 * num; matrix.M13 = M13 * num; matrix.M14 = M14 * num;
	matrix.M21 = M21 * num; matrix.M22 = M22 * num; matrix.M23 = M23 * num; matrix.M24 = M24 * num;
	matrix.M31 = M31 * num; matrix.M32 = M32 * num; matrix.M33 = M33 * num; matrix.M34 = M34 * num;
	matrix.M41 = M41 * num; matrix.M42 = M42 * num; matrix.M43 = M43 * num; matrix.M44 = M44 * num;

	return matrix;
}

void FMatrix::operator+=(const FMatrix& InValue)
{
	*this = *this + InValue;
}

void FMatrix::operator-=(const FMatrix& InValue)
{
	*this = *this - InValue;
}

void FMatrix::operator*=(const FMatrix& InValue)
{
	*this = *this * InValue;
}

void FMatrix::operator*=(const float& InValue)
{
	*this = *this * InValue;
}

void FMatrix::operator/=(const FMatrix& InValue)
{
	*this = *this / InValue;
}

void FMatrix::operator/=(const float& InValue)
{
	*this = *this / InValue;
}

std::string FMatrix::ToString()
{
	std::string temp = "";

	temp += ToStringRow1();
	temp += "," + ToStringRow2();
	temp += "," + ToStringRow3();
	temp += "," + ToStringRow4();

	return temp;
}

std::string FMatrix::ToStringRow1()
{
	std::string temp = "";

	temp += std::to_string(M11);
	temp += "," + std::to_string(M12);
	temp += "," + std::to_string(M13);
	temp += "," + std::to_string(M14);

	return temp;
}

std::string FMatrix::ToStringRow2()
{
	std::string temp = "";

	temp += std::to_string(M21);
	temp += "," + std::to_string(M22);
	temp += "," + std::to_string(M23);
	temp += "," + std::to_string(M24);

	return temp;
}

std::string FMatrix::ToStringRow3()
{
	std::string temp = "";

	temp += std::to_string(M31);
	temp += "," + std::to_string(M32);
	temp += "," + std::to_string(M33);
	temp += "," + std::to_string(M34);

	return temp;
}

std::string FMatrix::ToStringRow4()
{
	std::string temp = "";

	temp += std::to_string(M41);
	temp += "," + std::to_string(M42);
	temp += "," + std::to_string(M43);
	temp += "," + std::to_string(M44);

	return temp;
}

float FMatrix::Determinant()
{
	float value1 = M33 * M44 - M34 * M43;
	float value2 = M32 * M44 - M34 * M42;
	float value3 = M32 * M43 - M33 * M42;
	float value4 = M31 * M44 - M34 * M41;
	float value5 = M31 * M43 - M33 * M41;
	float value6 = M31 * M42 - M32 * M41;

	float temp =
		M11 * (M22 * value1 - M23 * value2 + M24 * value3) -
		M12 * (M21 * value1 - M23 * value4 + M24 * value5) +
		M13 * (M21 * value2 - M22 * value4 + M24 * value6) -
		M14 * (M21 * value3 - M22 * value5 + M23 * value6);

	return temp;
}

FMatrix FMatrix::Add(FMatrix InValue, FMatrix InValue2)
{
	FMatrix matrix;
	matrix.M11 = InValue.M11 + InValue2.M11;
	matrix.M12 = InValue.M12 + InValue2.M12;
	matrix.M13 = InValue.M13 + InValue2.M13;
	matrix.M14 = InValue.M14 + InValue2.M14;
	matrix.M21 = InValue.M21 + InValue2.M21;
	matrix.M22 = InValue.M22 + InValue2.M22;
	matrix.M23 = InValue.M23 + InValue2.M23;
	matrix.M24 = InValue.M24 + InValue2.M24;
	matrix.M31 = InValue.M31 + InValue2.M31;
	matrix.M32 = InValue.M32 + InValue2.M32;
	matrix.M33 = InValue.M33 + InValue2.M33;
	matrix.M34 = InValue.M34 + InValue2.M34;
	matrix.M41 = InValue.M41 + InValue2.M41;
	matrix.M42 = InValue.M42 + InValue2.M42;
	matrix.M43 = InValue.M43 + InValue2.M43;
	matrix.M44 = InValue.M44 + InValue2.M44;

	return matrix;
}

FMatrix FMatrix::Divide(FMatrix InValue, FMatrix InValue2)
{
	FMatrix matrix;
	matrix.M11 = InValue.M11 / InValue2.M11;
	matrix.M12 = InValue.M12 / InValue2.M12;
	matrix.M13 = InValue.M13 / InValue2.M13;
	matrix.M14 = InValue.M14 / InValue2.M14;
	matrix.M21 = InValue.M21 / InValue2.M21;
	matrix.M22 = InValue.M22 / InValue2.M22;
	matrix.M23 = InValue.M23 / InValue2.M23;
	matrix.M24 = InValue.M24 / InValue2.M24;
	matrix.M31 = InValue.M31 / InValue2.M31;
	matrix.M32 = InValue.M32 / InValue2.M32;
	matrix.M33 = InValue.M33 / InValue2.M33;
	matrix.M34 = InValue.M34 / InValue2.M34;
	matrix.M41 = InValue.M41 / InValue2.M41;
	matrix.M42 = InValue.M42 / InValue2.M42;
	matrix.M43 = InValue.M43 / InValue2.M43;
	matrix.M44 = InValue.M44 / InValue2.M44;

	return matrix;
}

FMatrix FMatrix::Divide(FMatrix InValue, float InValue2)
{
	FMatrix matrix;

	float value = 1.0f / InValue2;
	matrix.M11 = InValue.M11 * value;
	matrix.M12 = InValue.M12 * value;
	matrix.M13 = InValue.M13 * value;
	matrix.M14 = InValue.M14 * value;
	matrix.M21 = InValue.M21 * value;
	matrix.M22 = InValue.M22 * value;
	matrix.M23 = InValue.M23 * value;
	matrix.M24 = InValue.M24 * value;
	matrix.M31 = InValue.M31 * value;
	matrix.M32 = InValue.M32 * value;
	matrix.M33 = InValue.M33 * value;
	matrix.M34 = InValue.M34 * value;
	matrix.M41 = InValue.M41 * value;
	matrix.M42 = InValue.M42 * value;
	matrix.M43 = InValue.M43 * value;
	matrix.M44 = InValue.M44 * value;

	return matrix;
}

FMatrix FMatrix::Multiply(FMatrix InValue, FMatrix InValue2)
{
	FMatrix matrix;

	matrix.M11 = InValue.M11 * InValue2.M11 + InValue.M12 * InValue2.M21 + InValue.M13 * InValue2.M31 + InValue.M14 * InValue2.M41;
	matrix.M12 = InValue.M11 * InValue2.M12 + InValue.M12 * InValue2.M22 + InValue.M13 * InValue2.M32 + InValue.M14 * InValue2.M42;
	matrix.M13 = InValue.M11 * InValue2.M13 + InValue.M12 * InValue2.M23 + InValue.M13 * InValue2.M33 + InValue.M14 * InValue2.M43;
	matrix.M14 = InValue.M11 * InValue2.M14 + InValue.M12 * InValue2.M24 + InValue.M13 * InValue2.M34 + InValue.M14 * InValue2.M44;
	matrix.M21 = InValue.M21 * InValue2.M11 + InValue.M22 * InValue2.M21 + InValue.M23 * InValue2.M31 + InValue.M24 * InValue2.M41;
	matrix.M22 = InValue.M21 * InValue2.M12 + InValue.M22 * InValue2.M22 + InValue.M23 * InValue2.M32 + InValue.M24 * InValue2.M42;
	matrix.M23 = InValue.M21 * InValue2.M13 + InValue.M22 * InValue2.M23 + InValue.M23 * InValue2.M33 + InValue.M24 * InValue2.M43;
	matrix.M24 = InValue.M21 * InValue2.M14 + InValue.M22 * InValue2.M24 + InValue.M23 * InValue2.M34 + InValue.M24 * InValue2.M44;
	matrix.M31 = InValue.M31 * InValue2.M11 + InValue.M32 * InValue2.M21 + InValue.M33 * InValue2.M31 + InValue.M34 * InValue2.M41;
	matrix.M32 = InValue.M31 * InValue2.M12 + InValue.M32 * InValue2.M22 + InValue.M33 * InValue2.M32 + InValue.M34 * InValue2.M42;
	matrix.M33 = InValue.M31 * InValue2.M13 + InValue.M32 * InValue2.M23 + InValue.M33 * InValue2.M33 + InValue.M34 * InValue2.M43;
	matrix.M34 = InValue.M31 * InValue2.M14 + InValue.M32 * InValue2.M24 + InValue.M33 * InValue2.M34 + InValue.M34 * InValue2.M44;
	matrix.M41 = InValue.M41 * InValue2.M11 + InValue.M42 * InValue2.M21 + InValue.M43 * InValue2.M31 + InValue.M44 * InValue2.M41;
	matrix.M42 = InValue.M41 * InValue2.M12 + InValue.M42 * InValue2.M22 + InValue.M43 * InValue2.M32 + InValue.M44 * InValue2.M42;
	matrix.M43 = InValue.M41 * InValue2.M13 + InValue.M42 * InValue2.M23 + InValue.M43 * InValue2.M33 + InValue.M44 * InValue2.M43;
	matrix.M44 = InValue.M41 * InValue2.M14 + InValue.M42 * InValue2.M24 + InValue.M43 * InValue2.M34 + InValue.M44 * InValue2.M44;

	return matrix;
}

FMatrix FMatrix::Multiply(FMatrix InValue, float InValue2)
{
	FMatrix matrix;

	matrix.M11 = InValue.M11 * InValue2;
	matrix.M12 = InValue.M12 * InValue2;
	matrix.M13 = InValue.M13 * InValue2;
	matrix.M14 = InValue.M14 * InValue2;
	matrix.M21 = InValue.M21 * InValue2;
	matrix.M22 = InValue.M22 * InValue2;
	matrix.M23 = InValue.M23 * InValue2;
	matrix.M24 = InValue.M24 * InValue2;
	matrix.M31 = InValue.M31 * InValue2;
	matrix.M32 = InValue.M32 * InValue2;
	matrix.M33 = InValue.M33 * InValue2;
	matrix.M34 = InValue.M34 * InValue2;
	matrix.M41 = InValue.M41 * InValue2;
	matrix.M42 = InValue.M42 * InValue2;
	matrix.M43 = InValue.M43 * InValue2;
	matrix.M44 = InValue.M44 * InValue2;

	return matrix;
}

FMatrix FMatrix::Negative(FMatrix InValue)
{
	FMatrix m;
	m.M11 = -InValue.M11;
	m.M12 = -InValue.M12;
	m.M13 = -InValue.M13;
	m.M14 = -InValue.M14;
	m.M21 = -InValue.M21;
	m.M22 = -InValue.M22;
	m.M23 = -InValue.M23;
	m.M24 = -InValue.M24;
	m.M31 = -InValue.M31;
	m.M32 = -InValue.M32;
	m.M33 = -InValue.M33;
	m.M34 = -InValue.M34;
	m.M41 = -InValue.M41;
	m.M42 = -InValue.M42;
	m.M43 = -InValue.M43;
	m.M44 = -InValue.M44;

	return m;
}

FMatrix FMatrix::CreateTranslation(FVector InValue)
{
	FMatrix matrix;

	matrix.M11 = 1.0f; matrix.M12 = 0.0f; matrix.M13 = 0.0f; matrix.M14 = 0.0f;
	matrix.M21 = 0.0f; matrix.M22 = 1.0f; matrix.M23 = 0.0f; matrix.M24 = 0.0f;
	matrix.M31 = 0.0f; matrix.M32 = 0.0f; matrix.M33 = 1.0f; matrix.M34 = 0.0f;

	matrix.M41 = InValue.X;
	matrix.M42 = InValue.Y;
	matrix.M43 = InValue.Z;
	matrix.M44 = 1.0f;

	return matrix;
}

FMatrix FMatrix::CreateScale(FVector InValue)
{
	FMatrix matrix;
	matrix.M11 = InValue.X; matrix.M12 = 0.0f;     matrix.M13 = 0.0f;     matrix.M14 = 0.0f;
	matrix.M21 = 0.0f;     matrix.M22 = InValue.Y; matrix.M23 = 0.0f;     matrix.M24 = 0.0f;
	matrix.M31 = 0.0f;     matrix.M32 = 0.0f;     matrix.M33 = InValue.Z; matrix.M34 = 0.0f;
	matrix.M41 = 0.0f;     matrix.M42 = 0.0f;     matrix.M43 = 0.0f;     matrix.M44 = 1.0f;

	return matrix;
}

FMatrix FMatrix::CreateScale(float InValue)
{
	FMatrix matrix;
	matrix.M11 = InValue; matrix.M12 = 0.0f;  matrix.M13 = 0.0f;  matrix.M14 = 0.0f;
	matrix.M21 = 0.0f;  matrix.M22 = InValue; matrix.M23 = 0.0f;  matrix.M24 = 0.0f;
	matrix.M31 = 0.0f;  matrix.M32 = 0.0f;  matrix.M33 = InValue; matrix.M34 = 0.0f;
	matrix.M41 = 0.0f;  matrix.M42 = 0.0f;  matrix.M43 = 0.0f;  matrix.M44 = 1.0f;

	return matrix;
}

FMatrix FMatrix::CreateRotationX(float InValue)
{
	float val1 = cosf(InValue);
	float val2 = sinf(InValue);

	FMatrix matrix;

	matrix.M11 = 1.0f; matrix.M12 = 0.0f;  matrix.M13 = 0.0f; matrix.M14 = 0.0f;
	matrix.M21 = 0.0f; matrix.M22 = val1;  matrix.M23 = -val2; matrix.M24 = 0.0f;
	matrix.M31 = 0.0f; matrix.M32 = val2;  matrix.M33 = val1; matrix.M34 = 0.0f;
	matrix.M41 = 0.0f; matrix.M42 = 0.0f;  matrix.M43 = 0.0f; matrix.M44 = 1.0f;

	return matrix;
}

FMatrix FMatrix::CreateRotationY(float InValue)
{
	float val1 = cosf(InValue);
	float val2 = sinf(InValue);

	FMatrix matrix;

	matrix.M11 = val1;  matrix.M12 = 0.0f; matrix.M13 = val2;  matrix.M14 = 0.0f;
	matrix.M21 = 0.0f;  matrix.M22 = 1.0f; matrix.M23 = 0.0f;  matrix.M24 = 0.0f;
	matrix.M31 = -val2; matrix.M32 = 0.0f; matrix.M33 = val1;  matrix.M34 = 0.0f;
	matrix.M41 = 0.0f;  matrix.M42 = 0.0f; matrix.M43 = 0.0f;  matrix.M44 = 1.0f;

	return matrix;
}

FMatrix FMatrix::CreateRotationZ(float radians)
{
	float val1 = cosf(radians);
	float val2 = sinf(radians);

	FMatrix matrix;
	matrix.M11 = val1; matrix.M12 = -val2; matrix.M13 = 0.0f; matrix.M14 = 0.0f;
	matrix.M21 = val2; matrix.M22 = val1; matrix.M23 = 0.0f; matrix.M24 = 0.0f;
	matrix.M31 = 0.0f; matrix.M32 = 0.0f; matrix.M33 = 1.0f; matrix.M34 = 0.0f;
	matrix.M41 = 0.0f; matrix.M42 = 0.0f; matrix.M43 = 0.0f; matrix.M44 = 1.0f;
	return matrix;
}

FMatrix FMatrix::CreateFromAxisAngle(FVector InAxis, float InAngle)
{
	FMatrix matrix;
	float x = InAxis.X;
	float y = InAxis.Y;
	float z = InAxis.Z;

	float value = sinf(InAngle);
	float value1 = cosf(InAngle);
	float value2 = x * x;
	float value3 = y * y;
	float value4 = z * z;
	float value5 = x * y;
	float value6 = x * z;
	float value7 = y * z;

	matrix.M11 = value2 + value1 * (1.0f - value2);
	matrix.M12 = value5 - value1 * value5 - value * z;
	matrix.M13 = value6 - value1 * value6 + value * y;
	matrix.M14 = 0.0f;

	matrix.M21 = value5 - value1 * value5 + value * z;
	matrix.M22 = value3 + value1 * (1.0f - value3);
	matrix.M23 = value7 - value1 * value7 - value * x;
	matrix.M24 = 0.0f;

	matrix.M31 = value6 - value1 * value6 - value * y;
	matrix.M32 = value7 - value1 * value7 + value * x;
	matrix.M33 = value4 + value1 * (1.0f - value4);
	matrix.M34 = 0.0f;

	matrix.M41 = 0.0f;
	matrix.M42 = 0.0f;
	matrix.M43 = 0.0f;
	matrix.M44 = 1.0f;
	return matrix;
}

FMatrix FMatrix::CreatePerspective(float InWidth, float InHeight, float InNear, float InFar)
{
	FMatrix matrix;
	matrix.M11 = 2.0f * InNear / InWidth;
	matrix.M12 = 0.0f;
	matrix.M13 = 0.0f;
	matrix.M14 = 0.0f;

	matrix.M21 = 0.0f;
	matrix.M22 = 2.0f * InNear / InHeight;
	matrix.M23 = 0.0f;
	matrix.M24 = 0.0f;

	matrix.M31 = 0.0f;
	matrix.M32 = 0.0f;
	matrix.M33 = InFar / (InFar - InNear);
	matrix.M34 = 1.0f;

	matrix.M41 = 0.0f;
	matrix.M42 = 0.0f;
	matrix.M43 = InNear * InFar / (InNear - InFar);
	matrix.M44 = 0.0f;

	return matrix;
}

FMatrix FMatrix::CreatePerspectiveFieldOfView(float InFOV, float InAspectRatio, float InNear, float InFar)
{
	float yScale = 1.0f / tanf(InFOV * 0.5f); //cot
	float xScale = yScale / InAspectRatio;

	FMatrix matrix;
	matrix.M11 = xScale;
	matrix.M12 = 0.0f;
	matrix.M13 = 0.0f;
	matrix.M14 = 0.0f;

	matrix.M21 = 0.0f;
	matrix.M22 = yScale;
	matrix.M23 = 0.0f;
	matrix.M24 = 0.0f;

	matrix.M31 = 0.0f;
	matrix.M32 = 0.0f;
	matrix.M33 = InFar / (InFar - InNear);
	matrix.M34 = 1.0f;

	matrix.M41 = 0.0f;
	matrix.M42 = 0.0f;
	matrix.M43 = -InNear * InFar / (InFar - InNear);
	matrix.M44 = 0.0f;

	return matrix;
}

FMatrix FMatrix::CreatePerspectiveOffCenter(float InLeft, float InRight, float InBottom, float InTop, float InNear, float InFar)
{
	FMatrix matrix;
	matrix.M11 = 2.0f * InNear / (InRight - InLeft);
	matrix.M12 = 0.0f;
	matrix.M13 = 0.0f;
	matrix.M14 = 0.0f;

	matrix.M21 = 0.0f;
	matrix.M22 = 2.0f * InNear / (InTop - InBottom);
	matrix.M23 = 0.0f;
	matrix.M24 = 0.0f;

	matrix.M31 = (InLeft + InRight) / (InLeft - InRight);
	matrix.M32 = (InTop + InBottom) / (InBottom - InTop);
	matrix.M33 = InFar / (InFar - InNear);
	matrix.M34 = 1.0f;

	matrix.M41 = 0.0f;
	matrix.M42 = 0.0f;
	matrix.M43 = InNear * InFar / (InNear - InFar);
	matrix.M44 = 0.0f;

	return matrix;
}

FMatrix FMatrix::CreateLookAt(FVector InPosition, FVector InTarget, FVector InUp)
{
	FMatrix matrix;
	FVector zAxis = FVector::Normalize(InTarget - InPosition);
	FVector xAxis = FVector::Normalize(FVector::Cross(InUp, zAxis));
	FVector yAxis = FVector::Cross(zAxis, xAxis);

	matrix.M11 = xAxis.X; matrix.M12 = yAxis.X; matrix.M13 = zAxis.X; matrix.M14 = 0.0f;
	matrix.M21 = xAxis.Y; matrix.M22 = yAxis.Y; matrix.M23 = zAxis.Y; matrix.M24 = 0.0f;
	matrix.M31 = xAxis.Z; matrix.M32 = yAxis.Z; matrix.M33 = zAxis.Z; matrix.M34 = 0.0f;

	matrix.M41 = -FVector::Dot(xAxis, InPosition);
	matrix.M42 = -FVector::Dot(yAxis, InPosition);
	matrix.M43 = -FVector::Dot(zAxis, InPosition);
	matrix.M44 = 1.0f;

	return matrix;
}

FMatrix FMatrix::CreateFromQuaternion(FQuaternion InValue)
{
	float x = InValue.X * InValue.X;
	float y = InValue.Y * InValue.Y;
	float z = InValue.Z * InValue.Z;
	float value = InValue.X * InValue.Y;
	float z1 = InValue.Z * InValue.W;
	float value1 = InValue.Z * InValue.X;
	float y1 = InValue.Y * InValue.W;
	float y2 = InValue.Y * InValue.Z;
	float x1 = InValue.X * InValue.W;

	FMatrix matrix;
	matrix.M11 = 1.0f - 2.0f * (y + z);
	matrix.M12 = 2.0f * (value + z1);
	matrix.M13 = -2.0f * (value1 - y1);
	matrix.M14 = 0.0f;

	matrix.M21 = 2.0f * (value - z1);
	matrix.M22 = 1.0f - 2.0f * (z + x);
	matrix.M23 = -2.0f * (y2 + x1);
	matrix.M24 = 0.0f;

	matrix.M31 = 2.0f * (value1 + y1);
	matrix.M32 = 2.0f * (y2 - x1);
	matrix.M33 = -(1.0f - 2.0f * (y + x));
	matrix.M34 = 0.0f;

	matrix.M41 = 0.0f;
	matrix.M42 = 0.0f;
	matrix.M43 = 0.0f;
	matrix.M44 = 1.0f;

	return matrix;
}

FMatrix FMatrix::CreateFromYawPitchRoll(float InYaw, float InPitch, float InRoll)
{
	FQuaternion result;
	result = FQuaternion::CreateFromYawPitchRoll(InYaw, InPitch, InRoll);

	return CreateFromQuaternion(result);
}

FMatrix FMatrix::CreateOrthographic(float InWidth, float InHeight, float InNear, float InFar)
{
	FMatrix matrix;

	matrix.M11 = 2.0f / InWidth;
	matrix.M12 = 0.0f;
	matrix.M13 = 0.0f;
	matrix.M14 = 0.0f;

	matrix.M21 = 0.0f;
	matrix.M22 = 2.0f / InHeight;
	matrix.M23 = 0.0f;
	matrix.M24 = 0.0f;

	matrix.M31 = 0.0f;
	matrix.M32 = 0.0f;
	matrix.M33 = 1.0f / (InFar - InNear);
	matrix.M34 = 0.0f;

	matrix.M41 = 0.0f;
	matrix.M42 = 0.0f;
	matrix.M43 = -InNear / (InFar - InNear);
	matrix.M44 = 1.0f;

	return matrix;
}

FMatrix FMatrix::CreateOrthographicOffCenter(float InLeft, float InRight, float InBottom, float InTop, float InNear, float InFar)
{
	FMatrix matrix;

	matrix.M11 = 2.0f / (InRight - InLeft);
	matrix.M12 = 0.0;
	matrix.M13 = 0.0;
	matrix.M14 = 0.0;

	matrix.M21 = 0.0f;
	matrix.M22 = 2.0f / (InTop - InBottom);
	matrix.M23 = 0.0f;
	matrix.M24 = 0.0f;

	matrix.M31 = 0.0f;
	matrix.M32 = 0.0f;
	matrix.M33 = 1.0f / (InFar - InNear);
	matrix.M34 = 0.0f;

	matrix.M41 = (InLeft + InRight) / (InLeft - InRight);
	matrix.M42 = (InTop + InBottom) / (InBottom - InTop);
	matrix.M43 = InNear / (InNear - InFar);
	matrix.M44 = 1.0f;

	return matrix;
}

FMatrix FMatrix::Transform(FMatrix InValue, FQuaternion InRotation)
{
	float wxx = InRotation.W * (InRotation.X + InRotation.X);
	float wyy = InRotation.W * (InRotation.Y + InRotation.Y);
	float wzz = InRotation.W * (InRotation.Z + InRotation.Z);

	float xxx = InRotation.X * (InRotation.X + InRotation.X);
	float xyy = InRotation.X * (InRotation.Y + InRotation.Y);
	float xzz = InRotation.X * (InRotation.Z + InRotation.Z);

	float yyy = InRotation.Y * (InRotation.Y + InRotation.Y);
	float yzz = InRotation.Y * (InRotation.Z + InRotation.Z);
	float zzz = InRotation.Z * (InRotation.Z + InRotation.Z);

	float InValue1 = 1.0f - yyy - zzz;
	float InValue2 = xyy + wzz;
	float InValue3 = xzz - wyy;
	float InValue4 = xyy + wzz;

	float InValue5 = 1.0f - xxx - zzz;
	float InValue6 = yzz - wxx;
	float InValue7 = xzz - wyy;
	float InValue8 = yzz + wxx;

	float InValue9 = 1.0f - xxx - yyy;

	FMatrix matrix;
	matrix.M11 = InValue.M11 * InValue1 + InValue.M12 * InValue2 + InValue.M13 * InValue3;
	matrix.M12 = InValue.M11 * InValue4 + InValue.M12 * InValue5 + InValue.M13 * InValue6;
	matrix.M13 = InValue.M11 * InValue7 + InValue.M12 * InValue8 + InValue.M13 * InValue9;
	matrix.M14 = InValue.M14;

	matrix.M21 = InValue.M21 * InValue1 + InValue.M22 * InValue2 + InValue.M23 * InValue3;
	matrix.M22 = InValue.M21 * InValue4 + InValue.M22 * InValue5 + InValue.M23 * InValue6;
	matrix.M23 = InValue.M21 * InValue7 + InValue.M22 * InValue8 + InValue.M23 * InValue9;
	matrix.M24 = InValue.M24;

	matrix.M31 = InValue.M31 * InValue1 + InValue.M32 * InValue2 + InValue.M33 * InValue3;
	matrix.M32 = InValue.M31 * InValue4 + InValue.M32 * InValue5 + InValue.M33 * InValue6;
	matrix.M33 = InValue.M31 * InValue7 + InValue.M32 * InValue8 + InValue.M33 * InValue9;
	matrix.M34 = InValue.M34;

	matrix.M41 = InValue.M41 * InValue1 + InValue.M42 * InValue2 + InValue.M43 * InValue3;
	matrix.M42 = InValue.M41 * InValue4 + InValue.M42 * InValue5 + InValue.M43 * InValue6;
	matrix.M43 = InValue.M41 * InValue7 + InValue.M42 * InValue8 + InValue.M43 * InValue9;
	matrix.M44 = InValue.M44;

	return matrix;
}

FMatrix FMatrix::Transpose(FMatrix InValue)
{
	FMatrix InValue1;
	InValue1.M11 = InValue.M11; InValue1.M12 = InValue.M21; InValue1.M13 = InValue.M31; InValue1.M14 = InValue.M41;
	InValue1.M21 = InValue.M12; InValue1.M22 = InValue.M22; InValue1.M23 = InValue.M32; InValue1.M24 = InValue.M42;
	InValue1.M31 = InValue.M13; InValue1.M32 = InValue.M23; InValue1.M33 = InValue.M33; InValue1.M34 = InValue.M43;
	InValue1.M41 = InValue.M14; InValue1.M42 = InValue.M24; InValue1.M43 = InValue.M34; InValue1.M44 = InValue.M44;

	return InValue1;
}

FMatrix FMatrix::Invert(FMatrix InValue)
{
	float value5 = InValue.M11; float value4 = InValue.M12; float value3 = InValue.M13; float value2 = InValue.M14;
	float value9 = InValue.M21; float value8 = InValue.M22; float value7 = InValue.M23; float value6 = InValue.M24;
	float value17 = InValue.M31; float value16 = InValue.M32; float value15 = InValue.M33; float value14 = InValue.M34;
	float value13 = InValue.M41; float value12 = InValue.M42; float value11 = InValue.M43; float value10 = InValue.M44;

	float value23 = (value15 * value10) - (value14 * value11);
	float value22 = (value16 * value10) - (value14 * value12);
	float value21 = (value16 * value11) - (value15 * value12);
	float value20 = (value17 * value10) - (value14 * value13);
	float value19 = (value17 * value11) - (value15 * value13);
	float value18 = (value17 * value12) - (value16 * value13);
	float value39 = ((value8 * value23) - (value7 * value22)) + (value6 * value21);
	float value38 = -(((value9 * value23) - (value7 * value20)) + (value6 * value19));
	float value37 = ((value9 * value22) - (value8 * value20)) + (value6 * value18);
	float value36 = -(((value9 * value21) - (value8 * value19)) + (value7 * value18));
	float value = 1.0f / ((((value5 * value39) + (value4 * value38)) + (value3 * value37)) + (value2 * value36));


	FMatrix matrix;

	matrix.M11 = value39 * value;
	matrix.M21 = value38 * value;
	matrix.M31 = value37 * value;
	matrix.M41 = value36 * value;

	matrix.M12 = -(((value4 * value23) - (value3 * value22)) + (value2 * value21)) * value;
	matrix.M22 = (((value5 * value23) - (value3 * value20)) + (value2 * value19)) * value;
	matrix.M32 = -(((value5 * value22) - (value4 * value20)) + (value2 * value18)) * value;
	matrix.M42 = (((value5 * value21) - (value4 * value19)) + (value3 * value18)) * value;

	float value35 = (value7 * value10) - (value6 * value11);
	float value34 = (value8 * value10) - (value6 * value12);
	float value33 = (value8 * value11) - (value7 * value12);
	float value32 = (value9 * value10) - (value6 * value13);
	float value31 = (value9 * value11) - (value7 * value13);
	float value30 = (value9 * value12) - (value8 * value13);

	matrix.M13 = (((value4 * value35) - (value3 * value34)) + (value2 * value33)) * value;
	matrix.M23 = -(((value5 * value35) - (value3 * value32)) + (value2 * value31)) * value;
	matrix.M33 = (((value5 * value34) - (value4 * value32)) + (value2 * value30)) * value;
	matrix.M43 = -(((value5 * value33) - (value4 * value31)) + (value3 * value30)) * value;

	float value29 = (value7 * value14) - (value6 * value15);
	float value28 = (value8 * value14) - (value6 * value16);
	float value27 = (value8 * value15) - (value7 * value16);
	float value26 = (value9 * value14) - (value6 * value17);
	float value25 = (value9 * value15) - (value7 * value17);
	float value24 = (value9 * value16) - (value8 * value17);

	matrix.M14 = -(((value4 * value29) - (value3 * value28)) + (value2 * value27)) * value;
	matrix.M24 = (((value5 * value29) - (value3 * value26)) + (value2 * value25)) * value;
	matrix.M34 = -(((value5 * value28) - (value4 * value26)) + (value2 * value24)) * value;
	matrix.M44 = (((value5 * value27) - (value4 * value25)) + (value3 * value24)) * value;

	return matrix;
}

FMatrix FMatrix::Lerp(FMatrix InValue, FMatrix InValue2, float InAmount)
{
	FMatrix matrix;

	matrix.M11 = InValue.M11 + (InValue2.M11 - InValue.M11) * InAmount;
	matrix.M12 = InValue.M12 + (InValue2.M12 - InValue.M12) * InAmount;
	matrix.M13 = InValue.M13 + (InValue2.M13 - InValue.M13) * InAmount;
	matrix.M14 = InValue.M14 + (InValue2.M14 - InValue.M14) * InAmount;
	matrix.M21 = InValue.M21 + (InValue2.M21 - InValue.M21) * InAmount;
	matrix.M22 = InValue.M22 + (InValue2.M22 - InValue.M22) * InAmount;
	matrix.M23 = InValue.M23 + (InValue2.M23 - InValue.M23) * InAmount;
	matrix.M24 = InValue.M24 + (InValue2.M24 - InValue.M24) * InAmount;
	matrix.M31 = InValue.M31 + (InValue2.M31 - InValue.M31) * InAmount;
	matrix.M32 = InValue.M32 + (InValue2.M32 - InValue.M32) * InAmount;
	matrix.M33 = InValue.M33 + (InValue2.M33 - InValue.M33) * InAmount;
	matrix.M34 = InValue.M34 + (InValue2.M34 - InValue.M34) * InAmount;
	matrix.M41 = InValue.M41 + (InValue2.M41 - InValue.M41) * InAmount;
	matrix.M42 = InValue.M42 + (InValue2.M42 - InValue.M42) * InAmount;
	matrix.M43 = InValue.M43 + (InValue2.M43 - InValue.M43) * InAmount;
	matrix.M44 = InValue.M44 + (InValue2.M44 - InValue.M44) * InAmount;

	return matrix;
}