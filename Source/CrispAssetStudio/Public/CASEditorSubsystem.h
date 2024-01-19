//Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "CASEditorSubsystem.generated.h"

UENUM(BlueprintType)
enum class ECASType : uint8
{
	none,
	LocalLight,
	GlobalLight,
	GroupRep,
	Camera,
	Mesh,
	Environment,
	Other
};

UENUM(BlueprintType)
enum class ERotCalcType : uint8
{
	PlanarRot	UMETA(DisplayName = "Planar Rotation", Description = "Rotation is best used when tracking (dolly). Planar calculations assume the scene to be horizontal."),
	PlanarPos	UMETA(DisplayName = "Planar Position", Description = "Position should be used when panning. Planar calculations assume the scene to be horizontal."),
	ThreeDRot	UMETA(DisplayName = "3D Rotation", Description = "Rotation is best used when tracking (dolly)."),
	ThreeDPos	UMETA(DisplayName = "3D Position", Description = "Position should be used when panning.")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActorAdded, AActor*, actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActorDeleted, AActor*, actor);

/**
 * 
 */
UCLASS()
class CRISPASSETSTUDIO_API UCASEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UPROPERTY(BlueprintAssignable, Category = "CAS")
		FActorAdded ActorAddedEvent;

	UPROPERTY(BlueprintAssignable, Category = "CAS")
		FActorDeleted ActorDeletedEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		ERotCalcType RotCalcType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		FLinearColor SceneColour = FLinearColor(1, 1, 1);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		FLinearColor ReferenceColour = FLinearColor(1, 1, 1);

	UFUNCTION(BlueprintCallable, Category = "CAS")
		static ECASType GetCASType(AActor const* Actor);

	UFUNCTION(BlueprintCallable, Category = "CAS")
		TArray<AActor*> GetRelevantActors() const;

	UFUNCTION(BlueprintCallable, Category = "CAS")
		TArray<AActor*> GetActorsOfType(const ECASType Type) const;

	UFUNCTION(BlueprintCallable, Category = "CAS")
		TArray<ALight*> GetSelectedLights() const;

	UFUNCTION(BlueprintCallable, Category = "CAS")
		TArray<AActor*> GetSelectedActors() const;

	/*UFUNCTION(BlueprintCallable, Category = "CAS")
		TArray<UMaterialInterface*> GetSelectedMaterials() const;*/

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void CreateGroup(const TSubclassOf<ACASGroupRep> GroupClass) const;

	UFUNCTION(BlueprintCallable, Category = "CAS")
		FRotator GetBaseRotator(USceneComponent const* ReferenceComponent, AActor const* Target) const;

	UFUNCTION(BlueprintCallable, Category = "CAS")
		FLinearColor GetCalibratedColour(FLinearColor const& LightColour) const;

	void OnLevelActorAdded(AActor* Actor) const;
	void OnLevelActorDeleted(AActor* Actor) const;

	TSharedPtr<class FCASBroadcast> CASBroadcast;
};
