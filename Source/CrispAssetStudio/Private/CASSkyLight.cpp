// Copyright Crisp Clover. Feel free to copy.

#include "CASSkyLight.h"
#include "Components/SkyLightComponent.h"

ACASSkyLight::ACASSkyLight(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	RootComponent->Mobility = EComponentMobility::Movable;

	if (USkyLightComponent* comp = GetLightComponent())
		comp->SourceType = ESkyLightSourceType::SLS_SpecifiedCubemap;
}