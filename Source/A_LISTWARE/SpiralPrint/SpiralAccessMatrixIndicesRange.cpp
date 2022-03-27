#include "SpiralAccessMatrixIndicesRange.h"

void FMatrixIndex::operator+=(const FMatrixIndex& Other)
{
	X += Other.X;
	Y += Other.Y;
}

// --------------

FMatrixIndex FSpiralAccessMatrixIndicesRange::Iterator::operator*() const
{
	check(!IsEnd());

	return CurrentIndex;
}

void FSpiralAccessMatrixIndicesRange::Iterator::operator++()
{
	check(!IsEnd());

	NextElement();
}

bool FSpiralAccessMatrixIndicesRange::Iterator::operator!=(const Iterator& Other) const
{
	const bool bBothEnd = IsEnd() && Other.IsEnd();
	return !bBothEnd;
}

FSpiralAccessMatrixIndicesRange::Iterator::Iterator(const int32 InXSize, const int32 InYSize)
	: CirceXSize(InXSize), CirceYSize(InYSize)
{
	UpdateLimitsCache();
}

bool FSpiralAccessMatrixIndicesRange::Iterator::IsEnd() const
{
	return (CirceXSize <= 0 || CirceYSize <= 0);
}

bool FSpiralAccessMatrixIndicesRange::Iterator::IsCircleEnd() const
{
	return (SideIndex == 4);
}

void FSpiralAccessMatrixIndicesRange::Iterator::NextCircle()
{
	check(!IsEnd());

	++CurrentIndex.X;

	CirceXSize -= 2;
	CirceYSize -= 2;

	UpdateLimitsCache();
	SideIndex = 0;
}

void FSpiralAccessMatrixIndicesRange::Iterator::NextElement()
{
	++SideIndex;

	if (SideIndex < LimitsCache.Top)
	{
		++CurrentIndex.X;
	}
	else if (SideIndex < LimitsCache.Right)
	{
		++CurrentIndex.Y;
	}
	else
	{
		if (CirceYSize > 1 && CirceXSize > 1)
		{
			if (SideIndex < LimitsCache.Bottom)
				--CurrentIndex.X;
			else if (SideIndex < LimitsCache.Left)
				--CurrentIndex.Y;
			else
				NextCircle();
		}
		else
		{
			NextCircle();
		}
	}
}

void FSpiralAccessMatrixIndicesRange::Iterator::UpdateLimitsCache()
{
	LimitsCache.Top = CirceXSize;
	LimitsCache.Right = LimitsCache.Top + (CirceYSize - 1);
	LimitsCache.Bottom = LimitsCache.Right + (CirceXSize - 1);
	LimitsCache.Left = LimitsCache.Bottom + (CirceYSize - 2);
}

// - - - - - - - - - - - - -

FSpiralAccessMatrixIndicesRange::FSpiralAccessMatrixIndicesRange(const int32 InXSize, const int32 InYSize)
	: XSize(InXSize), YSize(InYSize) { }

FSpiralAccessMatrixIndicesRange::Iterator FSpiralAccessMatrixIndicesRange::begin() const
{
	return { XSize, YSize };
}

FSpiralAccessMatrixIndicesRange::Iterator FSpiralAccessMatrixIndicesRange::end() const
{
	return { 0, 0 };
}
