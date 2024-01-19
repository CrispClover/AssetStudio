// Copyright Crisp Clover. Feel free to copy.

#include "CASStaticMesh.h"
#include "CASLocalLight.h"

ACASStaticMesh::ACASStaticMesh(FObjectInitializer const& ObjectInitializer)
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

void ACASStaticMesh::OnConstruction(FTransform const& transform)
{
	Super::OnConstruction(transform);

	if (!Mesh)
		return;

	if (UStaticMesh const* oldMesh = Cast<UStaticMeshComponent>(MeshComponent)->GetStaticMesh())
	{
		if (oldMesh != Mesh)
		{
			const FBoxSphereBounds oldBounds = oldMesh->GetBounds();
			const FBoxSphereBounds newBounds = Mesh->GetBounds();

			OnMeshChange(oldBounds.BoxExtent, newBounds.BoxExtent);

			Cast<UStaticMeshComponent>(MeshComponent)->SetStaticMesh(Mesh);
		}
	}
}

bool ACASStaticMesh::ToggleWireframe()
{
	if (!WireframeMaterial)
		return false;

	wireframe = !wireframe;

	if (wireframe)
	{
		Cast<UStaticMeshComponent>(WireframeComponent)->SetStaticMesh(Cast<UStaticMeshComponent>(MeshComponent)->GetStaticMesh());

		for (int32 i = 0; i < WireframeComponent->GetNumMaterials(); i++)
			WireframeComponent->SetMaterial(i, WireframeMaterial);
	}
	else
	{
		Cast<UStaticMeshComponent>(WireframeComponent)->SetStaticMesh(nullptr);
	}

	Super::ToggleWireframe();
	return true;
}