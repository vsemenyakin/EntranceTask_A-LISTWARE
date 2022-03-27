#pragma once

#include <initializer_list>
#include "CoreMinimal.h"

template<typename Type>
class TMatrix2D
{
public:
	TMatrix2D() = default;
	TMatrix2D(const std::initializer_list<std::initializer_list<Type>>& InitializerList);
	TMatrix2D(const int32 InXSize, const int32 InYSize);
	TMatrix2D(const TMatrix2D& Other);
	TMatrix2D(TMatrix2D&& Other);
	
	int32 GetXSize() const;
	int32 GetYSize() const;
	
	Type& GetRef(const int32 XIndex, const int32 YIndex);
	const Type& GetRef(const int32 XIndex, const int32 YIndex) const;
	
	FString ToString() const;
	
	~TMatrix2D();
	
private:
	friend struct FRowAccessor;
	friend struct FConstRowAccessor;
	
	static bool IsValidInitialization(const std::initializer_list<std::initializer_list<Type>>& InitializerList);
	void CommonInit(const int32 InXSize, const int32 InYSize);
	
	Type* MatrixData = nullptr;
	int32 XSize = 0;
	int32 YSize = 0;
};

// - - - - -

#include "Matrix2D.inl"
