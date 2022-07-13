// Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "CASSwitcherButton.generated.h"

/**
 * 
 */
UCLASS()
class CRISPASSETSTUDIO_API UCASSwitcherButton : public UButton
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "UI")
		UWidgetSwitcher* Switcher;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI")
		int32 Index;

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

private:
	UFUNCTION()
		void Switch();
};
