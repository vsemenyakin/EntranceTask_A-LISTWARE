#include "ToString.h"

FString ToString(const int32 Value)
{
	return FString::Printf(TEXT("%d"), Value);
}
