// Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "CASMeshBase.h"
#include "CASSkeletalMesh.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CRISPASSETSTUDIO_API ACASSkeletalMesh : public ACASMeshBase
{
	GENERATED_UCLASS_BODY()

protected:
	virtual void OnConstruction(FTransform const& transform) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		TObjectPtr<USkeletalMesh> Mesh;

	virtual bool ToggleWireframe() override;
};
