// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt(FVector);

	//Allows the blueprint to call this method
	UFUNCTION(BlueprintCallable, Category = "Input")
		void Fire();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		UTankMovementComponent* tankMovementComponent = NULL;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		UTankAimingComponent* tankAimingComponent = NULL;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	/* Blueprint Variables*/

	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AProjectile> projectileBP = NULL;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float launchSpeed = 2500;

	//Gun reload time in seconds
	UPROPERTY(EditAnywhere, Category = "Firing")
		float reloadTime = 3;

	/* Non-Blueprint Variables*/

	UTankBarrel* barrel = NULL;
	double lastFireTime = 0;

	/* Functions */

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
