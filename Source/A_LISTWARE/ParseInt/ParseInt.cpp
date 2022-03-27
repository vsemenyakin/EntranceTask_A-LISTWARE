#include "ParseInt.h"

namespace ParseIntLocal
{
	TOptional<int32> CharToDigit(const TCHAR DigitChar)
	{
		return (DigitChar >= '0' && DigitChar <= '9') ?
			TOptional<int32>{ (DigitChar - '0') } :
			TOptional<int32>{ };
	}
}

TOptional<int32> StringToNumber(const FString& String)
{
	using namespace ParseIntLocal;
	
	const int32 Len = String.Len();

	const bool bEmptyString = (Len == 0);
	if (bEmptyString)
		return { };

	TOptional<int32> CurrentDigit = CharToDigit(String[0]);
	if (!CurrentDigit.IsSet())
		return { };

	const bool bFirstDigitIsZero = (Len > 1) && (CurrentDigit.GetValue() == 0);
	if (bFirstDigitIsZero)
		return { };

	int32 Result = CurrentDigit.GetValue();
	for (int32 DigitCharIndex = 1; DigitCharIndex < Len; ++DigitCharIndex)
	{
		CurrentDigit = CharToDigit(String[DigitCharIndex]);
		if (!CurrentDigit.IsSet())
			return {};

		Result = (Result * 10) + CurrentDigit.GetValue();
	}

	return Result;
}
