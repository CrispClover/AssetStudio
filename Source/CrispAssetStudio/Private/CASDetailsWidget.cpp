// Copyright Crisp Clover. Feel free to copy.

#include "CASDetailsWidget.h"
#include "Engine/Light.h"
#include "Components/LightComponent.h"
#include "Components/SkyLightComponent.h"
#include "CASSkyLight.h"

void UCASDetailsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!CAS)
		CAS = GEditor->GetEditorSubsystem<UCASEditorSubsystem>();

	CAS->ActorDeletedEvent.AddDynamic(this, &UCASDetailsWidget::RespondToActorDeleted);

	if (Actor)
		ActorView->SetObject(Actor);

	if (ALight* light = Cast<ALight>(Actor))
		ComponentView->SetObject(light->GetLightComponent());
	else if(ASkyLight* skyLight = Cast<ASkyLight>(Actor))
		ComponentView->SetObject(skyLight->GetLightComponent());
	else
		ComponentView->RemoveFromParent();
}

void UCASDetailsWidget::RespondToActorDeleted(AActor* actor)
{
	if (Actor == actor)
		this->RemoveFromParent();
}