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

void ACASGroupRep::OnConstruction(FTransform const& transform)
{
	Super::OnConstruction(transform);

	for (FCASLightData const& data : LightsData)
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
	if (ALight const* light = Cast<ALight>(actor))
		Remove(light);
}

void ACASGroupRep::Add(ALight* light)
{
	for (FCASLightData data : LightsData)
		if (data.Light == light)
			return;

	LightsData.Add(FCASLightData(light));
}

void ACASGroupRep::Remove(ALight const* light)
{
	for (int32 i = 0; i < LightsData.Num(); i++)
		if (LightsData[i].Light == light)
			LightsData.RemoveAtSwap(i);
	//TODO: restore original light data?
}

void ACASGroupRep::Apply()
{
	for (int32 i = 0; i < LightsData.Num(); i++)
	{
		if (LightsData[i].Light)
			LightsData[i].OriginalColour = LightsData[i].Light->GetLightColor();

		if (ACASLocalLight const* casLight = Cast<ACASLocalLight>(LightsData[i].Light))
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
		if (LightsData[i].Light)
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