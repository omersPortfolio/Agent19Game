// Fill out your copyright notice in the Description page of Project Settings.


#include "FPickupBase.h"
#include <Particles/ParticleSystemComponent.h>
#include <Components/SphereComponent.h>

// Sets default values
AFPickupBase::AFPickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = RootComp;

	CollisionComp = CreateDefaultSubobject<USphereComponent>("CollisionComp");
	CollisionComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFPickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

