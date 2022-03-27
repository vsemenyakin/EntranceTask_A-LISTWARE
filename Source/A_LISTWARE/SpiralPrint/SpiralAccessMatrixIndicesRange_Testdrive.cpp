#include "SpiralAccessMatrixIndicesRange_Testdrive.h"
#include "SpiralAccessMatrixIndicesRange.h"
//#include "ToString.h"//for "TMatrix2D<int32>" ToString() - trying to fix compile error
#include "Matrix2D.h"

namespace SpiralAccessMatrixIndicesRange_Testdrive_Local
{
	void RunTestdrive_SpiralAccessMatrixIndicesRange_ForSize(const int32 XSize, const int32 YSize)
	{
		TMatrix2D<int32> Matrix{ XSize, YSize };

		int32 Counter = 0;
		for (const FMatrixIndex MatrixIndex : FSpiralAccessMatrixIndicesRange{ XSize, YSize })
			Matrix.GetRef(MatrixIndex.X, MatrixIndex.Y) = (Counter++);

		UE_LOG(LogTemp, Log,
			TEXT("%s\n")
			TEXT(" ---------- "),
			*Matrix.ToString());
	}
}

void RunTestdrive_SpiralAccessMatrixIndicesRange()
{
	using namespace SpiralAccessMatrixIndicesRange_Testdrive_Local;

	const FMatrixIndex MinSize{ 1, 1 };
	const FMatrixIndex MaxSize{ 5, 5 };
	
	for (int32 XSize = MinSize.X; XSize <= MaxSize.X; ++XSize)
		for (int32 YSize = MinSize.Y; YSize <= MaxSize.Y; ++YSize)
			RunTestdrive_SpiralAccessMatrixIndicesRange_ForSize(XSize, YSize);
}