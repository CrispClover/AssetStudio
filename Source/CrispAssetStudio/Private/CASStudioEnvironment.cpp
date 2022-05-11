// Copyright Crisp Clover. Feel free to copy.


#include "CASStudioEnvironment.h"

ACASStudioEnvironment::ACASStudioEnvironment(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Sky = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sky"));
	Sky->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	Sky->Mobility = EComponentMobility::Static;
	Sky->SetGenerateOverlapEvents(false);
	Sky->bUseDefaultCollision = true;
	Sky->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Sky->SetWorldScale3D(FVector(120, 120, 120));

	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	Floor->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	Floor->Mobility = EComponentMobility::Static;
	Floor->SetGenerateOverlapEvents(false);
	Floor->bUseDefaultCollision = true;
	Floor->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void ACASStudioEnvironment::BeginPlay()
{
	Super::BeginPlay();
	ReInit();
}

void ACASStudioEnvironment::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);
	ReInit();
}

void ACASStudioEnvironment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMaterialData();
}

void ACASStudioEnvironment::ReInit()
{
	if (SkyMesh)
		Sky->SetStaticMesh(SkyMesh);
	if (FloorMesh)
		Floor->SetStaticMesh(FloorMesh);

	if (UnlitMaterial)//Unlit material must be set. Apply other materials if they're set and desired.
	{
		if (litFloor && LitFloorMaterial)
			Floor->SetMaterial(0, LitFloorMaterial);
		else
			Floor->SetMaterial(0, UnlitMaterial);

		if (gradient && GradientSkyMaterial)
			Sky->SetMaterial(0, GradientSkyMaterial);
		else
			Sky->SetMaterial(0, UnlitMaterial);
	}

	SetScale();
	UpdateMaterialData();
}

void ACASStudioEnvironment::UpdateMaterialData()
{
	//Colours
	Floor->SetCustomPrimitiveDataVector3(0, FVector(BackgroundColour));
	Floor->SetCustomPrimitiveDataVector3(3, FVector(GradientColour));
	Sky->SetCustomPrimitiveDataVector3(0, FVector(BackgroundColour));
	Sky->SetCustomPrimitiveDataVector3(3, FVector(GradientColour));

	//GradientData
	Sky->SetCustomPrimitiveDataVector2(6, GradientOrigin);
	Sky->SetCustomPrimitiveDataFloat(8, GradientScreenSlope);
	Sky->SetCustomPrimitiveDataFloat(9, GradientZInfluence);
	Sky->SetCustomPrimitiveDataFloat(10, GradientZSlope);
}

void ACASStudioEnvironment::SetScale()
{
	Floor->SetWorldScale3D(FVector(Scale, Scale, 1));
}

void ACASStudioEnvironment::ToggleFloor()
{
	visibleFloor = !visibleFloor;
	Floor->SetHiddenInGame(!visibleFloor);
	Floor->SetVisibility(visibleFloor);
}

bool ACASStudioEnvironment::ToggleUnlitFloor()
{
	if (!LitFloorMaterial || !UnlitMaterial)
		return false;

	litFloor = !litFloor;

	if (litFloor)
		Floor->SetMaterial(0, LitFloorMaterial);
	else
		Floor->SetMaterial(0, UnlitMaterial);

	return true;
}

bool ACASStudioEnvironment::ToggleSkyGradient()
{
	if (!GradientSkyMaterial || !UnlitMaterial)
		return false;

	gradient = !gradient;

	if (gradient)
		Sky->SetMaterial(0, GradientSkyMaterial);
	else
		Sky->SetMaterial(0, UnlitMaterial);

	return true;
}


