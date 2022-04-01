//Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/Classes/Components/SkyLightComponent.h"
#include "StudioEnvironmentBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class CRISPASSETSTUDIO_API AStudioEnvironmentBase : public AStudioActor
{
	GENERATED_UCLASS_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Studio", meta = (ExposeFunctionCategories = "Mesh,Rendering,Components|StaticMesh", AllowPrivateAccess = "true"))
		TObjectPtr<class UStaticMeshComponent> Sky;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Studio", meta = (ExposeFunctionCategories = "Mesh,Rendering,Components|StaticMesh", AllowPrivateAccess = "true"))
		TObjectPtr<class UStaticMeshComponent> Floor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Studio", meta = (ExposeFunctionCategories = "Light,Rendering,Rendering|Components|SkyLight", AllowPrivateAccess = "true"))
		TObjectPtr<class USkyLightComponent> Skylight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Studio", meta = (ExposeFunctionCategories = "Mesh,Rendering,Components|StaticMesh", AllowPrivateAccess = "true"))
		TObjectPtr<class UStaticMeshComponent> Calibrator;

public:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& transform) override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup|Meshes")
		TObjectPtr<UStaticMesh> SkyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup|Meshes")
		TObjectPtr<UStaticMesh> FloorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup|Materials")
		UMaterialInterface* LitFloorMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup|Materials")
		UMaterialInterface* UnlitMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup|MaterialData")
		FLinearColor BackgroundColour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup|Materials")
		UMaterialInterface* GradientSkyMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup|MaterialData")
		FLinearColor GradientColour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup|MaterialData")
		float GradientZInfluence = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup|MaterialData")
		float GradientZSlope = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup|MaterialData")
		float GradientScreenSlope = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup|MaterialData")
		FVector2D GradientOrigin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup", meta = (UIMin = "0.0"))
		float Scale = 1;

	UFUNCTION(BlueprintCallable, Category = "Studio")
		void ReInit();

	UFUNCTION(BlueprintCallable, Category = "Studio")
		void UpdateMaterialData();

	UFUNCTION(BlueprintCallable, Category = "Studio")
		void SetScale();

	UFUNCTION(BlueprintCallable, Category = "Studio")
		void ToggleFloor();

	/**
	* @return false if the floor materials haven't been set.
	*/
	UFUNCTION(BlueprintCallable, Category = "Studio")
		bool ToggleUnlitFloor();

	/**
	* @return false if the sky materials haven't been set.
	*/
	UFUNCTION(BlueprintCallable, Category = "Studio")
		bool ToggleSkyGradient();

	UFUNCTION(BlueprintCallable, Category = "Studio")
		void ToggleCalibrator();

protected:
	bool visibleFloor = true;
	bool litFloor = true;
	bool gradient = true;
};
