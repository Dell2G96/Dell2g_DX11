#include "Framework.h"
#include "BinaryFile.h"

#pragma warning(disable:6031)
CBinaryWriter::CBinaryWriter(wstring InFile)
{
	assert(InFile.length() > 0);

	FileHandle = CreateFile
	(
		InFile.c_str(),
		GENERIC_WRITE,
		0,
		nullptr,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		nullptr
	);
	assert(FileHandle != INVALID_HANDLE_VALUE);
}

CBinaryWriter::~CBinaryWriter()
{
	Close();
}

void CBinaryWriter::Close()
{
	{ if(FileHandle == nullptr) return; }

	CloseHandle(FileHandle);
	FileHandle = nullptr;
}

void CBinaryWriter::ToInt(int InValue)
{
	DWORD size = 0;
	WriteFile(FileHandle, &InValue, sizeof(int), &size, nullptr);
}

void CBinaryWriter::ToUINT(UINT InValue)
{
	DWORD size = 0;
	WriteFile(FileHandle, &InValue, sizeof(UINT), &size, nullptr);
}

void CBinaryWriter::ToSingle(float InValue)
{
	DWORD size = 0;
	WriteFile(FileHandle, &InValue, sizeof(float), &size, nullptr);
}

void CBinaryWriter::ToString(const string& InValue)
{
	ToUINT(InValue.size());


	DWORD size = 0;

	const char* str = InValue.c_str();
	WriteFile(FileHandle, str, InValue.size(), &size, nullptr);
}

void CBinaryWriter::ToByte(void* InValue, UINT InDataSize)
{
	DWORD size = 0;
	
	WriteFile(FileHandle, InValue, InDataSize, &size, nullptr);
	assert(InDataSize == size);
}

void CBinaryWriter::ToVector(FVector& InData)
{
	DWORD size = 0;

	const float* v = InData;
	WriteFile(FileHandle, v, sizeof(FVector), &size, nullptr);
	assert(sizeof(FVector) == size);
}

void CBinaryWriter::ToMatrix(FMatrix& InData)
{
	DWORD size = 0;

	const float* m = InData;
	WriteFile(FileHandle, m, sizeof(FMatrix), &size, nullptr);
	assert(sizeof(FMatrix) == size);
}

///////////////////////////////////////////////////////////////////////////////

CBinaryReader::CBinaryReader(wstring InFile)
{
	assert(InFile.length() > 0);

	FileHandle = CreateFile
	(
		InFile.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr
	);
	assert(FileHandle != INVALID_HANDLE_VALUE);
}

CBinaryReader::~CBinaryReader()
{
	Close();
}

void CBinaryReader::Close()
{
	{ if(FileHandle == nullptr) return; }
	
	CloseHandle(FileHandle);
	FileHandle = nullptr;
}

int CBinaryReader::FromInt()
{
	int value = 0;

	DWORD size = 0;
	ReadFile(FileHandle, &value, sizeof(int), &size, nullptr);

	return value;
}

UINT CBinaryReader::FromUINT()
{
	UINT value = 0;

	DWORD size = 0;
	ReadFile(FileHandle, &value, sizeof(UINT), &size, nullptr);

	return value;
}

float CBinaryReader::FromSingle()
{
	float value = 0;

	DWORD size = 0;
	ReadFile(FileHandle, &value, sizeof(float), &size, nullptr);

	return value;
}

string CBinaryReader::FromString()
{
	UINT length = FromUINT();
	char* temp = new char[length + 1];

	DWORD size = 0;
	ReadFile(FileHandle, temp, sizeof(char) * length, &size, nullptr);
	assert(size == (sizeof(char) * length));

	temp[length] = '\0';

	string result(temp);
	DeleteArray(temp);

	return result;
}

void CBinaryReader::FromByte(void** OutValue, UINT InDataSize)
{
	DWORD size = 0;
	ReadFile(FileHandle, *OutValue, InDataSize, &size, nullptr);
	assert(size == InDataSize);
}

FVector CBinaryReader::FromVector()
{
	float temp[16];

	DWORD size = 0;
	ReadFile(FileHandle, temp, sizeof(FVector), &size, nullptr);
	assert(size == sizeof(FVector));


	FVector result;
	memcpy_s(&result, sizeof(FVector), temp, sizeof(FVector));

	return result;
}

FMatrix CBinaryReader::FromMatrix()
{
	float temp[16];

	DWORD size = 0;
	ReadFile(FileHandle, temp, sizeof(FMatrix), &size, nullptr);
	assert(size == sizeof(FMatrix));


	FMatrix result;
	memcpy_s(&result, sizeof(FMatrix), temp, sizeof(FMatrix));

	return result;
}
#pragma warning(default:6031)