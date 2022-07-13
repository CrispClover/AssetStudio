// Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "CASEditorSubsystem.h"
#include "EditorUtilityWidget.h"
#include "CASSpawnBaseWidget.h"
#include "Components/WrapBox.h"
#include "Components/DetailsView.h"
#include "CASPluginControlWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CRISPASSETSTUDIO_API UCASPluginControlWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "CAS", meta = (BindWidget))
		UWrapBox* PluginControlsBox = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "CAS")
		UButton* CalibratorToggle = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "CAS")
		UDetailsView* CalibratorView = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "CAS")
		UDetailsView* SequenceView = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderSettings")
		FDirectoryPath OutputPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		TSubclassOf<UCASSpawnBaseWidget> SpawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		TSubclassOf<UCASSpawnBaseWidget> LightSpawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		TSubclassOf<ACASGroupRep> GroupClass;

	//FUNCTIONS
	UFUNCTION(BlueprintCallable, Category = "CAS")
		void FlipMultiple();

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void DetachMultiple();

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void CreateGroup();

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void BuildWidget();

	UFUNCTION(BlueprintImplementableEvent, Category = "CAS")
		void ToggleCalibrator();

	UFUNCTION(BlueprintImplementableEvent, Category = "CAS")
		void QueueSelected();

	UFUNCTION(BlueprintImplementableEvent, Category = "CAS")
		void QueueAll();

protected:
	virtual void NativeConstruct() override;
	virtual void BeginDestroy() override;

private:
	UCASEditorSubsystem* CAS = nullptr;
	UButton* BuildButton(FText buttonLabel, TSubclassOf<UButton> buttonClass);//TODO: add a class for this
};
