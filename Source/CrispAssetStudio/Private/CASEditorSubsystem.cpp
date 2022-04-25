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
#include "Engine/Selection.h"
#include "EditorScriptingHelpers.h"
#include "EngineUtils.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "CASEditorSubsystem.h"

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
	if (actor->IsA(ACASCamera::StaticClass())
		|| actor->IsA(ACASStudioEnvironment::StaticClass())
		|| actor->IsA(ACASSkyLight::StaticClass())
		|| actor->IsA(ADirectionalLight::StaticClass())
		)
		return ECASType::Other;

	else if (actor->IsA(ALight::StaticClass()))
		return ECASType::Light;

	else if (actor->IsA(ACASGroupRep::StaticClass()))
		return ECASType::GroupRep;

	else if (actor->IsA(ACASMeshBase::StaticClass()))
		return ECASType::Mesh;

	else
		return ECASType::none;
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
	if (!EditorScriptingHelpers::CheckIfInEditorAndPIE() || !GEditor)//is check needed?
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
	if (!EditorScriptingHelpers::CheckIfInEditorAndPIE() || !GEditor)//is check needed?
		return;

	UWorld* world = GEditor->GetEditorWorldContext(false).World();

	ACASGroupRep* rep = world->SpawnActor<ACASGroupRep>(GroupClass);

	TArray<ALight*> selectedLights = GetSelectedLights();

	rep->LightsData.Reserve(selectedLights.Num());

	for (ALight* light : selectedLights)
		rep->LightsData.Add(FCASLightData(light));

	rep->SetFolderPath(FName("CASGroups"));
}