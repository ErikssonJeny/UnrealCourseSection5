// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward declarations
class UTankMovementComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		UTankMovementComponent* tankMovementComponent = NULL;

	FTankDelegate OnDeath;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:	

	UPROPERTY(EditDefaultsOnly, Category = "Health")
		int32 startingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 currentHealth = 100;
	
};
