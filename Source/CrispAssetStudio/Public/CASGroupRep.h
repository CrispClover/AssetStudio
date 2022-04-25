// Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Light.h"
#include "CASGroupRep.generated.h"

USTRUCT(BlueprintType)
struct FCASLightData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		ALight* Light;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		FLinearColor OriginalColour;

	FCASLightData()
	{
		Light = nullptr;
		OriginalColour = FLinearColor();
	}

	FCASLightData(ALight* light)
	{
		Light = light;
		OriginalColour = light->GetLightColor();
	}
};


UCLASS(Abstract, Blueprintable)
class CRISPASSETSTUDIO_API ACASGroupRep : public AActor
{
	GENERATED_BODY()
	
public:
	ACASGroupRep();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Studio")
		TArray<FCASLightData> LightsData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		FLinearColor Colour;

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void RespondToActorDeleted(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void Apply();

	virtual void Destroyed() override;

public:

};
