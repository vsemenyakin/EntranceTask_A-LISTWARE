#include "FitMeshToText.h"
#include "Components/TextRenderComponent.h"

FTransform CalculateTransformForUniformTextFitting(const UTextRenderComponent* Text, const FTextFittingMarginsSetup& Margins)
{
	check(Text);

	const FBoxSphereBounds Bounds = Text->CalcBounds(FTransform::Identity);

	const float SizeX = Bounds.BoxExtent.Y * 2.f;
	const float SizeY = Bounds.BoxExtent.Z * 2.f;

	const float XStart = -SizeX;
	const float XEnd = SizeX;
	const float YStart = -SizeY;
	const float YEnd = SizeY;

	FTransform Transform{ };

	FVector Translation;
	Translation.X = Transform.GetTranslation().X;
	Translation.Y = (XStart - Margins.Left) + ((XEnd + Margins.Right) - (XStart - Margins.Left)) / 2.f;
	Translation.Z = (YStart - Margins.Bottom) + ((YEnd + Margins.Top) - (YStart - Margins.Bottom)) / 2.f;
	Transform.SetTranslation(Translation);

	const FVector Rotation{ 90.f, 0.f, -90.f };
	Transform.SetRotation(FQuat::MakeFromEuler(Rotation));

	FVector Scale;
	const float UnitsToScale = 0.01f;
	Scale.X = (SizeX + Margins.Left + Margins.Right) * UnitsToScale;
	Scale.Y = (SizeY + Margins.Bottom + Margins.Top) * UnitsToScale;
	Scale.Z = Transform.GetScale3D().Z;
	Transform.SetScale3D(Scale);

	return Transform;
}
