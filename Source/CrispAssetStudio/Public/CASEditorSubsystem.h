//Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "CASEditorSubsystem.generated.h"

UENUM()
enum class ECASType : uint8
{
	none,
	Light,
	GroupRep,
	Mesh,
	Other
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActorAdded, AActor*, actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActorDeleted, AActor*, actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCalcColours, ACASGroupRep*, rep, uint8, blendMode);

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

	UPROPERTY(BlueprintAssignable, Category = "CAS")
		FCalcColours CalcColoursEvent;

	UFUNCTION(BlueprintCallable, Category = "CAS")
		static ECASType GetCASType(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "CAS")
		TArray<AActor*> GetRelevantActors();

	UFUNCTION(BlueprintCallable, Category = "CAS")
		TArray<ALight*> GetSelectedLights();

	UFUNCTION(BlueprintCallable, Category = "CAS")
		TArray<AActor*> GetSelectedActors();

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void CreateGroup(TSubclassOf<ACASGroupRep> GroupClass);

	void OnLevelActorAdded(AActor* Actor);
	void OnLevelActorDeleted(AActor* Actor);

	TSharedPtr<class FCASBroadcast> CASBroadcast;
};
