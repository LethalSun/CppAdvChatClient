#pragma once
#include <stdio.h>

namespace chatClient
{
	class Util
	{
	public:
		Util() = default;
		~Util() = default;
		static void UnicodeToAnsi(const wchar_t* pszText, const int destSize, char* pszDest)
		{
			_snprintf_s(pszDest, destSize, _TRUNCATE, "%S", pszText);
		}
	};

}

