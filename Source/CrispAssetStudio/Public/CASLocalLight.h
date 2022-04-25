// Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Light.h"
#include "CASLocalLight.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class CRISPASSETSTUDIO_API ACASLocalLight : public ALight
{
	GENERATED_BODY()

public:
	ACASLocalLight(const FObjectInitializer& ObjectInitializer);
	virtual void OnConstruction(const FTransform& transform) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS", meta = (ExposeOnSpawn = true, UIMin = 0))
		float Distance = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS", meta = (ExposeOnSpawn = true, UIMin = -360, UIMax = 360))
		float Pitch = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS", meta = (ExposeOnSpawn = true, UIMin = -360, UIMax = 360))
		float Yaw = 0.f;

	UFUNCTION(BlueprintCallable, Category = "CAS")
		virtual void ApplyProperties();

protected:
	void SetDistance(float newDistance);
};
