// Fill out your copyright notice in the Description page of Project Settings.


#include "FInteractableBase.h"
#include <Components/WidgetComponent.h>
#include <Components/SphereComponent.h>
#include "FCharacterBase.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AFInteractableBase::AFInteractableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = RootComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComp);

	CollisionComp = CreateDefaultSubobject<USphereComponent>("CollisionComp");
	CollisionComp->SetupAttachment(RootComponent);

	WidgetComp = CreateDefaultSubobject<UWidgetComponent>("InteractionWidget");
	WidgetComp->SetupAttachment(RootComponent);

	InteractionSphere = CreateDefaultSubobject<USphereComponent>("InteractionSphere");
	InteractionSphere->SetupAttachment(RootComponent);
	

	InteractionText = "";

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AFInteractableBase::BeginOverlap);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &AFInteractableBase::EndOverlap);
}

// Called when the game starts or when spawned
void AFInteractableBase::BeginPlay()
{
	Super::BeginPlay();

	WidgetComp->SetVisibility(false);
	
	Character = Cast<AFCharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void AFInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFInteractableBase::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Character)
	{
		WidgetComp->SetVisibility(true);
	}
}

void AFInteractableBase::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (Character)
	{
		WidgetComp->SetVisibility(false);
	}
}

