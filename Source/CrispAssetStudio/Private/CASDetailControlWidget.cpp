// Copyright Crisp Clover. Feel free to copy.

#include "CASDetailControlWidget.h"
#include "Blueprint/WidgetTree.h"
#include "CASSwitcherButton.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/TextBlock.h"

void UCASDetailControlWidget::NativeDestruct()
{
	if (CAS)
		CAS->ActorAddedEvent.RemoveAll(this);

	Super::NativeDestruct();
}

void UCASDetailControlWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	CAS = GEditor->GetEditorSubsystem<UCASEditorSubsystem>();

	CAS->ActorAddedEvent.AddDynamic(this, &UCASDetailControlWidget::RespondToActorAdded);

	BuildWidget();
}

void UCASDetailControlWidget::RespondToActorAdded(AActor* actor)
{
	AddDetailsWidget(actor);
}

void UCASDetailControlWidget::AddDetailsWidget(AActor* actor)
{
	const ECASType type = UCASEditorSubsystem::GetCASType(actor);
	UCASDetailsWidget* detailsW = CreateWidget<UCASDetailsWidget>(GetWorld(), DetailsClass);
	detailsW->Actor = actor;
	if (TabSettings.Contains(type))
		(*Containers.Find(*TabSettings.Find(type)))->AddChildToWrapBox(detailsW);
}

void UCASDetailControlWidget::BuildWidget()
{
	for (const TPair<ECASType, FName>& pair : TabSettings)
		if (!Containers.Contains(pair.Value))
			BuildTab(pair.Value);

	for (AActor* actor : CAS->GetRelevantActors())
		AddDetailsWidget(actor);
}

void UCASDetailControlWidget::BuildTab(const FName tabName)
{
	if (!Switcher || !SwitcherControls)
		return;

	UVerticalBox* tab = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass());
	UWrapBox* container = WidgetTree->ConstructWidget<UWrapBox>(UWrapBox::StaticClass());
	container->SetInnerSlotPadding(FVector2D(10.0));

	tab->AddChildToVerticalBox(container);
	Switcher->AddChild(tab);

	UCASSwitcherButton* switchB = WidgetTree->ConstructWidget<UCASSwitcherButton>(UCASSwitcherButton::StaticClass());

	UTextBlock* label = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	label->SetText(FText::FromName(tabName));
	FSlateFontInfo fontInfo = label->GetFont();
	fontInfo.Size = 15;
	label->SetFont(fontInfo);
	switchB->AddChild(label);
	switchB->Switcher = Switcher;
	switchB->Index = Switcher->GetChildIndex(tab);
	UHorizontalBoxSlot* s = SwitcherControls->AddChildToHorizontalBox(switchB);
	s->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	s->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);

	Containers.Add(tabName, container);
}