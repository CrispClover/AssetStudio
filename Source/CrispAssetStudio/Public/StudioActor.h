//Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StudioActor.generated.h"

UCLASS(Abstract)
class CRISPASSETSTUDIO_API AStudioActor : public AActor
{
	GENERATED_BODY()

public:
	virtual void OnConstruction(const FTransform& transform) override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
		void UpdateProperties();
};
