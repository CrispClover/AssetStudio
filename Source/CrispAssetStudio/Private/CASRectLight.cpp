// Copyright Crisp Clover. Feel free to copy.

#include "CASRectLight.h"

ACASRectLight::ACASRectLight(FObjectInitializer const& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<URectLightComponent>(TEXT("LightComponent0")))
{
	RectLightComponent = CastChecked<URectLightComponent>(GetLightComponent());
	RectLightComponent->Mobility = EComponentMobility::Movable;
}

void ACASRectLight::AdjustDistance(FVector const& boxDifference)
{
	Super::AdjustDistance(boxDifference);

	const FVector wv = GetLightComponent()->GetRightVector() * boxDifference;
	const float w = RectLightComponent->SourceWidth * wv.Length();
	RectLightComponent->SetSourceWidth(w);

	const FVector hv = GetLightComponent()->GetUpVector() * boxDifference;
	const float h = RectLightComponent->SourceHeight * hv.Length();
	RectLightComponent->SetSourceHeight(h);
}
