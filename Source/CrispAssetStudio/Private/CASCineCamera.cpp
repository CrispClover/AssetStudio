// Copyright Crisp Clover. Feel free to copy.

#include "CASCineCamera.h"
#include "DrawDebugHelpers.h"
#include "CineCameraComponent.h"

ACASCineCamera::ACASCineCamera(FObjectInitializer const& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCineCameraComponent>(TEXT("CameraComponent")))
{
	CineCameraComponent = Cast<UCineCameraComponent>(GetCameraComponent());

	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(true);
}

void ACASCineCamera::ApplyProperties()
{
	Super::ApplyProperties();
	CineCameraComponent->FocusSettings.ManualFocusDistance = Distance - FocusOffset;
	CineCameraComponent->FocusSettings.bDrawDebugFocusPlane = FocusPlane;
}

bool ACASCineCamera::ShouldTickIfViewportsOnly() const
{
	return true;
}

void ACASCineCamera::NotifyCameraCut()
{
	Super::NotifyCameraCut();

	bResetInterplation = true;
}