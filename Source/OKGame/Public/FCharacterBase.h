// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FCharacterBase.generated.h"

class AFWeapon;

UCLASS()
class OKGAME_API AFCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFCharacterBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	class UFHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	class USkeletalMeshComponent* HandMesh;

	AFWeapon* GetCurrentWeapon() { return CurrentWeapon; }
	UFHealthComponent* GetHealthComponent() { return HealthComponent; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	UPROPERTY(BlueprintReadOnly);
	AFWeapon* CurrentWeapon;


	UPROPERTY(BlueprintReadOnly, Category = Character)
	bool bDied = false;

	UFUNCTION(BlueprintCallable)
	void HandleDeath();

	virtual FVector GetPawnViewLocation() const;

	void StartFire();
	void StopFire();

	void StartAim();
	void EndAim();

	void Reload();

private:

	

	UPROPERTY(EditDefaultsOnly, Category = "Character")
		TSubclassOf<AFWeapon> StarterWeaponClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Character")
		FName WeaponAttachSocketName;

	UAnimInstance* PlayerAnimInstance;
	UAnimInstance* PistolAnimInstance;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		class UAnimMontage* PistolFireMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		class UAnimMontage* HandFireMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		class UAnimMontage* ADSFireMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		class UAnimMontage* PistolReloadMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		class UAnimMontage* HandReloadMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		class USoundBase* FireSound;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bAiming;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bSprinting;

	void Interact();

public:	
	UFUNCTION()
	void Walk();

	UPROPERTY(EditAnywhere)
	float WalkingSpeed;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
