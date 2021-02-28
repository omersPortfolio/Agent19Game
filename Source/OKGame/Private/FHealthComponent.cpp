// Fill out your copyright notice in the Description page of Project Settings.


#include "FHealthComponent.h"

// Sets default values for this component's properties
UFHealthComponent::UFHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100;
	
}

void UFHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UFHealthComponent::TakeDamage);
	}

	Health = MaxHealth;
}


float UFHealthComponent::GetHealth()
{
	return Health;
}

float UFHealthComponent::GetMaxHealth()
{
	return MaxHealth;
}

void UFHealthComponent::ModifyHealth(const float Delta)
{
	const float OldHealth = Health;

	Health = FMath::Clamp<float>(Health + Delta, 0.f, MaxHealth);
}



void UFHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0) return;

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
}

