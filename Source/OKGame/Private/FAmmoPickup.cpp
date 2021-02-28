// Fill out your copyright notice in the Description page of Project Settings.


#include "FAmmoPickup.h"

AFAmmoPickup::AFAmmoPickup()
{
	AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>("AmmoMesh");
	RootComponent = AmmoMesh;
	//AmmoMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	AmmoMesh->SetCollisionProfileName("OverlapAll");
}
