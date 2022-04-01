//Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "StudioMeshBase.h"
#include "StudioStaticMeshBase.generated.h"

/**
 *
 */
UCLASS(Blueprintable, Abstract)
class CRISPASSETSTUDIO_API AStudioStaticMeshBase : public AStudioMeshBase
{
	GENERATED_UCLASS_BODY()

protected:
	virtual void OnConstruction(const FTransform& transform) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StudioSetup")
		TObjectPtr<UStaticMesh> Mesh;

	virtual bool ToggleWireframe() override;
};
