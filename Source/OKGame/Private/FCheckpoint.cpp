// Fill out your copyright notice in the Description page of Project Settings.


#include "FCheckpoint.h"
#include <Components/BoxComponent.h>

// Sets default values
AFCheckpoint::AFCheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Trigger");
	BoxCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFCheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFCheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

