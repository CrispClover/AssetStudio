// Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CASMeshBase.generated.h"

UCLASS(Abstract)
class CRISPASSETSTUDIO_API ACASMeshBase : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(FTransform const& transform) override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|Materials")
		UMaterialInterface* SimpleMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|MaterialData")
		FLinearColor SimpleDiffuse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|MaterialData")
		FLinearColor SimpleEmissive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|Materials")
		UMaterialInterface* WireframeMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|MaterialData")
		FLinearColor WireframeEmissive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS|MaterialData")
		float WireframeOffset;

	/**
	* @return false if the material hasn't been set, or if the MeshComponent isn't set.
	*/
	UFUNCTION(BlueprintCallable, Category = "CAS")
		bool ToggleSimpleMaterial();

	/**
	* @return false if the wireframe material hasn't been set.
	*/
	UFUNCTION(BlueprintCallable, Category = "CAS")
		virtual bool ToggleWireframe();

	/**
	* This function uses primitive data to update the materials: 
	* For the simple material the first 6 indices are used,
	* for the wireframe material the first 4. (starting at 0)
	*/
	UFUNCTION(BlueprintCallable, Category = "CAS")
		void UpdateMaterialData();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Studio", meta = (ExposeFunctionCategories = "Mesh,Rendering,Components|Mesh", AllowPrivateAccess = "true"))
		TObjectPtr<class UMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Studio", meta = (ExposeFunctionCategories = "Mesh,Rendering,Components|Mesh", AllowPrivateAccess = "true"))
		TObjectPtr<class UMeshComponent> WireframeComponent;

	void OnMeshChange(FVector3d const& OldBoxExtent, FVector3d const& NewBoxExtent) const;

	bool wireframe = false;

private:
	TArray<UMaterialInterface*> originalMaterials;
	bool simpleMat = false;
};
