// Copyright Crisp Clover. Feel free to copy.

#include "CASCamera.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMaterialLibrary.h"

ACASCamera::ACASCamera(FObjectInitializer const& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ApplyProperties();
}

void ACASCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ApplyProperties();
}

void ACASCamera::OnConstruction(FTransform const& transform)
{
	Super::OnConstruction(transform);
	ApplyProperties();

	if (showReferenceImage)
		UpdateRefImgMatData();
}

void ACASCamera::UpdateRefImgMatData()
{
	if (RefDynamicInstance && Image)
	{
		RefDynamicInstance->SetVectorParameterValue(FName("Controls"), FVector4(Crop, Shift));
		RefDynamicInstance->SetScalarParameterValue(FName("Alpha"), Alpha);
		RefDynamicInstance->SetTextureParameterValue(FName("RefImg"), Image);
		RefDynamicInstance->SetScalarParameterValue(FName("FlipU"), FlipU);
		RefDynamicInstance->SetScalarParameterValue(FName("FlipV"), FlipV);
	}
}

bool ACASCamera::ToggleReferenceImage()
{
	if (!RefImgMaterial)
		return false;

	if (!RefDynamicInstance)
	{
		RefDynamicInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, RefImgMaterial);
		UpdateRefImgMatData();
	}
	showReferenceImage = !showReferenceImage;

	if (showReferenceImage)
		GetCameraComponent()->PostProcessSettings.WeightedBlendables.Array.Add(FWeightedBlendable(1.f, RefDynamicInstance));
	else
		GetCameraComponent()->PostProcessSettings.WeightedBlendables.Array.Pop(false);

	return true;
}

void ACASCamera::ApplyProperties()
{
	GetCameraComponent()->SetRelativeLocation(FVector(-Distance, 0, 0));
}