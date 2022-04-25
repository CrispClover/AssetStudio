// Copyright Crisp Clover. Feel free to copy.


#include "CASStaticMesh.h"

ACASStaticMesh::ACASStaticMesh(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UStaticMeshComponent* mc = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	mc->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	mc->Mobility = EComponentMobility::Static;
	mc->SetGenerateOverlapEvents(false);
	mc->bUseDefaultCollision = true;

	RootComponent = MeshComponent = mc;

	UStaticMeshComponent* wc = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wireframe"));
	wc->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	wc->Mobility = EComponentMobility::Static;
	wc->SetGenerateOverlapEvents(false);
	wc->bUseDefaultCollision = true;

	WireframeComponent = wc;

	WireframeComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void ACASStaticMesh::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

	if (Mesh)
		Cast<UStaticMeshComponent>(MeshComponent)->SetStaticMesh(Mesh);
}

bool ACASStaticMesh::ToggleWireframe()
{
	if (!WireframeMaterial)
		return false;

	wireframe = !wireframe;

	if (wireframe)
	{
		Cast<UStaticMeshComponent>(WireframeComponent)->SetStaticMesh(Cast<UStaticMeshComponent>(MeshComponent)->GetStaticMesh());

		for (int i = 0; i < WireframeComponent->GetNumMaterials(); i++)
			WireframeComponent->SetMaterial(i, WireframeMaterial);
	}
	else
	{
		Cast<UStaticMeshComponent>(WireframeComponent)->SetStaticMesh(nullptr);
	}

	Super::ToggleWireframe();
	return true;
}