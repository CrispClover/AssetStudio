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

void ACASGroupRep::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

	for (FLightData data : LightsData)
	{
		if (ACASLocalLight* light = Cast<ACASLocalLight>(data.Light))
		{
			light->Pitch = Pitch + data.OriginalPitch;
			light->Yaw = Yaw + data.OriginalYaw;
			light->ApplyProperties();
		}
	}
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
	{
		LightsData[i].OriginalColour = LightsData[i].Light->GetLightColor();

		if (ACASLocalLight* casLight = Cast<ACASLocalLight>(LightsData[i].Light))
		{
			LightsData[i].OriginalPitch = casLight->Pitch;
			LightsData[i].OriginalYaw = casLight->Yaw;
			Pitch = 0.f;
			Yaw = 0.f;
		}
	}
}

void ACASGroupRep::Destroyed()
{
	for (int32 i = 0; i < LightsData.Num(); i++)
	{
		LightsData[i].Light->SetLightColor(LightsData[i].OriginalColour);

		if (ACASLocalLight* casLight = Cast<ACASLocalLight>(LightsData[i].Light))
		{
			casLight->Pitch = LightsData[i].OriginalPitch;
			casLight->Yaw = LightsData[i].OriginalYaw;
			casLight->ApplyProperties();
		}
	}
	Super::Destroyed();
}