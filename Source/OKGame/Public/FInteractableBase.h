// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "FInteractableBase.generated.h"

UCLASS()
class OKGAME_API AFInteractableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFInteractableBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class AFCharacterBase* Character;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() PURE_VIRTUAL(AFInteractableBase::Interact, );

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName InteractionText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* RootComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	class USphereComponent* InteractionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	class UWidgetComponent* WidgetComp;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

};
