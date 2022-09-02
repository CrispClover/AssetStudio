// Copyright Crisp Clover. Feel free to copy.

#include "CASRectLight.h"

ACASRectLight::ACASRectLight(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<URectLightComponent>(TEXT("LightComponent0")))
{
	RectLightComponent = CastChecked<URectLightComponent>(GetLightComponent());
	RectLightComponent->Mobility = EComponentMobility::Movable;
}

void ACASRectLight::AdjustDistance(FVector boxDifference)
{
	Super::AdjustDistance(boxDifference);

	FVector wv = GetLightComponent()->GetRightVector() * boxDifference;
	float w = RectLightComponent->SourceWidth * wv.Length();
	RectLightComponent->SetSourceWidth(w);

	FVector hv = GetLightComponent()->GetUpVector() * boxDifference;
	float h = RectLightComponent->SourceHeight * hv.Length();
	RectLightComponent->SetSourceHeight(h);
}
