#include "SpiralPrint.h"
#include "SpiralAccessMatrixIndicesRange.h"
#include "ToString.h"

FString SpiralPrint(const TMatrix2D<int32>& Matrix, const int32 NumbersInLine)
{
	int32 CurrentNumbersInLineNum = 0;

	static const FString NumbersDelimiter{ TEXT("  ") };
	
	FString Result;

	for (const FMatrixIndex MatrixIndex : FSpiralAccessMatrixIndicesRange{ Matrix.GetXSize(), Matrix.GetYSize() })
	{
		if (CurrentNumbersInLineNum != 0)
			Result += NumbersDelimiter;

		Result += ToString(Matrix.GetRef(MatrixIndex.X, MatrixIndex.Y));
		++CurrentNumbersInLineNum;
		
		if (CurrentNumbersInLineNum == NumbersInLine)
		{
			Result += '\n';
			CurrentNumbersInLineNum = 0;
		}
	}

	return Result;
}
