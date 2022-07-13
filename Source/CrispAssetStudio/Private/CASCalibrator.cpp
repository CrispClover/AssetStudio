// Copyright Crisp Clover. Feel free to copy.

#include "CASCalibrator.h"

ACASCalibrator::ACASCalibrator(const FObjectInitializer& ObjectInitializer)
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

void ACASCalibrator::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

	if (!GEditor)
		return;//??

	if (!CAS)
		CAS = GEditor->GetEditorSubsystem<UCASEditorSubsystem>();

	CAS->SceneColour = SceneColour;
	CAS->ReferenceColour = ReferenceColour;
}