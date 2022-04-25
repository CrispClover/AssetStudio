// Copyright Crisp Clover. Feel free to copy.


#include "CASRectLight.h"

ACASRectLight::ACASRectLight(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<URectLightComponent>(TEXT("LightComponent0")))
{
	RectLightComponent = CastChecked<URectLightComponent>(GetLightComponent());
	RectLightComponent->Mobility = EComponentMobility::Movable;
}

