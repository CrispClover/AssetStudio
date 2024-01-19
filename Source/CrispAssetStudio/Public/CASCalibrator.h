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

protected:
	virtual void OnConstruction(FTransform const& transform) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Studio")
		TObjectPtr<class UStaticMeshComponent> Calibrator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		FLinearColor ReferenceColour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		FLinearColor SceneColour;

private:
	UCASEditorSubsystem* CAS = nullptr;
};
