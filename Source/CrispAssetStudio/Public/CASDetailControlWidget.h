// Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "CASEditorSubsystem.h"
#include "EditorUtilityWidget.h"
#include "CASDetailsWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/WidgetSwitcher.h"
#include "Components/WrapBox.h"
#include "CASDetailControlWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CRISPASSETSTUDIO_API UCASDetailControlWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	//PROPERTIES
	UPROPERTY(BlueprintReadOnly, Category = "CAS", meta = (BindWidget))
		UHorizontalBox* SwitcherControls = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "CAS", meta = (BindWidget))
		UWidgetSwitcher* Switcher = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "CAS")
		TMap<FName, UWrapBox*> Containers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		TMap<ECASType, FName> TabSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		TSubclassOf<UCASDetailsWidget> DetailsClass;

	//FUNCTIONS
	UFUNCTION(BlueprintCallable, Category = "CAS")
		void RespondToActorAdded(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void AddDetailsWidget(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void BuildWidget();

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void BuildTab(FName TabName);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UCASEditorSubsystem* CAS = nullptr;
};
