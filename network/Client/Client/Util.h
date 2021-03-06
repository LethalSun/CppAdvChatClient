#pragma once
#include <stdio.h>

namespace MDNetwork
{
	const int MaxPacketSize = 4096;

	class Util
	{
	public:
		Util() = default;
		~Util() = default;
		static void UnicodeToAnsi(const wchar_t* pszText, const int destSize, char* pszDest)
		{
			_snprintf_s(pszDest, destSize, _TRUNCATE, "%S", pszText);
		}

		static void AnsiToUnicode(const char* pszText, const int destSize, wchar_t* pszDest)
		{
			_snwprintf_s(pszDest, destSize, _TRUNCATE, L"%s", pszText);
		}

		static std::wstring CharToWstring(const char* pszText)
		{
			int textLength = strlen(pszText) + 1;
			wchar_t wTemp[MaxPacketSize];
			mbstowcs_s(0, wTemp, textLength, pszText, _TRUNCATE);

			return std::wstring(wTemp);
		}

	};

}

