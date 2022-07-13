// Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CASEditorSubsystem.h"
#include "CASCalibrator.generated.h"

/**
 * 
 */
UCLASS()
class CRISPASSETSTUDIO_API ACASCalibrator : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Studio")
		TObjectPtr<class UStaticMeshComponent> Calibrator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		FLinearColor ReferenceColour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		FLinearColor SceneColour;

protected:
	virtual void OnConstruction(const FTransform& transform) override;

private:
	UCASEditorSubsystem* CAS = nullptr;
};
