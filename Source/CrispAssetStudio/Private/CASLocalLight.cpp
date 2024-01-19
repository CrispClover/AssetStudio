// Copyright Crisp Clover. Feel free to copy.

#include "CASLocalLight.h"
#include "Kismet/KismetMathLibrary.h"

ACASLocalLight::ACASLocalLight(FObjectInitializer const& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<ULocalLightComponent>(TEXT("LightComponent0")))
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	if (GetLightComponent())
	{
		GetLightComponent()->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

		static const auto CVarDefaultLightUnits = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("r.DefaultFeature.LightUnits"));
		const ELightUnits DefaultUnits = (ELightUnits)CVarDefaultLightUnits->GetValueOnAnyThread();
		CastChecked<ULocalLightComponent>(GetLightComponent())->SetIntensityUnits(DefaultUnits);

		ApplyProperties();
	}
}

void ACASLocalLight::OnConstruction(FTransform const& transform)
{
	Super::OnConstruction(transform);
	ApplyProperties();
}

void ACASLocalLight::AdjustDistance(FVector const& boxDifference)
{
	const FVector d = GetLightComponent()->GetForwardVector() * boxDifference;

	Distance = Distance * d.Length();

	SetDistance();
}

void ACASLocalLight::SetDistance()
{
	GetLightComponent()->SetRelativeLocation(FVector(-Distance, 0, 0));
}

void ACASLocalLight::SetRotation()
{
	const int32 yM = -(int32)bYawIsFlipped * 2 + 1;//-1 when flipped, 1 when not flipped
	SetActorRelativeRotation(UKismetMathLibrary::ComposeRotators(FRotator(TypeRotation.Pitch + Pitch, yM * (TypeRotation.Yaw + Yaw), TypeRotation.Roll), BaseRotation));
}

void ACASLocalLight::Flip()
{
	bYawIsFlipped = !bYawIsFlipped;
	SetRotation();
}

void ACASLocalLight::ApplyProperties()
{
	SetDistance();
	SetRotation();
}
