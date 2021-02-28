// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FInteractableBase.h"
#include "FInteractableAmmo.generated.h"

/**
 * 
 */
UCLASS()
class OKGAME_API AFInteractableAmmo : public AFInteractableBase
{
	GENERATED_BODY()

public:
	AFInteractableAmmo();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int PickupAmmo;

	UPROPERTY(BlueprintReadOnly)
	bool bPickedUp;

	virtual void Interact() override;
	
};
