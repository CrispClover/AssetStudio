// Copyright Crisp Clover. Feel free to copy.

#include "CASSwitcherButton.h"

TSharedRef<SWidget> UCASSwitcherButton::RebuildWidget()
{
	TSharedRef<SWidget> widget = Super::RebuildWidget();

	OnClicked.AddDynamic(this, &UCASSwitcherButton::Switch);

	return widget;
}

void UCASSwitcherButton::Switch()
{
	if (!Switcher)
		return;

	Switcher->SetActiveWidgetIndex(Index);
	TArray<UWidget*> siblings = GetParent()->GetAllChildren();

	for (UWidget* sibling : siblings)
		if (UCASSwitcherButton* button = Cast<UCASSwitcherButton>(sibling))
			button->SetIsEnabled(button != this);
}
