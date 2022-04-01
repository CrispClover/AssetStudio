//Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "StudioMeshBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class CRISPASSETSTUDIO_API AStudioMeshBase : public AStudioActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& transform) override;

	bool wireframe = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Studio", meta = (ExposeFunctionCategories = "Mesh,Rendering,Components|Mesh", AllowPrivateAccess = "true"))
		TObjectPtr<class UMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Studio", meta = (ExposeFunctionCategories = "Mesh,Rendering,Components|Mesh", AllowPrivateAccess = "true"))
		TObjectPtr<class UMeshComponent> WireframeComponent;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup|Materials")
		UMaterialInterface* SimpleMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup|MaterialData")
		FLinearColor SimpleDiffuse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup|MaterialData")
		FLinearColor SimpleEmissive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup|Materials")
		UMaterialInterface* WireframeMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup|MaterialData")
		FLinearColor WireframeEmissive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup|MaterialData")
		float WireframeOffset;

	/**
	* @return false if the material hasn't been set, or if the MeshComponent isn't set.
	*/
	UFUNCTION(BlueprintCallable, Category = "Studio")
		bool ToggleSimpleMaterial();

	/**
	* @return false if the wireframe material hasn't been set.
	*/
	UFUNCTION(BlueprintCallable, Category = "Studio")
		virtual bool ToggleWireframe();

	UFUNCTION(BlueprintCallable, Category = "Studio")
		void UpdateMaterialData();

private:
	TArray<UMaterialInterface*> originalMaterials;
	bool simpleMat = false;
};