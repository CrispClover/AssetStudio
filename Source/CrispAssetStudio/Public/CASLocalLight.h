// Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Light.h"
#include "Components/LocalLightComponent.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Studio", meta = (ExposeOnSpawn = true))
		FRotator BaseRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Studio", meta = (ExposeOnSpawn = true))
		FRotator TypeRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS", meta = (ExposeOnSpawn = true, UIMin = 0))
		float Distance = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS", meta = (UIMin = -360, UIMax = 360))
		float Pitch = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS", meta = (UIMin = -360, UIMax = 360))
		float Yaw = 0.f;

	UFUNCTION(BlueprintCallable, Category = "CAS")
		virtual void Flip();

	UFUNCTION(BlueprintCallable, Category = "CAS")
		virtual void ApplyProperties();

	UFUNCTION(BlueprintCallable, Category = "CAS")
		virtual void AdjustDistance(FVector const& BoxDifference);

protected:
	void SetDistance();
	void SetRotation();
	bool bYawIsFlipped;
};
