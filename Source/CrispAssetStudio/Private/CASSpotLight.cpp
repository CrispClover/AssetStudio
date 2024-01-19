// Copyright Crisp Clover. Feel free to copy.


#include "CASSpotLight.h"
#include "Components/ArrowComponent.h"

ACASSpotLight::ACASSpotLight(FObjectInitializer const& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USpotLightComponent>(TEXT("LightComponent0")))
{
	SpotLightComponent = CastChecked<USpotLightComponent>(GetLightComponent());
	SpotLightComponent->Mobility = EComponentMobility::Movable;

	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent0"));
	ArrowComponent->ArrowColor = GetLightColor().ToFColor(true);
	ArrowComponent->bTreatAsASprite = true;
	ArrowComponent->SetupAttachment(SpotLightComponent);
	ArrowComponent->bLightAttachment = true;
	ArrowComponent->bIsScreenSizeScaled = true;
}

void ACASSpotLight::AdjustDistance(FVector const& boxDifference)
{
	Super::AdjustDistance(boxDifference);

	const FVector wv = GetLightComponent()->GetRightVector() * boxDifference;
	const FVector hv = GetLightComponent()->GetUpVector() * boxDifference;
	
	const double m = FMath::Max(wv.Length(), hv.Length());

	SpotLightComponent->SetOuterConeAngle(SpotLightComponent->OuterConeAngle * m);
}
