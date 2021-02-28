// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPickupBase.h"
#include "FHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class OKGAME_API AFHealthPickup : public AFPickupBase
{
	GENERATED_BODY()

public:
	AFHealthPickup();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	class UParticleSystemComponent* PickupParticle;

	void OnPickup(class UFHealthComponent* HealthComp);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HealthPickup")
	float HealAmount;

	UPROPERTY(BlueprintReadOnly)
	bool bPickedUp;
	
};
