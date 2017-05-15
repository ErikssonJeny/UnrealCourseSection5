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
	Locked,
	NoAmmo
};

//Holds parameters & properties for barrels & turrets
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable, Category = "Input")
		void Initialise(UTankBarrel* setBarrel, UTankTurret* setTurret);

	FVector aimDirection;

	// Sets default values for this component's properties
	UTankAimingComponent();

	EFiringStatus GetFiringStatus() const;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Allows the blueprint to call this method
	UFUNCTION(BlueprintCallable, Category = "Input")
		void Fire();

	UFUNCTION(BlueprintCallable, Category = "Input")
		void AimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = "Ammo")
		int32 GetAmmoCount() const;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 ammoCount = 2;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus firingStatus = EFiringStatus::Aiming;

	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AProjectile> projectileBP = NULL;

private:

	/* Blueprint Variables*/

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float launchSpeed = 2500;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float proposedSpeed = 2500;

	//Gun reload time in seconds
	UPROPERTY(EditAnywhere, Category = "Firing")
		float reloadTime = 3;

	/* Non-Blueprint Variables*/

	double lastFireTime = 0;

	UTankBarrel* barrel = NULL;
	UTankTurret* turret = NULL;

	/* Functions */

	bool IsBarrelMoving();
	void MoveBarrel(FVector);
		
};
