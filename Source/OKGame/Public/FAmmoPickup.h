// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPickupBase.h"
#include "FAmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class OKGAME_API AFAmmoPickup : public AFPickupBase
{
	GENERATED_BODY()

public:

	AFAmmoPickup();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ammo")
	UStaticMeshComponent* AmmoMesh;
	
};
