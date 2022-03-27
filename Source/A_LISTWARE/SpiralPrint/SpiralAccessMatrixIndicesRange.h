#pragma once

#include "CoreMinimal.h"

struct FMatrixIndex
{
	void operator+=(const FMatrixIndex& Other);

	int32 X = 0;
	int32 Y = 0;
};

// --------------

class FSpiralAccessMatrixIndicesRange
{
public:
	class Iterator
	{
	public:
		FMatrixIndex operator*() const;
		void operator++();
		bool operator!=(const Iterator& Other) const;

	private:
		Iterator(const int32 InXSize, const int32 InYSize);
		friend class FSpiralAccessMatrixIndicesRange;

		bool IsEnd() const;
		bool IsCircleEnd() const;

		void NextCircle();
		void NextElement();

		void UpdateLimitsCache();

		int32 CirceXSize = 0;
		int32 CirceYSize = 0;

		FMatrixIndex CurrentIndex{ 0, 0 };
		int32 SideIndex = 0;

		struct
		{
			int32 Top = 0;
			int32 Right = 0;
			int32 Bottom = 0;
			int32 Left = 0;
		} LimitsCache;
	};

	// - - - - - - -
	
	FSpiralAccessMatrixIndicesRange(const int32 InXSize, const int32 InYSize);
	Iterator begin() const;
	Iterator end() const;

private:
	int32 XSize = 0;
	int32 YSize = 0;
};
