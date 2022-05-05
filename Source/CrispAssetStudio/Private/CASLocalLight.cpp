// Copyright Crisp Clover. Feel free to copy.

#include "CASLocalLight.h"
#include "Kismet/KismetMathLibrary.h"

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

void ACASLocalLight::SetDistance()
{
	GetLightComponent()->SetRelativeLocation(FVector(-Distance, 0, 0));
}

void ACASLocalLight::SetRotation()
{
	FRotator rot;

	if (bYawIsFlipped)
		rot = UKismetMathLibrary::ComposeRotators(FRotator(Pitch, -Yaw, 0), UKismetMathLibrary::ComposeRotators(BaseRotation, FRotator(TypeRotation.Pitch, -TypeRotation.Yaw, TypeRotation.Roll)));
	else
		rot = UKismetMathLibrary::ComposeRotators(FRotator(Pitch, Yaw, 0), UKismetMathLibrary::ComposeRotators(BaseRotation, TypeRotation));

	SetActorRelativeRotation(rot);
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