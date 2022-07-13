//Copyright Crisp Clover. Feel free to copy.

#include "CASEditorSubsystem.h"
#include "Engine/DirectionalLight.h"
#include "CASLocalLight.h"
#include "CASStudioEnvironment.h"
#include "CASCamera.h"
#include "CASGroupRep.h"
#include "CASMeshBase.h"
#include "CASStaticMesh.h"
#include "CASSkeletalMesh.h"
#include "CASSkyLight.h"
#include "CASRectLight.h"
#include "CASCalibrator.h"
#include "Engine/Selection.h"
#include "EditorScriptingHelpers.h"
#include "EngineUtils.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/DataTableFunctionLibrary.h"

// Start of broadcast class
class FCASBroadcast
{
public:
	FCASBroadcast(UCASEditorSubsystem* InCASEditorSubsystem);
	void Initialize();
	void Deinitialize();

private:
	void OnLevelActorAdded(AActor* actor) { CAS->OnLevelActorAdded(actor); }
	void OnLevelActorDeleted(AActor* actor) { CAS->OnLevelActorDeleted(actor); }
	UCASEditorSubsystem* CAS;
	bool bIsInitialized;
};

FCASBroadcast::FCASBroadcast(UCASEditorSubsystem* InCASEditorSubsystem) : CAS(InCASEditorSubsystem) , bIsInitialized(false)
{
	Initialize();
}

void FCASBroadcast::Initialize()
{
	if (!bIsInitialized)
	{
		bIsInitialized = true;
		GEngine->OnLevelActorAdded().AddRaw(this, &FCASBroadcast::OnLevelActorAdded);
		GEngine->OnLevelActorDeleted().AddRaw(this, &FCASBroadcast::OnLevelActorDeleted);
	}
}

void FCASBroadcast::Deinitialize()
{
	if (bIsInitialized)
	{
		bIsInitialized = false;
		GEngine->OnLevelActorAdded().RemoveAll(this);
		GEngine->OnLevelActorDeleted().RemoveAll(this);
	}
}
//End of broadcast class

//Start of subsystem
void UCASEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	CASBroadcast = MakeShareable(new FCASBroadcast(this));
}

void UCASEditorSubsystem::Deinitialize()
{
	if (CASBroadcast)
		CASBroadcast->Deinitialize();

	Super::Deinitialize();
}

ECASType UCASEditorSubsystem::GetCASType(AActor* actor)
{
	if (actor->IsA(ASkyLight::StaticClass()) || actor->IsA(ADirectionalLight::StaticClass()))
		return ECASType::GlobalLight;

	else if (actor->IsA(ALight::StaticClass()))//Must be checked after global lights. (due to inheritance)
		return ECASType::LocalLight;

	else if (actor->IsA(ACASGroupRep::StaticClass()))
		return ECASType::GroupRep;

	else if (actor->IsA(ACameraActor::StaticClass()))
		return ECASType::Camera;

	else if (actor->IsA(ACASMeshBase::StaticClass()))
		return ECASType::Mesh;

	else if (actor->IsA(ACASStudioEnvironment::StaticClass()))
		return ECASType::Environment;

	else if (actor->IsA(ACASCalibrator::StaticClass()))
		return ECASType::Other;

	else
		return ECASType::none;
}

FRotator UCASEditorSubsystem::GetBaseRotator(USceneComponent* refComp, AActor* target)//TODO: Default target = nullptr?
{
	if (!refComp)
		return FRotator();

	FRotator baseRot = FRotator();
	FRotator actorRot = FRotator();
	FVector basePos;
	FVector compPos;

	if (target)
		actorRot = target->GetActorRotation();

	if (target && (RotCalcType == ERotCalcType::PlanarPos || RotCalcType == ERotCalcType::ThreeDPos))
		basePos = target->GetActorLocation();

	switch (RotCalcType)
	{
	case ERotCalcType::PlanarRot:
		baseRot = FRotator(0, refComp->GetComponentRotation().Yaw, 0);
		break;

	case ERotCalcType::PlanarPos:
		compPos = refComp->GetComponentLocation();
		compPos.Z = basePos.Z = 0;
		baseRot = UKismetMathLibrary::FindLookAtRotation(compPos, basePos);
		baseRot = FRotator(0, baseRot.Yaw, 0);
		break;

	case ERotCalcType::ThreeDRot:
		baseRot = refComp->GetComponentRotation();
		break;

	case ERotCalcType::ThreeDPos:
		compPos = refComp->GetComponentLocation();
		baseRot = UKismetMathLibrary::FindLookAtRotation(compPos, basePos);
		break;
	}

	FRotator localRotation = UKismetMathLibrary::ComposeRotators(baseRot, actorRot.GetInverse());

	return localRotation;
}

