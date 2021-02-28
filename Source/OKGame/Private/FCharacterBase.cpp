// Fill out your copyright notice in the Description page of Project Settings.


#include "FCharacterBase.h"
#include <Camera/CameraComponent.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include <Components/SphereComponent.h>
#include "FHealthComponent.h"
#include <Components/SkeletalMeshComponent.h>
#include "FHealthPickup.h"
#include <GameFramework/SpringArmComponent.h>
#include "FWeapon.h"
#include <Animation/AnimInstance.h>
#include <Kismet/GameplayStatics.h>
#include "FInteractableBase.h"

// Sets default values
AFCharacterBase::AFCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComp->SetupAttachment(GetMesh());

	HandMesh = CreateDefaultSubobject<USkeletalMeshComponent>("HandMesh");
	HandMesh->SetupAttachment(CameraComp);
	HandMesh->SetRelativeLocation(FVector(-12.0f, 0.0f, -165.0f));
	HandMesh->SetRelativeRotation(FRotator(-1.0f, 0.0f, -90.0f));

	HealthComponent = CreateDefaultSubobject<UFHealthComponent>("HealthComponent");

	WalkingSpeed = 1000.0f;

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AFCharacterBase::BeginOverlap);

	WeaponAttachSocketName = "WeaponSocket";

	bAiming = false;
}

// Called when the game starts or when spawned
void AFCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	PlayerAnimInstance = HandMesh->GetAnimInstance();

	// Spawn the weapon here
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	CurrentWeapon = GetWorld()->SpawnActor<AFWeapon>(StarterWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (CurrentWeapon)
	{
		PistolAnimInstance = CurrentWeapon->GetMeshComp()->GetAnimInstance();
		CurrentWeapon->SetOwner(this);
		CurrentWeapon->AttachToComponent(HandMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponAttachSocketName);
	}
}

void AFCharacterBase::MoveForward(float Value)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AFCharacterBase::MoveRight(float Value)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AFCharacterBase::HandleDeath()
{
	/*if (HealthComponent->GetHealth() <= 0.0f && !bDied)
	{
		bDied = true;
	}*/
}


FVector AFCharacterBase::GetPawnViewLocation() const
{
	if (CameraComp)
	{
		return CameraComp->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
}

void AFCharacterBase::StartFire()
{
	if (CurrentWeapon && !CurrentWeapon->bReloading && !bSprinting && PlayerAnimInstance && CurrentWeapon->Ammo > 0)
	{
		CurrentWeapon->StartFire();
		
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, CurrentWeapon->GetActorLocation(), 0.7f);

		if (!bAiming)
		{
			PlayerAnimInstance->Montage_Play(HandFireMontage);
			PistolAnimInstance->Montage_Play(PistolFireMontage);
		}
		else
		{
			PlayerAnimInstance->Montage_Play(ADSFireMontage);
			PistolAnimInstance->Montage_Play(PistolFireMontage);
		}
	}
}

void AFCharacterBase::StopFire()
{
	CurrentWeapon->StopFire();
}

void AFCharacterBase::StartAim()
{
	if (!bSprinting)
	{
		bAiming = true;
	}
}

void AFCharacterBase::EndAim()
{
	bAiming = false;
}

void AFCharacterBase::Reload()
{
	CurrentWeapon->Reload();
	if (CurrentWeapon->bReloading)
	{
		PistolAnimInstance->Montage_Play(PistolReloadMontage);
		PlayerAnimInstance->Montage_Play(HandReloadMontage);
	}
}

void AFCharacterBase::Interact()
{
	FHitResult Hit;
	FVector Start = CameraComp->GetComponentLocation();
	FVector End = Start + CameraComp->GetForwardVector() * 300;

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility))
	{
		AFInteractableBase* Obj = Cast<AFInteractableBase>(Hit.Actor);
		if (Obj)
		{
			Obj->Interact();
		}
	}
}

void AFCharacterBase::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
}

void AFCharacterBase::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFHealthPickup* HealthPickup = Cast<AFHealthPickup>(OtherActor);

	if (HealthPickup)
	{
		HealthPickup->OnPickup(HealthComponent);
	}
}

void AFCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFCharacterBase::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFCharacterBase::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFCharacterBase::StopFire);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AFCharacterBase::Reload);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFCharacterBase::Interact);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AFCharacterBase::StartAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AFCharacterBase::EndAim);
}

