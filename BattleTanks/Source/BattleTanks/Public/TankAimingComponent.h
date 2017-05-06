// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Forward declarations
class UTankBarrel;
class UTankTurret;

//Holds parameters & properties for barrels & turrets
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void SetBarrelReference(UTankBarrel*);
	void SetTurretReference(UTankTurret*);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector, float);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UTankBarrel* barrel = NULL;
	UTankTurret* turret = NULL;

	void MoveBarrel(FVector);
	void MoveTurret(FVector);
		
};