FLinearColor UCASEditorSubsystem::GetCalibratedColour(FLinearColor lightColour)
{
	FVector lv = FVector(lightColour);
	FVector sv = FVector(SceneColour);
	FVector rv = FVector(ReferenceColour);
	lv.Normalize();
	sv.Normalize();
	rv.Normalize();
	return FLinearColor(lv / sv * rv);
}


void UCASEditorSubsystem::OnLevelActorAdded(AActor* actor)
{
	ActorAddedEvent.Broadcast(actor);
}

void UCASEditorSubsystem::OnLevelActorDeleted(AActor* actor)
{
	ActorDeletedEvent.Broadcast(actor);
}

TArray<AActor*> UCASEditorSubsystem::GetRelevantActors()
{
	if (!EditorScriptingHelpers::CheckIfInEditorAndPIE() || !GEditor)
		return TArray<AActor*>();

	TGuardValue<bool> UnattendedScriptGuard(GIsRunningUnattendedScript, true);
	UWorld* world = GEditor->GetEditorWorldContext(false).World();
	TArray<AActor*> result;

	for (TActorIterator<AActor> it(world, AActor::StaticClass(), EActorIteratorFlags::SkipPendingKill); it; ++it)
	{
		AActor* actor = *it;
		ECASType type = GetCASType(actor);
		if (type != ECASType::none)
			result.Add(actor);
	}

	return result;
}

TArray<AActor*> UCASEditorSubsystem::GetActorsOfType(ECASType type)
{
	if (!EditorScriptingHelpers::CheckIfInEditorAndPIE() || !GEditor)
		return TArray<AActor*>();

	TGuardValue<bool> UnattendedScriptGuard(GIsRunningUnattendedScript, true);
	UWorld* world = GEditor->GetEditorWorldContext(false).World();
	TArray<AActor*> result;

	for (TActorIterator<AActor> it(world, AActor::StaticClass(), EActorIteratorFlags::SkipPendingKill); it; ++it)
	{
		AActor* actor = *it;
		if (type == GetCASType(actor))
			result.Add(actor);
	}

	return result;
}

TArray<ALight*> UCASEditorSubsystem::GetSelectedLights()
{
	if (!GEditor)
		return TArray<ALight*>();

	TArray<ALight*> result;
	result.Reserve(GEditor->GetSelectedActorCount());

	for (FSelectionIterator It = GEditor->GetSelectedActorIterator(); It; ++It)
		if (ALight* light = Cast<ALight>(*It))
			result.Add(light);

	return result;
}

TArray<AActor*> UCASEditorSubsystem::GetSelectedActors()
{
	if (!GEditor)
		return TArray<AActor*>();

	TArray<AActor*> result;
	result.Reserve(GEditor->GetSelectedActorCount());

	for (FSelectionIterator It = GEditor->GetSelectedActorIterator(); It; ++It)
		if (AActor* actor = Cast<AActor>(*It))
			result.Add(actor);

	return result;
}

void UCASEditorSubsystem::CreateGroup(TSubclassOf<ACASGroupRep> GroupClass)
{
	if (!EditorScriptingHelpers::CheckIfInEditorAndPIE() || !GEditor)
		return;

	UWorld* world = GEditor->GetEditorWorldContext(false).World();

	ACASGroupRep* rep = world->SpawnActor<ACASGroupRep>(GroupClass);

	TArray<ALight*> selectedLights = GetSelectedLights();

	rep->LightsData.Reserve(selectedLights.Num());

	for (ALight* light : selectedLights)
		rep->LightsData.Add(FCASLightData(light));

	rep->SetFolderPath(FName("CASGroups"));
}