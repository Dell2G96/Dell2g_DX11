#pragma once

class CBinaryWriter
{
public:
	CBinaryWriter(wstring InFile);
	~CBinaryWriter();

	void Close();

public:
	void ToInt(int InValue);
	void ToUINT(UINT InValue);
	void ToSingle(float InValue);

	void ToString(const string& InValue);
	void ToByte(void* InValue, UINT InDataSize);

	void ToVector(FVector& InData);
	void ToMatrix(FMatrix& InData);

private:
	HANDLE FileHandle = nullptr;
};

///////////////////////////////////////////////////////////////////////////////

class CBinaryReader
{
public:
	CBinaryReader(wstring InFile);
	~CBinaryReader();

	void Close();

public:
	int FromInt();
	UINT FromUINT();
	float FromSingle();

	string FromString();
	void FromByte(void** OutValue, UINT InDataSize);

	FVector FromVector();
	FMatrix FromMatrix();

private:
	HANDLE FileHandle = nullptr;
};