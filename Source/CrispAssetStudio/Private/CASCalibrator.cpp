// Copyright Crisp Clover. Feel free to copy.

#include "CASCalibrator.h"

ACASCalibrator::ACASCalibrator(FObjectInitializer const& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UStaticMeshComponent* mc = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Calibrator"));
	mc->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	mc->SetHiddenInGame(true);
	mc->Mobility = EComponentMobility::Static;
	mc->SetGenerateOverlapEvents(false);
	mc->bUseDefaultCollision = true;

	RootComponent = Calibrator = mc;
}

void ACASCalibrator::OnConstruction(FTransform const& transform)
{
	Super::OnConstruction(transform);

	if (!GEditor)
		return;//TODO: needed??

	if (!CAS)
		CAS = GEditor->GetEditorSubsystem<UCASEditorSubsystem>();

	CAS->SceneColour = SceneColour;
	CAS->ReferenceColour = ReferenceColour;
}