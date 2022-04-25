// Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "Components/VerticalBox.h"
#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "CASSpawnBaseWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CRISPASSETSTUDIO_API UCASSpawnBaseWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "CAS", meta = (BindWidget))
		UVerticalBox* Container = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "CAS", meta = (BindWidget))
		UComboBoxString* Selector = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "CAS", meta = (BindWidget))
		UButton* Button = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "CAS", meta = (BindWidget))
		UTextBlock* Label = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "CAS")
		TSubclassOf<AActor> ActorClass = nullptr;
};
