// Copyright Crisp Clover. Feel free to copy.


#include "CASSkeletalMesh.h"
#include "CASLocalLight.h"

ACASSkeletalMesh::ACASSkeletalMesh(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	USkeletalMeshComponent* mc = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	mc->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	mc->Mobility = EComponentMobility::Movable;
	mc->SetGenerateOverlapEvents(false);

	RootComponent = MeshComponent = mc;

	USkeletalMeshComponent* wc = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Wireframe"));
	wc->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	wc->Mobility = EComponentMobility::Movable;
	wc->SetGenerateOverlapEvents(false);

	WireframeComponent = wc;

	WireframeComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void ACASSkeletalMesh::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

	if (!Mesh)
		return;

	if (USkeletalMesh* oldMesh = Cast<USkeletalMeshComponent>(MeshComponent)->SkeletalMesh)
	{
		if (oldMesh != Mesh)
		{
			FBoxSphereBounds oldBounds = oldMesh->GetBounds();
			FBoxSphereBounds newBounds = Mesh->GetBounds();

			OnMeshChange(oldBounds.BoxExtent, newBounds.BoxExtent);

			Cast<USkeletalMeshComponent>(MeshComponent)->SetSkeletalMesh(Mesh);
		}
	}
}

bool ACASSkeletalMesh::ToggleWireframe()
{
	if (!WireframeMaterial)
		return false;

	wireframe = !wireframe;

	if (wireframe && Mesh)
	{
		Cast<USkeletalMeshComponent>(WireframeComponent)->SetSkeletalMesh(Mesh);

		for (int i = 0; i < WireframeComponent->GetNumMaterials(); i++)
			WireframeComponent->SetMaterial(i, WireframeMaterial);
	}
	else
	{
		Cast<USkeletalMeshComponent>(WireframeComponent)->SetSkeletalMesh(nullptr);
	}

	Super::ToggleWireframe();
	return true;
}

