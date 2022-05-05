// Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "CASLocalLight.h"
#include "Components/SpotLightComponent.h"
#include "CASSpotLight.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CRISPASSETSTUDIO_API ACASSpotLight : public ACASLocalLight
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Light")
		TObjectPtr<class USpotLightComponent> SpotLightComponent;

private:
	UPROPERTY()
		TObjectPtr<class UArrowComponent> ArrowComponent;

};
