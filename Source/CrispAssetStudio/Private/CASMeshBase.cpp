// Copyright Crisp Clover. Feel free to copy.

#include "CASMeshBase.h"

void ACASMeshBase::BeginPlay()
{
	Super::BeginPlay();
	UpdateMaterialData();
}

void ACASMeshBase::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);
	UpdateMaterialData();
}

bool ACASMeshBase::ToggleSimpleMaterial()
{
	if (!SimpleMaterial || !MeshComponent)
		return false;

	simpleMat = !simpleMat;

	if (simpleMat)
	{
		originalMaterials = MeshComponent->GetMaterials();

		for (int i = 0; i < MeshComponent->GetNumMaterials(); i++)
			MeshComponent->SetMaterial(i, SimpleMaterial);
	}
	else
	{
		for (int i = 0; i < originalMaterials.Num(); i++)
			MeshComponent->SetMaterial(i, originalMaterials[i]);

		originalMaterials.Empty();
	}

	UpdateMaterialData();
	return true;
}

void ACASMeshBase::UpdateMaterialData()
{
	if (simpleMat)
	{
		MeshComponent->SetCustomPrimitiveDataVector3(0, FVector(SimpleEmissive));
		MeshComponent->SetCustomPrimitiveDataVector3(3, FVector(SimpleDiffuse));
	}

	if (wireframe)
	{
		WireframeComponent->SetCustomPrimitiveDataVector3(0, FVector(WireframeEmissive));
		WireframeComponent->SetCustomPrimitiveDataFloat(3, WireframeOffset);
	}
}

bool ACASMeshBase::ToggleWireframe()
{
	UpdateMaterialData();
	return true;
}