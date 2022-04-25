// Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "CASCamera.h"
#include "CASCineCamera.generated.h"

class UCineCameraComponent;

/**
 * 
 */
UCLASS(Blueprintable)
class CRISPASSETSTUDIO_API ACASCineCamera : public ACASCamera
{
	GENERATED_BODY()

public:
	ACASCineCamera(const FObjectInitializer& ObjectInitializer);

	virtual bool ShouldTickIfViewportsOnly() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		float FocusOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		bool FocusPlane;

	UFUNCTION(BlueprintCallable, Category = "Camera")
		UCineCameraComponent* GetCineCameraComponent() const { return CineCameraComponent; }

protected:
	uint8 bResetInterplation : 1;
	virtual void ApplyProperties() override;
	virtual void NotifyCameraCut() override;

private:
	UCineCameraComponent* CineCameraComponent;
};
