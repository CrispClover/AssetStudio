// Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "CASEditorSubsystem.h"
#include "Components/GridPanel.h"
#include "Components/Button.h"
#include "CASActionsWidget.generated.h"

/**
 * 
 */
UCLASS()
class CRISPASSETSTUDIO_API UCASActionsWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()
	
public:
	virtual void SynchronizeProperties() override;

	UPROPERTY(BlueprintReadOnly, Category = "CAS", meta = (BindWidget))
		UGridPanel* Container = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "CAS", meta = (BindWidget))
		UButton* Delete = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS", meta = (ExposeOnSpawn = true))
		AActor* Actor;

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void DeleteActor();

protected:
	virtual void NativeConstruct() override;
};
