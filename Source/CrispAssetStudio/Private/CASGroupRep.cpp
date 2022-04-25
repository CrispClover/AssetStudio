// Copyright Crisp Clover. Feel free to copy.

#include "CASGroupRep.h"
#include "CASEditorSubsystem.h"

ACASGroupRep::ACASGroupRep()
:Super()
{
	if (!GEditor)
		return;

	UCASEditorSubsystem* cas = GEditor->GetEditorSubsystem<UCASEditorSubsystem>();

	if (!cas)
		return;

	cas->ActorDeletedEvent.AddDynamic(this, &ACASGroupRep::RespondToActorDeleted);
}

void ACASGroupRep::RespondToActorDeleted(AActor* actor)
{
	if (ALight* light = Cast<ALight>(actor))
		for (int i = 0; i < LightsData.Num(); i++)
			if (LightsData[i].Light == light)
				LightsData.RemoveAtSwap(i);
}

void ACASGroupRep::Apply()
{
	for (int32 i = 0; i < LightsData.Num(); i++)
		LightsData[i].OriginalColour = LightsData[i].Light->GetLightColor();
}

void ACASGroupRep::Destroyed()
{
	for (int32 i = 0; i < LightsData.Num(); i++)
		LightsData[i].Light->SetLightColor(LightsData[i].OriginalColour);

	Super::Destroyed();
}