#pragma once

#include "BackgroundToText/FitMeshToText.h"//for FTextFittingMarginsSetup

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreMinimal.h"
#include "BlueprintAPI.generated.h"

class UTextRenderComponent;
struct FTextFittingMarginsSetup;

// - - - - - - - - - - - - - - - - - - -

USTRUCT(BlueprintType)
struct FBPOptional_Int32
{
	GENERATED_BODY()

	FBPOptional_Int32() = default;

	FBPOptional_Int32(const TOptional<int32>& CppOptional)
		: Value(CppOptional.Get(0)), bIsSet(CppOptional.IsSet()) { }
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Value = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsSet = false;
};

// - - - - - - - - - - - - - - - - - - -

UCLASS()
class A_LISTWARE_API UBlueprintAPI : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static FBPOptional_Int32 FromString_Int32(const FString& String);

	UFUNCTION(BlueprintPure)
	static FTransform CalculateTransformForUniformTextFitting(const UTextRenderComponent* Text, const FTextFittingMarginsSetup& Margins);

	UFUNCTION(BlueprintCallable)
	static FString RandomizeNewTestMatrix(const int32 XSize, int32 YSize);
	
	UFUNCTION(BlueprintCallable)
	static FString SpiralPrintForTestMatrix(const int32 NumbersInLine = 5);
};
