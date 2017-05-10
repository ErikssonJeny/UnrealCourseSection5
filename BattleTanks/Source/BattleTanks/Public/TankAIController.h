// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

//Forward declarations
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

private:

	ATank* controlledTank = NULL;
	ATank* playerTank = NULL;

	UPROPERTY(EditDefaultsOnly, Category = Pathfinding)
		float acceptanceRadius = 50.f;

	void BeginPlay() override;
	void Tick(float deltaTime) override;
	
};
