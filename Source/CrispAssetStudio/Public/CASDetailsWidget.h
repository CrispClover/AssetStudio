// Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "CASEditorSubsystem.h"
#include "EditorUtilityWidget.h"
#include "Components/VerticalBox.h"
#include "Components/EditableTextBox.h"
#include "Components/DetailsView.h"
#include "CASDetailsWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CRISPASSETSTUDIO_API UCASDetailsWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "CAS", meta = (BindWidget))
		UVerticalBox* Container = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "CAS", meta = (BindWidget))
		UEditableTextBox* NameBox = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "CAS", meta = (BindWidget))
		UDetailsView* ActorView = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "CAS", meta = (BindWidget))
		UDetailsView* ComponentView = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS", meta = (ExposeOnSpawn = true))
		AActor* Actor;

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void RespondToActorDeleted(AActor* InActor);

protected:
	virtual void NativeConstruct() override;

private:
	UCASEditorSubsystem* CAS = nullptr;
};
