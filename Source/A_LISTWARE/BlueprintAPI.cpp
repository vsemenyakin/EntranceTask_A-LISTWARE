#include "BlueprintAPI.h"
#include "ParseInt/ParseInt.h"
#include "SpiralPrint/SpiralPrint.h"

namespace BlueprintAPILocal
{
	static TOptional<TMatrix2D<int32>> TestMatrix;
}

FBPOptional_Int32 UBlueprintAPI::FromString_Int32(const FString& String)
{
	return StringToNumber(String);
}

FTransform UBlueprintAPI::CalculateTransformForUniformTextFitting(const UTextRenderComponent* Text, const FTextFittingMarginsSetup& Margins)
{
	return ::CalculateTransformForUniformTextFitting(Text, Margins);
}

FString UBlueprintAPI::RandomizeNewTestMatrix(int32 XSize, int32 YSize)
{
	if (XSize <= 0 || YSize <= 0)
		return TEXT("Invalid arguments passed");
	
	BlueprintAPILocal::TestMatrix = TMatrix2D<int32>{ XSize, YSize };

	static constexpr int32 MinNumber = 0;
	static constexpr int32 MaxNumber = 30;
	for (int32 Y = 0; Y < YSize; ++Y)
		for (int32 X = 0; X < XSize; ++X)
			BlueprintAPILocal::TestMatrix.GetValue().GetRef(X, Y) = FMath::RandRange(MinNumber, MaxNumber);
	
	return BlueprintAPILocal::TestMatrix.GetValue().ToString();
}

FString UBlueprintAPI::SpiralPrintForTestMatrix(const int32 NumbersInLine)
{
	using namespace BlueprintAPILocal;
	
	return BlueprintAPILocal::TestMatrix.IsSet() ?
		SpiralPrint(BlueprintAPILocal::TestMatrix.GetValue(), NumbersInLine) :
		TEXT("No test matrix was set");
}
