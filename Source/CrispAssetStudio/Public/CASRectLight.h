// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CASLocalLight.h"
#include "Components/RectLightComponent.h"
#include "CASRectLight.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CRISPASSETSTUDIO_API ACASRectLight : public ACASLocalLight
{
	GENERATED_UCLASS_BODY()

public:
	virtual void AdjustDistance(FVector BoxDifference) override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Light")
		TObjectPtr<class URectLightComponent> RectLightComponent;
};
