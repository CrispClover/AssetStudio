// Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "CASStudioEnvironment.generated.h"

UCLASS()
class CRISPASSETSTUDIO_API ACASStudioEnvironment : public AActor
{
	GENERATED_UCLASS_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(FTransform const& transform) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Studio", meta = (ExposeFunctionCategories = "Mesh,Rendering,Components|StaticMesh", AllowPrivateAccess = "true"))
		TObjectPtr<class UStaticMeshComponent> Sky;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Studio", meta = (ExposeFunctionCategories = "Mesh,Rendering,Components|StaticMesh", AllowPrivateAccess = "true"))
		TObjectPtr<class UStaticMeshComponent> Floor;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|Meshes")
		TObjectPtr<UStaticMesh> SkyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|Meshes")
		TObjectPtr<UStaticMesh> FloorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|Materials")
		UMaterialInterface* LitFloorMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|Materials")
		UMaterialInterface* UnlitMaterial;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|Materials")
		//UMaterialInterface* HDRMaterial;//TODO?

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|MaterialData")
		FLinearColor BackgroundColour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|MaterialData")
		FLinearColor GradientColour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|MaterialData")
		FVector2D GradientOrigin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|MaterialData")
		float GradientScreenSlope = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|MaterialData")
		float GradientAlpha = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS", meta = (UIMin = "0.0"))
		float Scale = 1;

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void ReInit();

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void UpdateMaterialData();

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void SetScale();

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void ToggleFloor();

	/**
	* @return false if the floor materials haven't been set.
	*/
	UFUNCTION(BlueprintCallable, Category = "CAS")
		bool ToggleUnlitFloor();

protected:
	bool visibleFloor = true;
	bool litFloor = true;
};
