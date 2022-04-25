// Copyright Crisp Clover. Feel free to copy.

#include "CASLocalLight.h"
#include "Components/RectLightComponent.h"

ACASLocalLight::ACASLocalLight(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<ULocalLightComponent>(TEXT("LightComponent0")))
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	if (GetLightComponent())
	{
		GetLightComponent()->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

		static const auto CVarDefaultLightUnits = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("r.DefaultFeature.LightUnits"));
		ELightUnits DefaultUnits = (ELightUnits)CVarDefaultLightUnits->GetValueOnAnyThread();
		CastChecked<ULocalLightComponent>(GetLightComponent())->SetIntensityUnits(DefaultUnits);

		ApplyProperties();
	}
}

void ACASLocalLight::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);
	ApplyProperties();
}

void ACASLocalLight::SetDistance(float newDistance)
{
	GetLightComponent()->SetRelativeLocation(FVector(-newDistance, 0, 0));
}

void ACASLocalLight::ApplyProperties()
{
	SetDistance(Distance);
	SetActorRotation(FRotator(Pitch, Yaw, 0));
}