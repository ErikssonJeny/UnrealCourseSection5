// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

//Forward declarations
class ATank;
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:


protected:

	UPROPERTY(EditDefaultsOnly, Category = "Pathfinding")
		float acceptanceRadius = 50.f;

private:


	UFUNCTION()
		void OnTankDeath();

	ATank* playerTank = NULL;
	UTankAimingComponent* aimingComponent = NULL;

	virtual void SetPawn(APawn* InPawn) override;


	void BeginPlay() override;
	void Tick(float deltaTime) override;
	UTankAimingComponent* GetAimingComponent();
	
};
