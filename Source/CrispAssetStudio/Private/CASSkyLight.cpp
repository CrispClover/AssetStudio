// Copyright Crisp Clover. Feel free to copy.

#include "CASSkyLight.h"
#include "Components/SkyLightComponent.h"

ACASSkyLight::ACASSkyLight(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	RootComponent->Mobility = EComponentMobility::Movable;

	if (USkyLightComponent* comp = GetLightComponent())
		comp->SourceType = ESkyLightSourceType::SLS_SpecifiedCubemap;

	Calibrator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Calibrator"));
	Calibrator->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	Calibrator->Mobility = EComponentMobility::Static;
	Calibrator->SetGenerateOverlapEvents(false);
	Calibrator->bUseDefaultCollision = true;
	Calibrator->SetHiddenInGame(true);
	Calibrator->SetVisibility(false);
	Calibrator->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	Calibrator->SetRelativeLocation(FVector(-200, -200, 40));
}

void ACASSkyLight::ToggleCalibrator()
{
	Calibrator->ToggleVisibility();
}