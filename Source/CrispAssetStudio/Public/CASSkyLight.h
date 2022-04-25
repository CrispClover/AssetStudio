// Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "Engine/SkyLight.h"
#include "CASSkyLight.generated.h"

/**
 * 
 */
UCLASS()
class CRISPASSETSTUDIO_API ACASSkyLight : public ASkyLight
{
	GENERATED_UCLASS_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Studio", meta = (ExposeFunctionCategories = "Mesh,Rendering,Components|StaticMesh", AllowPrivateAccess = "true"))
		TObjectPtr<class UStaticMeshComponent> Calibrator;

public:
	UFUNCTION(BlueprintCallable, Category = "CAS")
		void ToggleCalibrator();
};
