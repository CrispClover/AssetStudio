// Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CASCamera.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CRISPASSETSTUDIO_API ACASCamera : public ACameraActor
{
	GENERATED_BODY()

public:
	ACASCamera(const FObjectInitializer& ObjectInitializer);
	virtual void OnConstruction(const FTransform& transform) override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|Reference")
		UMaterialInterface* RefImgMaterial;

	UPROPERTY(BlueprintReadOnly, Category = "CAS")
		UMaterialInstanceDynamic* RefDynamicInstance = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS", meta = (UIMin = 0))
		float Distance = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|Reference", meta = (UIMin = 0.f, UIMax = 1.f))
		float Alpha = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|Reference")
		FVector2D Crop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|Reference")
		FVector2D Shift;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|Reference")
		UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|Reference")
		bool FlipU;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|Reference")
		bool FlipV;

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void UpdateRefImgMatData();

	/**
	* @return false if the reference image material hasn't been set.
	*/
	UFUNCTION(BlueprintCallable, Category = "CAS")
		bool ToggleReferenceImage();

protected:
	virtual void ApplyProperties();

private:
	bool showReferenceImage;
};
