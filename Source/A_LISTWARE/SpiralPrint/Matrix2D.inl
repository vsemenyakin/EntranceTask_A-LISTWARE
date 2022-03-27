#pragma once

#include "Templates/UnrealTypeTraits.h"//for TIsSame
#include "HAL/UnrealMemory.h"

template<typename Type>
TMatrix2D<Type>::TMatrix2D(const std::initializer_list<std::initializer_list<Type>>& InitializerList)
{
	check(IsValidInitialization(InitializerList));

	CommonInit(InitializerList.begin()->size(), InitializerList.size());

	auto RowIterator = InitializerList.begin();
	for (int32 YIndex = 0; YIndex < XSize; ++YIndex, ++RowIterator)
	{
		auto RowElementIterator = RowIterator.begin()->begin();
		for (int32 XIndex = 0; XIndex < XSize; ++XIndex, ++RowElementIterator)
		{
			(*this)[XIndex][YIndex] = *RowElementIterator;
		}
	}
}

template<typename Type>
TMatrix2D<Type>::TMatrix2D(const int32 InXSize, const int32 InYSize)
{
	check((InXSize > 0) && (InYSize > 0));

	CommonInit(InXSize, InYSize);
}

template<typename Type>
TMatrix2D<Type>::TMatrix2D(const TMatrix2D& Other)
{
	CommonInit(Other.XSize, Other.YSize);
	Memcpy(MatrixData, Other.MatrixData);
}

template<typename Type>
TMatrix2D<Type>::TMatrix2D(TMatrix2D&& Other)
	: MatrixData(Other.MatrixData), XSize(Other.XSize), YSize(Other.YSize)
{
	Other.MatrixData = nullptr;
}

template<typename Type>
int32 TMatrix2D<Type>::GetXSize() const
{
	return XSize;
}

template<typename Type>
int32 TMatrix2D<Type>::GetYSize() const
{
	return YSize;
}

template<typename Type>
Type& TMatrix2D<Type>::GetRef(const int32 XIndex, const int32 YIndex)
{
	const Type& ConstResult = const_cast<const TMatrix2D*>(this)->GetRef(XIndex, YIndex);
	return const_cast<Type&>(ConstResult);
}

template<typename Type>
const Type& TMatrix2D<Type>::GetRef(const int32 XIndex, const int32 YIndex) const
{
	check(XIndex >= 0 && XIndex < XSize);
	check(YIndex >= 0 && YIndex < YSize);
	return MatrixData[YIndex * XSize + XIndex];
}

template<typename Type>
FString TMatrix2D<Type>::ToString() const
{
	static_assert(TIsSame<Type, int32>::Value, "Sorry, only int32 specialization of ToString is supported now");
	
	FString Result;
	
	for (int32 Y = 0; Y < YSize; ++Y)
	{
		//FString LineString = FString::Printf(TEXT("%s"), *::ToString((*this)[0][Y]));
		FString LineString = FString::Printf(TEXT("%d"), GetRef(0, Y));
		for (int32 X = 1; X < XSize; ++X)
		{
			//LineString += FString::Printf(TEXT("\t\t%s"), *::ToString((*this)[X][Y]));
			LineString += FString::Printf(TEXT("   %d"), GetRef(X, Y));
		}

		Result += LineString;

		if (Y != YSize - 1)
			Result += '\n';
	}

	return Result;
}

template<typename Type>
TMatrix2D<Type>::~TMatrix2D()
{
	if (MatrixData != nullptr)
		delete[] MatrixData;
}

template<typename Type>
static bool TMatrix2D<Type>::IsValidInitialization(const std::initializer_list<std::initializer_list<Type>>& InitializerList)
{
	const int32 YSize = InitializerList.size();
	if (YSize == 0)
		return false;

	const int32 XSize = InitializerList.begin()->size();
	if (XSize == 0)
		return false;

	for (const std::initializer_list<Type>& RowList : InitializerList)
		if (RowList.size() != XSize)
			return false;

	return true;
}

template<typename Type>
void TMatrix2D<Type>::CommonInit(const int32 InXSize, const int32 InYSize)
{
	XSize = InXSize;
	YSize = InYSize;
	MatrixData = new Type[XSize * YSize];
}
