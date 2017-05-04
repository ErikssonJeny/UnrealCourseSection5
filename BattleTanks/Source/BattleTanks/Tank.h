// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Public/TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel; //Forward declaration

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt(FVector);

	//Allows the blueprint to call this method
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* assignedBarrel);

protected:

	UTankAimingComponent* tankAimingComponent = NULL;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
		float launchSpeed = 100000;

	
	
};
