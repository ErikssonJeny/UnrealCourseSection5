// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Forward declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;

//Enum

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

//Holds parameters & properties for barrels & turrets
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable, Category = "Input")
		void Initialise(UTankBarrel* setBarrel, UTankTurret* setTurret);

	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Allows the blueprint to call this method
	UFUNCTION(BlueprintCallable, Category = "Input")
		void Fire();

	UFUNCTION(BlueprintCallable, Category = "Input")
		void AimAt(FVector hitLocation);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus firingStatus = EFiringStatus::Aiming;

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

	double lastFireTime = 0;

	UTankBarrel* barrel = NULL;
	UTankTurret* turret = NULL;

	/* Functions */

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	void MoveBarrel(FVector);
		
};
