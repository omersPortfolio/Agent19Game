// Fill out your copyright notice in the Description page of Project Settings.


#include "FWeapon.h"
#include "DrawDebugHelpers.h"
#include <Kismet/GameplayStatics.h>
#include "FSpider.h"
#include "FPlayerController.h"
#include "Particles/ParticleSystem.h"

AFWeapon::AFWeapon()
{
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	RootComponent = MeshComp;

	MuzzleSocketName = "MuzzleSocket";

	MaxAmmo = 10;
	ClipSize = 30;
	bReloading = false;
	bFireReady = true;
}

void AFWeapon::BeginPlay()
{
	Super::BeginPlay();
	Ammo = MaxAmmo;
}

void AFWeapon::StartFire()
{
	AActor* MyOwner = GetOwner();

	if (MyOwner)
	{
		Ammo--;
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();
		FVector TraceEnd = EyeLocation + (ShotDirection * 10000);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
		{
			AActor* HitActor = Hit.GetActor();

			if (AFSpider* Spider = Cast<AFSpider>(HitActor))
			{
				if (AFPlayerController* PC = Cast<AFPlayerController>(MyOwner->GetInstigatorController()))
				{
					UGameplayStatics::ApplyPointDamage(HitActor, DamageAmount, ShotDirection, Hit, MyOwner->GetInstigatorController(), this, DamageType);
					PC->OnHitEnemy();
					if (ImpactEffect)
					{
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
					}
				}
			}
		}

		if (MuzzleEffect)
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, MuzzleSocketName);
		}
		
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AFWeapon::StopFire, 5.0f, true);
		bFireReady = false;


		/*DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);*/
	}
}

void AFWeapon::StopFire()
{
	bFireReady = true;
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void AFWeapon::Reload()
{
	
	if (Ammo < ClipSize && MaxAmmo != 0 && !bReloading)
	{
		bReloading = true;
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &AFWeapon::EndReload, 3.0f, false);
	}
}

void AFWeapon::EndReload()
{
	bReloading = false;

	AmmoDifference = ClipSize - Ammo;
	if (MaxAmmo > AmmoDifference)
	{
		Ammo += AmmoDifference;
		MaxAmmo -= AmmoDifference;
	}
	else
	{
		Ammo += MaxAmmo;
		MaxAmmo = 0;
	}
	
}

USkeletalMeshComponent* AFWeapon::GetMeshComp()
{
	return MeshComp;
}



