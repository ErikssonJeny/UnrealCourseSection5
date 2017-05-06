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

	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;

private:

	void BeginPlay() override;
	void Tick(float deltaTime) override;
	
};
