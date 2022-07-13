// Copyright Crisp Clover. Feel free to copy.

#include "CASPluginControlWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/WrapBoxSlot.h"
#include "CASLocalLight.h"

void UCASPluginControlWidget::BeginDestroy()
{
	if (CAS)
		CAS->ActorAddedEvent.RemoveAll(this);

	Super::BeginDestroy();
}

void UCASPluginControlWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!CAS)
		CAS = GEditor->GetEditorSubsystem<UCASEditorSubsystem>();

	BuildWidget();
}

void UCASPluginControlWidget::FlipMultiple()
{
	for (ALight* light : CAS->GetSelectedLights())//TODO: Move to Subsystem?
	{
		if (ACASLocalLight* casLight = Cast<ACASLocalLight>(light))
			casLight->Flip();
	}
}

void UCASPluginControlWidget::DetachMultiple()
{
	for (ALight* light : CAS->GetSelectedLights())//TODO: Move to Subsystem?
	{
		light->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		light->SetFolderPath("Lights");//TODO: add text input for user?
	}
}

void UCASPluginControlWidget::CreateGroup()
{
	CAS->CreateGroup(GroupClass);
}

void UCASPluginControlWidget::BuildWidget()
{
	if (LightSpawnClass && LightSpawnClass && PluginControlsBox)//TODO?
	{
		UEditorUtilityWidget* lb = CreateWidget<UCASSpawnBaseWidget>(GetWorld(), LightSpawnClass);
		PluginControlsBox->AddChildToWrapBox(lb);

		UButton* group = BuildButton(FText::FromString("Create Light Group"), UButton::StaticClass());
		group->OnClicked.AddDynamic(this, &UCASPluginControlWidget::CreateGroup);
		group->SetToolTipText(FText::FromString("Creates a light-group containing all selected lights."));
		PluginControlsBox->AddChildToWrapBox(group);

		UButton* flip = BuildButton(FText::FromString("Flip Selected"), UButton::StaticClass());
		flip->OnClicked.AddDynamic(this, &UCASPluginControlWidget::FlipMultiple);
		flip->SetToolTipText(FText::FromString("Flips the yaw of all selected lights."));
		PluginControlsBox->AddChildToWrapBox(flip);

		UButton* detach = BuildButton(FText::FromString("Detach Selected"), UButton::StaticClass());
		detach->OnClicked.AddDynamic(this, &UCASPluginControlWidget::DetachMultiple);
		detach->SetToolTipText(FText::FromString("Detaches the selected lights from their parent actor."));
		PluginControlsBox->AddChildToWrapBox(detach);

		UEditorUtilityWidget* sb = CreateWidget<UCASSpawnBaseWidget>(GetWorld(), SpawnClass);
		PluginControlsBox->AddChildToWrapBox(sb);

		CalibratorToggle = BuildButton(FText::FromString("Toggle Calibrator"), UButton::StaticClass());
		CalibratorToggle->OnClicked.AddDynamic(this, &UCASPluginControlWidget::ToggleCalibrator);
		PluginControlsBox->AddChildToWrapBox(CalibratorToggle);

		CalibratorView = WidgetTree->ConstructWidget<UDetailsView>(UDetailsView::StaticClass());
		CalibratorView->CategoriesToShow.Add(FName("CAS"));
		PluginControlsBox->AddChildToWrapBox(CalibratorView);

		SequenceView = WidgetTree->ConstructWidget<UDetailsView>(UDetailsView::StaticClass());
		SequenceView->CategoriesToShow.Add(FName("RenderSettings"));
		SequenceView->SetObject(this);
		PluginControlsBox->AddChildToWrapBox(SequenceView);

		UButton* renderSel = BuildButton(FText::FromString("Queue Selected"), UButton::StaticClass());
		renderSel->OnClicked.AddDynamic(this, &UCASPluginControlWidget::QueueSelected);
		PluginControlsBox->AddChildToWrapBox(renderSel);

		UButton* renderAll = BuildButton(FText::FromString("Queue All"), UButton::StaticClass());
		renderAll->OnClicked.AddDynamic(this, &UCASPluginControlWidget::QueueAll);
		PluginControlsBox->AddChildToWrapBox(renderAll);

		for (UPanelSlot* ps : PluginControlsBox->GetSlots())
		{
			if (UWrapBoxSlot* ws = Cast<UWrapBoxSlot>(ps))
			{
				ws->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
				ws->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			}
		}
	}
}

UButton* UCASPluginControlWidget::BuildButton(FText buttonLabel, TSubclassOf<UButton> buttonClass)//TODO: add a class for this?
{
	UButton* button = WidgetTree->ConstructWidget<UButton>(buttonClass);
	UTextBlock* label = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	label->SetText(buttonLabel);
	label->Font.Size = 15;
	button->AddChild(label);

	return button;
}