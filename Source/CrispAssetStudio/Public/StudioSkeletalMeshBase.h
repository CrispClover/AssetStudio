//Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "StudioMeshBase.h"
#include "StudioSkeletalMeshBase.generated.h"

/**
 * 
 */
UCLASS()
class CRISPASSETSTUDIO_API AStudioSkeletalMeshBase : public AStudioMeshBase
{
	GENERATED_UCLASS_BODY()

protected:
	virtual void OnConstruction(const FTransform& transform) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup")
		TObjectPtr<USkeletalMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup")
		TObjectPtr<UAnimationAsset> Animation;

	virtual bool ToggleWireframe() override;
};
