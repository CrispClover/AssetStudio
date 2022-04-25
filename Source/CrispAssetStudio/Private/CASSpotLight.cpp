// Copyright Crisp Clover. Feel free to copy.


#include "CASSpotLight.h"
#include "Components/ArrowComponent.h"
#include "Components/SpotLightComponent.h"

ACASSpotLight::ACASSpotLight(const FObjectInitializer& ObjectInitializer)
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
