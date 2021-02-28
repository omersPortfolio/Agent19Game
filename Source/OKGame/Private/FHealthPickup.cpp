// Fill out your copyright notice in the Description page of Project Settings.


#include "FHealthPickup.h"
#include "FHealthComponent.h"
#include <Particles/ParticleSystemComponent.h>


AFHealthPickup::AFHealthPickup()
{
	PickupParticle = CreateDefaultSubobject<UParticleSystemComponent>("PickupParticle");
	PickupParticle->SetupAttachment(RootComponent);
}

void AFHealthPickup::OnPickup(class UFHealthComponent* HealthComp)
{
	if (HealthComp)
	{
		bPickedUp = true;
		HealthComp->ModifyHealth(HealAmount);
	}
	
}
