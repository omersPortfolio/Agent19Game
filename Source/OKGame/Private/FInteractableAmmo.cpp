// Fill out your copyright notice in the Description page of Project Settings.


#include "FInteractableAmmo.h"
#include <Kismet/GameplayStatics.h>
#include "FCharacterBase.h"
#include "FWeapon.h"


AFInteractableAmmo::AFInteractableAmmo()
{


	PickupAmmo = 20;
	bPickedUp = false;
	
	InteractionText = "Pick Up";
}

void AFInteractableAmmo::Interact()
{
	AFCharacterBase* Char = Cast<AFCharacterBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Char)
	{
		bPickedUp = true;
		Char->GetCurrentWeapon()->MaxAmmo += PickupAmmo;
		
	}
}
