// Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "CASMeshBase.h"
#include "CASStaticMesh.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CRISPASSETSTUDIO_API ACASStaticMesh : public ACASMeshBase
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		TObjectPtr<UStaticMesh> Mesh;

	virtual bool ToggleWireframe() override;

protected:
	virtual void OnConstruction(const FTransform& transform) override;
};
