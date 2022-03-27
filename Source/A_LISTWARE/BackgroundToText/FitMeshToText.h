#pragma once

#include "FitMeshToText.generated.h"

class UTextRenderComponent;

USTRUCT(BlueprintType)
struct FTextFittingMarginsSetup
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Left = 0.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Right = 0.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Top = 0.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Bottom = 0.f;
};

// - - - - - - - - - - - -

FTransform CalculateTransformForUniformTextFitting(const UTextRenderComponent* Text, const FTextFittingMarginsSetup& Margins);
