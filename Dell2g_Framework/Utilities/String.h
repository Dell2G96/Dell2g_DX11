#pragma once

class CString
{
public:
	static void SplitString(vector<string>* InResult, string InOrigin, string InToken);
	static void SplitString(vector<wstring>* InResult, wstring InOrigin, wstring InToken);

	static bool StartsWith(string InValue, string InCompare);
	static bool StartsWith(wstring InValue, wstring InCompare);

	static bool Contain(string InValue, string InCompare);
	static bool Contain(wstring InValue, wstring InCompare);

	static void Replace(string* InValue, string InCompare, string InRepace);
	static void Replace(wstring* InValue, wstring InCompare, wstring InRepace);

	static wstring ToWString(string InValue);
	static string ToString(wstring InValue);

	static string ToUpper(string InValue);
	static wstring ToUpper(wstring InValue);
	static string ToLower(string InValue);	
	static wstring ToLower(wstring InValue);

	static string Format(const string InFormat, ...);
	static wstring Format(const wstring InFormat, ...);

	static FColor FromColor(const string& InValue);
	static FVector2D FromVector2D(const string& InValue);
	static FVector FromVector(const string& InValue);
	static FVector4 FromVector4(const string& InValue);
};