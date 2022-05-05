// Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "CASEditorSubsystem.h"
#include "EditorUtilityWidget.h"
#include "CASDetailsWidget.h"
#include "CASSpawnBaseWidget.h"
#include "Components/ScrollBox.h"
#include "Components/HorizontalBox.h"
#include "Components/WidgetSwitcher.h"
#include "Components/WrapBox.h"
#include "CASControlWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CRISPASSETSTUDIO_API UCASControlWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	//PROPERTIES
	UPROPERTY(BlueprintReadOnly, Category = "CAS", meta = (BindWidget))
		UWrapBox* PluginControlsBox = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "CAS", meta = (BindWidget))
		UHorizontalBox* SwitcherControls = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "CAS", meta = (BindWidget))
		UWidgetSwitcher* Switcher = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "CAS", meta = (BindWidgetOptional))
		UWrapBox* LightsContainer = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "CAS", meta = (BindWidgetOptional))
		UWrapBox* MeshesContainer = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "CAS", meta = (BindWidgetOptional))
		UWrapBox* OthersContainer = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		TSubclassOf<UCASDetailsWidget> DetailsClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		TSubclassOf<UCASSpawnBaseWidget> SpawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		TSubclassOf<UCASSpawnBaseWidget> LightSpawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		TSubclassOf<ACASGroupRep> GroupClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		UDataTable* Table;

	//FUNCTIONS
	virtual void SynchronizeProperties() override;

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void RespondToActorAdded(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void FlipMultiple();

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void DetachMultiple();

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void CreateGroup();

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void AddDetailsWidget(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void BuildWidget();

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void BuildTab(UWrapBox*& Container, FString TabName);

protected:
	virtual void NativeConstruct() override;
	virtual void BeginDestroy() override;

private:
	UCASEditorSubsystem* CAS = nullptr;
	UButton* BuildButton(FText buttonLabel, TSubclassOf<UButton> buttonClass);//TODO: add a class for this
};
