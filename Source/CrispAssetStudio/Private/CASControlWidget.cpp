// Copyright Crisp Clover. Feel free to copy.

#include "CASControlWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "CASSwitcherButton.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBoxSlot.h"
#include "Engine/Light.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "CASLocalLight.h"

void UCASControlWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UCASControlWidget::BeginDestroy()
{
	if (CAS)
		CAS->ActorAddedEvent.RemoveAll(this);

	Super::BeginDestroy();
}

void UCASControlWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!CAS)
		CAS = GEditor->GetEditorSubsystem<UCASEditorSubsystem>();

	CAS->ActorAddedEvent.AddDynamic(this, &UCASControlWidget::RespondToActorAdded);

	BuildWidget();
}

void UCASControlWidget::RespondToActorAdded(AActor* actor)
{
	AddDetailsWidget(actor);
}

void UCASControlWidget::FlipMultiple()
{
	for (ALight* light : CAS->GetSelectedLights())//TODO: Move to Subsystem
	{
		if (ACASLocalLight* casLight = Cast<ACASLocalLight>(light))
			casLight->Flip();
	}
}

void UCASControlWidget::DetachMultiple()
{
	for (ALight* light : CAS->GetSelectedLights())//TODO: Move to Subsystem
	{
		light->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		light->SetFolderPath("Lights");//TODO: add text input for user?
	}
}

void UCASControlWidget::CreateGroup()
{
	CAS->CreateGroup(GroupClass);
}

void UCASControlWidget::AddDetailsWidget(AActor* actor)
{
	if (!LightsContainer)
		BuildTab(LightsContainer, "Lights");

	ECASType type = UCASEditorSubsystem::GetCASType(actor);
	UCASDetailsWidget* detailsW = CreateWidget<UCASDetailsWidget>(GetWorld(), DetailsClass);
	detailsW->Actor = actor;

	switch (type)
	{
	case ECASType::Light:
		LightsContainer->AddChildToWrapBox(detailsW);
		break;
	
	case ECASType::GroupRep:
		LightsContainer->AddChildToWrapBox(detailsW);
		break;

	case ECASType::Mesh:
		if (!MeshesContainer)
			BuildTab(MeshesContainer, "Meshes");

		MeshesContainer->AddChildToWrapBox(detailsW);
		break;

	case ECASType::Other:
		if (!OthersContainer)
			BuildTab(OthersContainer, "Others");

		OthersContainer->AddChildToWrapBox(detailsW);
		break;
	}
}

void UCASControlWidget::BuildWidget()
{
	if (LightSpawnClass && LightSpawnClass && PluginControlsBox)//TODO: separate?
	{
		UEditorUtilityWidget* sb = CreateWidget<UCASSpawnBaseWidget>(GetWorld(), SpawnClass);
		PluginControlsBox->AddChildToWrapBox(sb);
		UEditorUtilityWidget* lb = CreateWidget<UCASSpawnBaseWidget>(GetWorld(), LightSpawnClass);
		PluginControlsBox->AddChildToWrapBox(lb);

		UButton* group = BuildButton(FText::FromString("Create Group"), UButton::StaticClass());
		group->OnClicked.AddDynamic(this, &UCASControlWidget::CreateGroup);
		PluginControlsBox->AddChildToWrapBox(group);

		UButton* flip = BuildButton(FText::FromString("Flip Selected"), UButton::StaticClass());
		flip->OnClicked.AddDynamic(this, &UCASControlWidget::FlipMultiple);
		PluginControlsBox->AddChildToWrapBox(flip);

		UButton* detach = BuildButton(FText::FromString("Detach Selected"), UButton::StaticClass());
		detach->OnClicked.AddDynamic(this, &UCASControlWidget::DetachMultiple);
		PluginControlsBox->AddChildToWrapBox(detach);

	}

	if (!LightsContainer)
		BuildTab(LightsContainer, "Lights");
	else
		LightsContainer->ClearChildren();//TODO: needed?

	if (!MeshesContainer)
		BuildTab(MeshesContainer, "Meshes");
	else
		MeshesContainer->ClearChildren();

	if (!OthersContainer)
		BuildTab(OthersContainer, "Others");
	else
		OthersContainer->ClearChildren();

	for (AActor* actor : CAS->GetRelevantActors())
		AddDetailsWidget(actor);
}

void UCASControlWidget::BuildTab(UWrapBox*& container, FString tabName)
{
	if (!Switcher || !SwitcherControls)
		return;

	UVerticalBox* tab = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass());

	container = WidgetTree->ConstructWidget<UWrapBox>(UWrapBox::StaticClass());
	container->SetInnerSlotPadding(FVector2D(10.0));

	tab->AddChildToVerticalBox(container);
	Switcher->AddChild(tab);

	UCASSwitcherButton* switchB = WidgetTree->ConstructWidget<UCASSwitcherButton>(UCASSwitcherButton::StaticClass());

	UTextBlock* label = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	label->SetText(FText::FromString(tabName));
	label->Font.Size = 15;
	switchB->AddChild(label);
	switchB->Switcher = Switcher;
	switchB->Index = Switcher->GetChildIndex(tab);
	UHorizontalBoxSlot* s = SwitcherControls->AddChildToHorizontalBox(switchB);
	s->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	s->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
}

UButton* UCASControlWidget::BuildButton(FText buttonLabel, TSubclassOf<UButton> buttonClass)//TODO: add a class for this
{
	UButton* button = WidgetTree->ConstructWidget<UButton>(buttonClass);
	UTextBlock* label = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	label->SetText(buttonLabel);
	label->Font.Size = 15;
	button->AddChild(label);

	return button;
}