// Copyright Crisp Clover. Feel free to copy.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Light.h"
#include "CASLocalLight.h"
#include "CASGroupRep.generated.h"

USTRUCT(BlueprintType)
struct FLightData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		ALight* Light;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		FLinearColor OriginalColour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		float OriginalPitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		float OriginalYaw;

	FLightData()
	{
		Light = nullptr;
		OriginalColour = FLinearColor();
	}

	FLightData(ALight* light)
	{
		Light = light;
		OriginalColour = light->GetLightColor();
		if(ACASLocalLight* casLight = Cast<ACASLocalLight>(light))
		{
			OriginalPitch = casLight->Pitch;
			OriginalYaw = casLight->Yaw;
		}
	}
};

UCLASS(Abstract, Blueprintable)
class CRISPASSETSTUDIO_API ACASGroupRep : public AActor
{
	GENERATED_BODY()
	
public:
	ACASGroupRep();
	virtual void OnConstruction(const FTransform& transform) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Studio")
		TArray<FLightData> LightsData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS")
		FLinearColor Colour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS", meta = (UIMin = -360, UIMax = 360))
		float Pitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAS", meta = (UIMin = -360, UIMax = 360))
		float Yaw;

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void RespondToActorDeleted(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "CAS")
		void Apply();

	virtual void Destroyed() override;

public:

};
