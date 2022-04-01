//Copyright Crisp Clover. Feel free to copy.

#include "StudioActor.h"

void AStudioActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateProperties();
}

void AStudioActor::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);
	UpdateProperties();
}

void AStudioActor::UpdateProperties_Implementation()
{

}