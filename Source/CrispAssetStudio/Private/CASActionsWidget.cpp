// Copyright Crisp Clover. Feel free to copy.

#include "CASActionsWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"

void UCASActionsWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (Delete)
	{
		Delete->SetBackgroundColor(FLinearColor(1,0,0));
		UTextBlock* label = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		label->SetText(FText::FromString("Delete"));
		FSlateFontInfo fontInfo = label->GetFont();
		fontInfo.Size = 12;
		label->SetFont(fontInfo);
		Delete->AddChild(label);
	}
}

void UCASActionsWidget::DeleteActor()
{
	if (Actor)
		Actor->Destroy();
}

void UCASActionsWidget::NativeConstruct()
{
	if (Delete)
		Delete->OnClicked.AddDynamic(this, &UCASActionsWidget::DeleteActor);
}
