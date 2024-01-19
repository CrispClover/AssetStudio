// Copyright Crisp Clover. Feel free to copy.

#include "CASPluginControlWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/WrapBoxSlot.h"
#include "CASLocalLight.h"

void UCASPluginControlWidget::NativeDestruct()
{
	if (CAS)
		CAS->ActorAddedEvent.RemoveAll(this);

	Super::NativeDestruct();
}

void UCASPluginControlWidget::NativeConstruct()
{
	Super::NativeConstruct();

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

		UButton* calibrator = BuildButton(FText::FromString("Toggle Calibrator"), UButton::StaticClass());
		calibrator->OnClicked.AddDynamic(this, &UCASPluginControlWidget::ToggleCalibrator);
		calibrator->SetToolTipText(FText::FromString("Toggles the calibrator. Uses visibility or spawns/destroys the actor depending on DeleteCalibrator. (Found in the Widget's Blueprint)"));
		PluginControlsBox->AddChildToWrapBox(calibrator);

		CalibratorView = WidgetTree->ConstructWidget<UDetailsView>(UDetailsView::StaticClass());
		CalibratorView->CategoriesToShow.Add(FName("CAS"));
		PluginControlsBox->AddChildToWrapBox(CalibratorView);

		SequenceView = WidgetTree->ConstructWidget<UDetailsView>(UDetailsView::StaticClass());
		SequenceView->CategoriesToShow.Add(FName("RenderSettings"));
		SequenceView->SetObject(this);
		PluginControlsBox->AddChildToWrapBox(SequenceView);

		UButton* renderSel = BuildButton(FText::FromString("Queue Selected"), UButton::StaticClass());
		renderSel->OnClicked.AddDynamic(this, &UCASPluginControlWidget::QueueSelected);
		renderSel->SetToolTipText(FText::FromString("Creates Sequences for all selected cameras and queues them for rendering with the Movie Render Queue."));
		PluginControlsBox->AddChildToWrapBox(renderSel);

		UButton* renderAll = BuildButton(FText::FromString("Queue All"), UButton::StaticClass());
		renderAll->OnClicked.AddDynamic(this, &UCASPluginControlWidget::QueueAll);
		renderAll->SetToolTipText(FText::FromString("Creates Sequences for all cameras and queues them for rendering with the Movie Render Queue."));
		PluginControlsBox->AddChildToWrapBox(renderAll);

		/*UButton* renderMat = BuildButton(FText::FromString("Queue Materials"), UButton::StaticClass());
		renderMat->OnClicked.AddDynamic(this, &UCASPluginControlWidget::QueueMaterialRenders);
		renderMat->SetToolTipText(FText::FromString("Creates Sequences for all selected materials and queues them for rendering with the Movie Render Queue."));
		PluginControlsBox->AddChildToWrapBox(renderMat);*/

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

UButton* UCASPluginControlWidget::BuildButton(FText const& buttonLabel, const TSubclassOf<UButton> buttonClass)//TODO: add a class for this?
{
	UButton* button = WidgetTree->ConstructWidget<UButton>(buttonClass);
	UTextBlock* label = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	label->SetText(buttonLabel);
	FSlateFontInfo fontInfo = label->GetFont();
	fontInfo.Size = 15;
	label->SetFont(fontInfo);
	button->AddChild(label);

	return button;
}