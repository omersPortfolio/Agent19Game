// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FInteractableBase.h"
#include "Components/SpotLightComponent.h"
#include "FInteractableLight.generated.h"

/**
 * 
 */
UCLASS()
class OKGAME_API AFInteractableLight : public AFInteractableBase
{
	GENERATED_BODY()

public:

	AFInteractableLight();

	virtual void Interact() override;

	UPROPERTY()
	bool State;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Intensity;

	UPROPERTY(EditAnywhere)
	USpotLightComponent* Light;

protected:
	virtual void BeginPlay() override;
	
};
